#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInteger.h"

// ------- Sub functions -------

Node* newNode(unsigned char digit, Node* prev) {
    Node* n = (Node*)calloc(1, sizeof(Node));
    if (n) {
        n->digit = digit;
        n->prev = prev;
    }
    return n;
}

void clearNodes(BigInteger* BI) {
    Node* cur = BI->LowerDigits;
    while (cur) {
        Node* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    BI->LowerDigits = BI->HigherDigits = NULL;
}

void makeZero(BigInteger* BI) {
    if (!BI) return;
    clearNodes(BI);
    BI->LowerDigits = BI->HigherDigits = newNode(0, NULL);
    BI->sign = 0;
}

int isZero(const BigInteger* BI) {
    return !BI->LowerDigits || (BI->LowerDigits == BI->HigherDigits && BI->LowerDigits->digit == 0);
}

int digitCounter(const BigInteger* BI) {
    int count = 0;
    for (Node* n = BI ? BI->LowerDigits : NULL; n; n = n->next) count++;
    return count;
}

// Delete leading zeros from the result
void trimZeros(BigInteger* BI) {
    while (BI->HigherDigits != BI->LowerDigits && BI->HigherDigits->digit == 0) {
        Node* tmp = BI->HigherDigits;
        BI->HigherDigits = tmp->prev;
        BI->HigherDigits->next = NULL;
        free(tmp);
    }
}

// ------- Arithmetic -------
int addSmall(BigInteger* BI, unsigned int d) {
    if (!BI) return -1;
    unsigned int carry = d;
    Node* cur = BI->LowerDigits;

    while (cur && carry) {
        unsigned int tmp = cur->digit + carry;
        cur->digit = (unsigned char)(tmp & 0xFF);
        carry = tmp >> 8;
        if (!cur->next && carry) {
            cur->next = newNode(0, cur);
            BI->HigherDigits = cur->next;
        }
        cur = cur->next;
    }
    return 0;
}

int mulSmall(BigInteger* BI, unsigned int m) {
    if (!BI) return -1;
    unsigned int carry = 0;
    Node* cur = BI->LowerDigits;

    while (cur || carry) {
        unsigned int tmp = (cur ? cur->digit * m : 0) + carry;
        unsigned char digit = (unsigned char)(tmp & 0xFF);
        carry = tmp >> 8;

        if (cur) {
            cur->digit = digit;
            if (!cur->next && carry) {
                cur->next = newNode(0, cur);
                BI->HigherDigits = cur->next;
            }
            cur = cur->next;
        } else {
            BI->HigherDigits->next = newNode(digit, BI->HigherDigits);
            BI->HigherDigits = BI->HigherDigits->next;
        }
    }
    trimZeros(BI);
    return 0;
}

int divSmall(BigInteger* BI, unsigned int d, unsigned int* rem) {
    if (!BI || d == 0) return -1;
    unsigned int remainder = 0;
    for (Node* cur = BI->HigherDigits; cur; cur = cur->prev) {
        unsigned int tmp = (remainder << 8) | cur->digit;
        cur->digit = (unsigned char)(tmp / d);
        remainder = tmp % d;
    }
    trimZeros(BI);
    if (rem) *rem = remainder;
    return 0;
}

int compareAbs(const BigInteger* a, const BigInteger* b) {
    int lenA = digitCounter(a), lenB = digitCounter(b);
    if (lenA != lenB) return lenA > lenB ? 1 : -1;
    for (Node *curA = a->HigherDigits, *curB = b->HigherDigits; curA; curA = curA->prev, curB = curB->prev) {
        if (curA->digit != curB->digit) return curA->digit > curB->digit ? 1 : -1;
    }
    return 0;
}

BigInteger* addBigIntegerAbs(const BigInteger* a, const BigInteger* b) {
    if (!a || !b) return NULL;
    BigInteger* res = createBigInteger();
    unsigned int carry = 0;
    Node *curA = a->LowerDigits, *curB = b->LowerDigits, *last = NULL;

    while (curA || curB || carry) {
        unsigned int sum = carry + (curA ? curA->digit : 0) + (curB ? curB->digit : 0);
        Node* n = newNode(sum & 0xFF, last);
        if (last) last->next = n; else res->LowerDigits = n;
        last = n;
        carry = sum >> 8;
        if (curA) curA = curA->next;
        if (curB) curB = curB->next;
    }
    res->HigherDigits = last;
    if (!res->LowerDigits) makeZero(res); // if both a and b were zero
    return res;
}

BigInteger* subBigIntegerAbs(const BigInteger* a, const BigInteger* b) {
    BigInteger* res = createBigInteger();
    Node *curA = a->LowerDigits, *curB = b->LowerDigits, *last = NULL;
    int borrow = 0;

    while (curA) {
        int val = curA->digit - borrow - (curB ? curB->digit : 0);
        borrow = (val < 0);
        if (borrow) val += 256;
        Node* n = newNode((unsigned char)val, last);
        if (last) last->next = n; else res->LowerDigits = n;
        last = n;
        curA = curA->next;
        if (curB) curB = curB->next;
    }
    res->HigherDigits = last;
    trimZeros(res);
    return res;
}


// ------- API functions -------
BigInteger* createBigInteger() {
    return (BigInteger*)calloc(1, sizeof(BigInteger));
}

int count(const BigInteger* BI) {
    if (!BI || !BI->LowerDigits) return 0;
    int c = 0;
    Node* cur = BI->LowerDigits;
    while (cur) {
        c++;
        cur = cur->next;
    }
    return c;
}

int isEmpty(const BigInteger* BI) {
    return count(BI) == 0; // no digits means zero
}

int isFull(const BigInteger* BI) {
    return 0; // never full (must be)
}

void makeEmpty(BigInteger* BI) {
    if (!BI) return;
    Node* cur = BI->LowerDigits;
    while (cur) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }
    BI->LowerDigits = NULL;
    BI->HigherDigits = NULL;
    BI->sign = 0;
}

