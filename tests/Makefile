DEQUE		= deque-test
MAP			= map-test
VECTOR 		= vector-test

CC 			= gcc
CFLAGS 		= -g -Wall

RM 			= rm
RMFLAGS 	= -f

LIBS 		= -ldata_structures

TESTER_SRC	= tester/tester.c

# all target. for building the entire application.
# - optional, because the first target in a Makefile is assumed to be the
#   'all' target.
# - marked phony, because it's just a recipe and not a file
.PHONY: all
all: $(VECTOR) $(DEQUE)

$(DEQUE): deque-test.o
	$(CC) $(CFLAGS) -o $@ $^ $(TESTER_SRC) $(LIBS)
$(MAP): map-test.o
	$(CC) $(CFLAGS) -o $@ $^ $(TESTER_SRC) $(LIBS)
$(VECTOR): vector-test.o
	$(CC) $(CFLAGS) -o $@ $^ $(TESTER_SRC) $(LIBS)

%.o: %c
	$(CC) $(CFLAGS) -c $< -o $@

# run test for deque
test-deque:
	make clean
	make
	./$(DEQUE)
# run test for map
test-map:
	make clean
	make
	./$(MAP)
# run test for vector
test-vector:
	make clean
	make
	./$(VECTOR)

# clean target.
# - removes the .o object files and the project's executable
# - marked phony, because it's just a recipe and not a file
.PHONY: clean
clean:
	$(RM) $(RMFLAGS) *.o $(PROJECT)
