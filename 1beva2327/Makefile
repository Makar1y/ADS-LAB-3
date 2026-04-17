main.exe: main.c deque.h deque.o
	gcc -std=c99 -Wall -o main.exe main.c deque.o

deque.o: deque.c deque.h
	gcc -c -std=c99 -Wall deque.c

clean:
	rm -f *.o main.exe