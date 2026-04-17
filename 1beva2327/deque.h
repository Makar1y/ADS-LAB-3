#ifndef DEQUE_H
#define DEQUE_H

typedef struct {
    int *data;      
    int capacity;   
    int size;       
    int front;      
    int rear;       
} Deque;

Deque* createDeque(int capacity);
int isEmpty(Deque* dq);
int isFull(Deque* dq);
void insertFront(Deque* dq, int value);
int removeFront(Deque* dq);
void insertBack(Deque* dq, int value);
int removeBack(Deque* dq);
int getFront(Deque* dq);
int getBack(Deque* dq);
int getCount(Deque* dq);
void destroyDeque(Deque* dq);
Deque* clone(Deque* dq);
void makeEmpty(Deque* dq);
char* toString(Deque* dq);

#endif