BigInteger* clone(const BigInteger* BI) {
    if (!BI) return NULL;
    BigInteger* copy = createBigInteger();
    if (isEmpty(BI)) return copy;

    copy->sign = BI->sign;
    Node* cur = BI->LowerDigits;
    Node* prevNew = NULL;

    while (cur) {
        Node* nNew = (Node*)malloc(sizeof(Node));
        nNew->digit = cur->digit;
        nNew->prev = prevNew;
        nNew->next = NULL;

        if (prevNew) prevNew->next = nNew;
        else copy->LowerDigits = nNew;

        copy->HigherDigits = nNew;
        prevNew = nNew;
        cur = cur->next;
    }
    return copy;
}

int stringToBigInteger(const char* str, BigInteger* BI) {
    if (!str || !BI) return -1;
    makeZero(BI);
    int i = (str[0] == '-');
    if (str[i] == '\0') return -2;
    for (; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9') return -3;
        mulSmall(BI, 10);
        addSmall(BI, str[i] - '0');
    }
    BI->sign = (str[0] == '-' && !isZero(BI));
    return 0;
}

char* bigIntegerToStringDec(const BigInteger* BI) {
    if (!BI) return NULL;
    if (isZero(BI)) {
        char* res = malloc(2);
        if (res) strcpy(res, "0");
        return res;
    }
    BigInteger* tmp = clone(BI);
    int capacity = digitCounter(tmp) * 4 + 2; // Assumption
    char* buffer = malloc(capacity);
    int pos = 0;

    while (!isZero(tmp)) {
        unsigned int rem;
        divSmall(tmp, 10, &rem);
        buffer[pos++] = '0' + (char)rem;
    }
    // Add sign if negative
    if (BI->sign && pos > 0) buffer[pos++] = '-'; 
    buffer[pos] = '\0';

    for (int i = 0; i < pos / 2; i++) {
        char t = buffer[i];
        buffer[i] = buffer[pos - 1 - i];
        buffer[pos - 1 - i] = t;
    }
    Done(&tmp);
    return buffer;
}

BigInteger* addBigInteger(const BigInteger* a, const BigInteger* b) {
    if (!a || !b) return NULL;
    if (a->sign == b->sign) {
        BigInteger* res = addBigIntegerAbs(a, b);
        res->sign = a->sign;
        return res;
    }
    int cmp = compareAbs(a, b);
    if (cmp == 0) { BigInteger* z = createBigInteger(); makeZero(z); return z; }
    BigInteger* res = (cmp > 0) ? subBigIntegerAbs(a, b) : subBigIntegerAbs(b, a);
    res->sign = (cmp > 0) ? a->sign : b->sign;
    return res;
}

