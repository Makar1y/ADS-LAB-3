PROGRAM = PriemimoKomisija
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
BIGINT_RENAMES = -Dcount=bi_count -DisEmpty=bi_isEmpty -DisFull=bi_isFull -DmakeEmpty=bi_makeEmpty -Dclone=bi_clone

$(PROGRAM): main.o params.o simulation.o deque.o BigInteger.o
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o params.o simulation.o deque.o BigInteger.o

main.o: main.c params.h simulation.h bigint_compat.h
	$(CC) $(CFLAGS) -c main.c

params.o: params.c params.h
	$(CC) $(CFLAGS) -c params.c

simulation.o: simulation.c simulation.h params.h bigint_compat.h 1beva2327/deque.h
	$(CC) $(CFLAGS) -c simulation.c

deque.o: 1beva2327/deque.c 1beva2327/deque.h
	$(CC) $(CFLAGS) -c -o deque.o 1beva2327/deque.c

BigInteger.o: 1vlsa2150/BigInteger.c 1vlsa2150/BigInteger.h
	$(CC) $(CFLAGS) $(BIGINT_RENAMES) -c -o BigInteger.o 1vlsa2150/BigInteger.c

clean:
	rm -f *.o $(PROGRAM)
