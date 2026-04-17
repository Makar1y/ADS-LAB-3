#ifndef BigInteger_h
#define BigInteger_h

typedef struct Node {
    unsigned char digit;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct BigInteger {
    Node* LowerDigits;
    Node* HigherDigits;
    char sign; // 0 for positive, 1 for negative
} BigInteger;

BigInteger* createBigInteger();

// ------- Queries -------
int count(const BigInteger* BI);

int isEmpty(const BigInteger* BI);

int isFull(const BigInteger* BI);

// ------- Commands -------
void makeEmpty(BigInteger* BI);

BigInteger* clone(const BigInteger* BI);

// ------- Input and output ------- 
int stringToBigInteger(const char* str, BigInteger* BI);

char* bigIntegerToStringDec(const BigInteger* BI);

// ------- Arithmetic -------
BigInteger* addBigInteger(const BigInteger* a, const BigInteger* b);

BigInteger* subBigInteger(const BigInteger* a, const BigInteger* b);

BigInteger* mulBigInteger(const BigInteger* a, const BigInteger* b);

BigInteger* divBigInteger(const BigInteger* a, const BigInteger* b);

BigInteger* modBigInteger(const BigInteger* a, const BigInteger* b);

// ------- Delete -------
void Done(BigInteger** BI);
#endif