BigInteger* subBigInteger(const BigInteger* a, const BigInteger* b) {
    if (!a || !b) return NULL;

    // different signs
    if (a->sign != b->sign) {
        BigInteger* res = addBigIntegerAbs(a, b);
        res->sign = a->sign;
        return res;
    }

    // same signs
    int cmp = compareAbs(a, b);
    if (cmp == 0) {
        BigInteger* res = createBigInteger();
        makeZero(res);
        return res;
    }

    BigInteger* res;
    if (cmp > 0) {
        res = subBigIntegerAbs(a, b);
        res->sign = a->sign;
    } else {
        res = subBigIntegerAbs(b, a);
        res->sign = !a->sign; // opposite sing
    }
    
    return res;
}

BigInteger* mulBigInteger(const BigInteger* a, const BigInteger* b) {
    if (!a || !b) return NULL;

    // if any of them is zero, return zero
    if (isZero(a) || isZero(b)) {
        BigInteger* res = createBigInteger();
        makeZero(res);
        return res;
    }

    // result will be here
    BigInteger* totalRes = createBigInteger();
    makeZero(totalRes);

    int shift = 0; 
    
    for (Node* curB = b->LowerDigits; curB; curB = curB->next) {
        if (curB->digit != 0) {
            // copy original
            BigInteger* temp = clone(a);
            temp->sign = 0; 
            
            mulSmall(temp, curB->digit);
            
            // shift left each node after mul
            for (int s = 0; s < shift; s++) {
                Node* nNew = newNode(0, NULL);
                nNew->next = temp->LowerDigits;
                if (temp->LowerDigits) temp->LowerDigits->prev = nNew;
                temp->LowerDigits = nNew;
            }

            // add to total
            BigInteger* oldTotal = totalRes;
            totalRes = addBigInteger(totalRes, temp);
            
            // free temp obj
            Done(&oldTotal);
            Done(&temp);
        }
        shift++;
    }

    // set sign of the result
    totalRes->sign = (a->sign != b->sign);
    
    return totalRes;
}

BigInteger* divBigInteger(const BigInteger* a, const BigInteger* b) {
    if (!a || !b || isZero(b)) return NULL; // division by zero

    BigInteger* quotient = createBigInteger();
    makeZero(quotient);

    if (compareAbs(a, b) < 0) {
        return quotient;
    }
    
    BigInteger* current = createBigInteger();
    makeZero(current);
    
    // result will be here
    BigInteger* result = createBigInteger();
    makeZero(result);

    BigInteger* bAbs = clone(b);
    bAbs->sign = 0;

    // go from higher digits to lower
    for (Node* curA = a->HigherDigits; curA; curA = curA->prev) {
        if (isZero(current)) {
            current->LowerDigits->digit = curA->digit;
        } else {
            mulSmall(current, 256);
            addSmall(current, curA->digit);
        }
        trimZeros(current);

        unsigned char digit = 0;
        while (compareAbs(current, bAbs) >= 0) {
            BigInteger* nextCur = subBigIntegerAbs(current, bAbs);
            Done(&current);
            current = nextCur;
            digit++;
        }

        mulSmall(result, 256);
        addSmall(result, digit);
    }

    result->sign = (a->sign != b->sign);

    Done(&current);
    Done(&bAbs);
    Done(&quotient);

    return result;
}

// work only with numbers with the same sign
BigInteger* modBigInteger(const BigInteger* a, const BigInteger* b) {
    if (!a || !b || isZero(b) || (a->sign != b->sign)) return NULL;

    // remainder will be here
    BigInteger* current = createBigInteger();
    makeZero(current);

    BigInteger* bAbs = clone(b);
    bAbs->sign = 0;

    // go from higher digits to lower
    for (Node* curA = a->HigherDigits; curA; curA = curA->prev) {
        if (isZero(current)) {
            current->LowerDigits->digit = curA->digit;
        } else {
            mulSmall(current, 256);
            addSmall(current, curA->digit);
        }
        trimZeros(current);

        while (compareAbs(current, bAbs) >= 0) {
            BigInteger* nextCur = subBigIntegerAbs(current, bAbs);
            Done(&current);
            current = nextCur;
        }
    }

    // sign same as (a) 
    current->sign = a->sign;

    Done(&bAbs);
    
    return current;
}

void Done(BigInteger** BI) {
    if (BI && *BI) {
        clearNodes(*BI);
        free(*BI);
        *BI = NULL;
    }
}
