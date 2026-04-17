#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"


/*
* Sukuria tuščią deką.
* Per parametrus ima jo dydį. 
* Grąžina rodyklę į naują deką.
*/
Deque* createDeque(int capacity) {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    if (!dq) {
        printf("Klaida: Nepavyko išskirti atminties.\n");
        exit(1);
    }
    
    dq->data = (int*)malloc(capacity * sizeof(int));
    if (!dq->data) {
        printf("Klaida: Nepavyko išskirti atminties masyvui.\n");
        free(dq);
        exit(1);
    }
    
    dq->capacity = capacity;
    dq->size = 0;
    dq->front = 0;
    dq->rear = capacity - 1; 
    return dq;
}

//Grąžina 1, jei tuščias, 0 - jei ne.
int isEmpty(Deque* dq) {
    return dq->size == 0;
}

//Grąžina 1, jei pilnas, 0 - jei ne.
int isFull(Deque* dq) {
    if (dq->size == dq->capacity) {
        return 1;
    }
    return 0;
}

//Įterpia reikšmę deko priekyje.
void insertFront(Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Klaida: Dekas pilnas, negalima įterpti į pradžią\n");
        return;
    }
    dq->front = (dq->front - 1 + dq->capacity) % dq->capacity;
    dq->data[dq->front] = value;
    dq->size++;
}

//Ištrina reikšmę iš deko priekio ir grąžina išrintą reikšmę.
int removeFront(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Klaida: Dekas tuščias, nėra ko išimti iš pradžios\n");
        return -1; 
    }
    int value = dq->data[dq->front];
    dq->front = (dq->front + 1) % dq->capacity;
    dq->size--;
    return value;
}

//Įterpia reikšmę deko gale.
void insertBack(Deque* dq, int value) {
    if (isFull(dq)) {
        printf("Klaida: Dekas pilnas, negalima įterpti į pabaigą\n");
        return;
    }
    dq->rear = (dq->rear + 1) % dq->capacity;
    dq->data[dq->rear] = value;
    dq->size++;
}

//Ištrina reikšmę iš deko galo. Grąžina ištrintą reikšmę
int removeBack(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Klaida: Dekas tuščias, nėra ko išimti iš pabaigos\n");
        return -1;
    }
    int value = dq->data[dq->rear];
    dq->rear = (dq->rear - 1 + dq->capacity) % dq->capacity;
    dq->size--;
    return value;
}

//Grąžina reikšmę, kuri yra deko priekyje.
int getFront(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Klaida: Dekas tuščias.\n");
        return -1;
    }
    return dq->data[dq->front];
}

//Grąžina reikšmę, kuri yra deko gale.
int getBack(Deque* dq) {
    if (isEmpty(dq)) {
        printf("Klaida: Dekas tuščias.\n");
        return -1;
    }
    return dq->data[dq->rear];
}

//Grąžina elementų esančių deke skaičių.
int getCount(Deque* dq) {
    return dq->size;
}

//Sunaikina deką (atlaisvina atmintį).
void destroyDeque(Deque* dq) {
    if (dq) {
        if (dq->data) {
            free(dq->data);
        }
        free(dq);
    }
}

//Sukuria deko kopiją. Grąžina rodyklę į naują deką
Deque* clone(Deque* dq) {
    if (!dq) return NULL;
    
    //Panaudojame jau esamą funkciją naujam dekui sukurti.
    Deque* newDq = createDeque(dq->capacity);
    
    //Nukopijuojame kintamuosius.
    newDq->size = dq->size;
    newDq->front = dq->front;
    newDq->rear = dq->rear;
    
    //Nukopijuojame visą duomenų masyvą.
    for (int i = 0; i < dq->capacity; i++) {
        newDq->data[i] = dq->data[i];
    }
    
    return newDq;
}

//Išvalo deko duomenis.
void makeEmpty(Deque* dq) {
    if (!dq) return;
    
    //Atstatome deko kintamuosius į pradinius
    dq->size = 0;
    dq->front = 0;
    dq->rear = dq->capacity - 1;
}

//Grąžina deko duomenis atitinkantį tekstą, arba jo pradžią
char* toString(Deque* dq) {
    if (!dq) return NULL;
    
    //Išskiriame atmintį (max 256 simboliai)
    char* buffer = (char*)malloc(256 * sizeof(char)); 
    if (isEmpty(dq)) {
        strcpy(buffer, "[]");
        return buffer;
    }
    
    //Rodysime maksimaliai pirmus 10 elementų
    int limit = (dq->size > 10) ? 10 : dq->size;
    strcpy(buffer, "[");
    
    char temp[32];
    for (int i = 0; i < limit; i++) {
        int index = (dq->front + i) % dq->capacity;
        
        // Prijungiame elementą ir kablelį (jei tai ne paskutinis rodomas elementas)
        snprintf(temp, sizeof(temp), "%d%s", dq->data[index], (i == limit - 1) ? "" : ", ");
        strcat(buffer, temp);
    }
    
    if (dq->size > 10) {
        strcat(buffer, ", ...]"); // Nurodome, kad elementų yra daugiau
    } else {
        strcat(buffer, "]");
    }
    
    return buffer;
}