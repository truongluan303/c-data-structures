output: 	test.o vector.o
	gcc test.o vector.o -o test

test.o: 	test.c
	gcc -c test.c

vector.o:	vector.c
	gcc -c vector.c

runtest:
	make
	./test

memcheck:
	make
	valgrind ./test

clean:
	rm *.o test