test.exe : test.c biginteger.h biginteger.o
	gcc -std=c99 -o test.exe test.c biginteger.o

biginteger.o : biginteger.c biginteger.h
	gcc -std=c99 -c biginteger.c