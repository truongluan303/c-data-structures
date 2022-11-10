CC = gcc

output: 	test.o vector.o
	$(CC) test.o vector.o -o test

test.o: 	test.c
	$(CC) -c test.c

vector.o:	vector.c
	$(CC) -c vector.c

runtest:
	make
	./test

memcheck:
	make
	valgrind ./test
