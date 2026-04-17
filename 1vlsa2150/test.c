#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "BigInteger.h"
#include "BigInteger.c"

int main() {
{
    printf("Test for createBigInteger and Done: \n");
        BigInteger* bi = createBigInteger();
        assert(bi != NULL);
        Done(&bi);
        assert(bi == NULL);
    printf("+test passed\n\n");
}
{
    printf("Test for stringToBigInteger and bigIntegerToStringDec: \n");
        BigInteger* bi = createBigInteger();
        assert(stringToBigInteger("12345", bi) == 0);
        char* str = bigIntegerToStringDec(bi);
        assert(strcmp(str, "12345") == 0);
        free(str);
        Done(&bi);
    printf("+test passed\n\n");   
}
{
    printf("Test for isEmpty: \n");
        BigInteger* bi = createBigInteger();
        assert(isEmpty(bi) == 1);
        stringToBigInteger("123", bi);
        assert(isEmpty(bi) == 0);
        Done(&bi);
    printf("+test passed\n\n");
}
{
    printf("Test for count: \n");
        BigInteger* bi = createBigInteger();
        assert(count(bi) == 0);
        stringToBigInteger("1000", bi);
        assert(count(bi) == 2);
        Done(&bi);
    printf("+test passed\n\n");
}
{
    printf("Test for isFull: \n");
        BigInteger* bi = createBigInteger();
        assert(isFull(bi) == 0);
        Done(&bi);
    printf("+test passed\n\n");
}
{
    printf("Test for makeEmpty: \n");
        BigInteger* bi = createBigInteger();
        stringToBigInteger("123", bi);
        assert(isEmpty(bi) == 0);
        makeEmpty(bi);
        assert(isEmpty(bi) == 1);
        Done(&bi);
    printf("+test passed\n\n");
}
{
    printf("Test for clone: \n");
        BigInteger* bi1 = createBigInteger();
        stringToBigInteger("-42", bi1);
        
        BigInteger* bi2 = clone(bi1);
        assert(bi2->sign == bi1->sign);
        
        char* str1 = bigIntegerToStringDec(bi1);
        char* str2 = bigIntegerToStringDec(bi2);
        assert(strcmp(str1, str2) == 0);
        
        free(str1);
        free(str2);
        Done(&bi1);
        Done(&bi2);
    printf("+test passed\n\n");   
}
{
    printf("Test for addBigInteger: \n");
        BigInteger* bi1 = createBigInteger();
        BigInteger* bi2 = createBigInteger();

        printf("Testing with '+' '+'\n");
            stringToBigInteger("150000", bi1);
            stringToBigInteger("50000", bi2);
            BigInteger* sum = addBigInteger(bi1, bi2);
            char* str = bigIntegerToStringDec(sum);
            assert(strcmp(str, "200000") == 0);
            free(str);
        printf("+test passed\n");
        
        printf("Testing with '-' '-'\n");
            stringToBigInteger("-150000", bi1);
            stringToBigInteger("-50000", bi2);
            sum = addBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(sum);
            assert(strcmp(str, "-200000") == 0);
            free(str);
        printf("+test passed\n");

        printf("Testing with '+' '-'\n");
            stringToBigInteger("150000", bi1);
            stringToBigInteger("-50000", bi2);
            sum = addBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(sum);
            assert(strcmp(str, "100000") == 0);
            free(str);
        printf("+test passed\n");

        printf("Testing with '-' '+'\n");
            stringToBigInteger("-150000", bi1);
            stringToBigInteger("50000", bi2);
            sum = addBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(sum);
            assert(strcmp(str, "-100000") == 0);
            free(str);
        printf("+test passed\n");

        Done(&bi1);
        Done(&bi2);
    printf("+test for addBigInteger passed\n\n");   
}
{
    printf("Test for subBigInteger: \n");
        BigInteger* bi1 = createBigInteger();
        BigInteger* bi2 = createBigInteger();

        printf("Testing with '+' '+'\n");
            stringToBigInteger("150000", bi1);
            stringToBigInteger("50000", bi2);
            BigInteger* diff = subBigInteger(bi1, bi2);
            char* str = bigIntegerToStringDec(diff);
            assert(strcmp(str, "100000") == 0);
            free(str);
        printf("+test passed\n");
        
        printf("Testing with '-' '-'\n");
            stringToBigInteger("-150000", bi1);
            stringToBigInteger("-50000", bi2);
            diff = subBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(diff);
            assert(strcmp(str, "-100000") == 0);
            free(str);
        printf("+test passed\n");

        printf("Testing with '+' '-'\n");
            stringToBigInteger("150000", bi1);
            stringToBigInteger("-50000", bi2);
            diff = subBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(diff);
            assert(strcmp(str, "200000") == 0);
            free(str);
        printf("+test passed\n");

        printf("Testing with '-' '+'\n");
            stringToBigInteger("-150000", bi1);
            stringToBigInteger("50000", bi2);
            diff = subBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(diff);  
            assert(strcmp(str, "-200000") == 0);
            free(str);
        printf("+test passed\n");

        Done(&bi1);
        Done(&bi2);
    printf("+test for subBigInteger passed\n\n");   
}
{
    printf("Test for mulBigInteger: \n");
        BigInteger* bi1 = createBigInteger();
        BigInteger* bi2 = createBigInteger();

        printf("Testing with '+' '+'\n");
            stringToBigInteger("10", bi1);
            stringToBigInteger("5", bi2);
            BigInteger* prod = mulBigInteger(bi1, bi2);
            char* str = bigIntegerToStringDec(prod);
            assert(strcmp(str, "50") == 0);
            free(str);
        printf("+test passed\n");

        printf("Testing with '-' '-'\n");
            stringToBigInteger("-10", bi1);
            stringToBigInteger("-5", bi2);
            prod = mulBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(prod);
            assert(strcmp(str, "50") == 0);
            free(str);
        printf("+test passed\n");

        printf("Testing with '+' '-'\n");
            stringToBigInteger("10", bi1);
            stringToBigInteger("-5", bi2);
            prod = mulBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(prod);
            assert(strcmp(str, "-50") ==  0); 
            free(str);
        printf("+test passed\n");

        printf("Testing with '-' '+'\n");
            stringToBigInteger("-10", bi1);
            stringToBigInteger("5", bi2);
            prod = mulBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(prod);  
            assert(strcmp(str, "-50") ==  0); 
            free(str);
        printf("+test passed\n");

        Done(&bi1);
        Done(&bi2);

    printf("+test for mulBigInteger passed\n\n");   
}
{
    printf("Test for divBigInteger: \n");
        BigInteger* bi1 = createBigInteger();
        BigInteger* bi2 = createBigInteger();

        printf("Testing with '+' '+'\n");
            stringToBigInteger("100", bi1);
            stringToBigInteger("5", bi2);
            BigInteger* quot = divBigInteger(bi1, bi2);
            char* str = bigIntegerToStringDec(quot);
            assert(strcmp(str, "20") == 0);
            free(str);
        printf("+test passed\n");

        printf("Testing with '-' '-'\n");
            stringToBigInteger("-100", bi1);
            stringToBigInteger("-5", bi2);
            quot = divBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(quot);
            assert(strcmp(str, "20") == 0);
            free(str);
        printf("+test passed\n");

        printf("Testing with '+' '-'\n");
            stringToBigInteger("100", bi1);
            stringToBigInteger("-5", bi2);
            quot = divBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(quot);
            assert(strcmp(str, "-20") ==  0); 
            free(str);
        printf("+test passed\n");

        printf("Testing with '-' '+'\n");
            stringToBigInteger("-100", bi1);
            stringToBigInteger("5", bi2);
            quot = divBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(quot);  
            assert(strcmp(str, "-20") ==  0); 
            free(str);
        printf("+test passed\n");

        Done(&bi1);
        Done(&bi2);

    printf("+test for divBigInteger passed\n\n");   
}
{
    printf("Test for modBigInteger: \n");
        BigInteger* bi1 = createBigInteger();
        BigInteger* bi2 = createBigInteger();

        printf("Testing with '+' '+'\n");
            stringToBigInteger("100", bi1);
            stringToBigInteger("7", bi2);
            BigInteger* mod = modBigInteger(bi1, bi2);
            char* str = bigIntegerToStringDec(mod);
            assert(strcmp(str, "2") == 0);
            free(str);
        printf("+test passed\n");

        printf("Testing with '-' '-'\n");
            stringToBigInteger("-100", bi1);
            stringToBigInteger("-7", bi2);
            mod = modBigInteger(bi1, bi2);
            str = bigIntegerToStringDec(mod);
            assert(strcmp(str, "-2") == 0);
            free(str);
        printf("+test passed\n");

        Done(&bi1);
        Done(&bi2);

    printf("+test for modBigInteger passed\n\n");   
}

    return 0;
};
