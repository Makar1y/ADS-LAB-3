// main.c
#include <stdio.h>
#include "deque.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);

    // Konsolės simbolių transliavimas UTF-8 koduote
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    
    Deque* dq = createDeque(5);
    
    insertBack(dq, 10);
    insertBack(dq, 20);
    insertFront(dq, 5);
    
    printf("Elementų skaičius: %d\n", getCount(dq));
    printf("Pradžios elementas (getFront): %d\n", getFront(dq));
    printf("Pabaigos elementas (getBack): %d\n", getBack(dq));
    
    printf("\nIšimame iš pradžios: %d\n", removeFront(dq)); 
    printf("Išimame iš pabaigos: %d\n", removeBack(dq));   
    
    printf("Elementų skaičius po išėmimų: %d\n", getCount(dq));
    fflush(stdout);
    destroyDeque(dq);
    printf("\nDekas sėkmingai sunaikintas.\n");
    
    return 0;
}