DEQUE				= deque-test
SINGLY_LINKED_LIST	= singly_linked_list-test
TRIE				= trie-test
VECTOR 				= vector-test

CC 					= gcc
CFLAGS 				= -g -w

RM 					= rm
RMFLAGS 			= -f

LIBS 				= -ldata_structures

TESTER_SRC			= tester/tester.c

# all target. for building the entire application.
# - optional, because the first target in a Makefile is assumed to be the
#   'all' target.
# - marked phony, because it's just a recipe and not a file
.PHONY: all
all: $(DEQUE) $(SINGLY_LINKED_LIST) $(TRIE) $(VECTOR)

$(DEQUE): deque-test.o
	$(CC) $(CFLAGS) -o $@ $^ $(TESTER_SRC) $(LIBS)

$(SINGLY_LINKED_LIST): singly_linked_list-test.o
	$(CC) $(CFLAGS) -o $@ $^ $(TESTER_SRC) $(LIBS)

$(TRIE): trie-test.o
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
# run test for trie
test-trie:
	make clean
	make
	./$(TRIE)
# run test for singly linked list
test-singly-linked-list:
	make clean
	make
	./$(SINGLY_LINKED_LIST)
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
