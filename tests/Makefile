VECTOR = vector-test

CC = gcc
CFLAGS = -g -Wall

RM = rm
RMFLAGS = -f

LIBS = -ldata_structures

# all target. for building the entire application.
# - optional, because the first target in a Makefile is assumed to be the
#   'all' target.
# - marked phony, because it's just a recipe and not a file
.PHONY: all
all: $(VECTOR)

$(VECTOR): vector-test.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %c
	$(CC) $(CFLAGS) -c $< -o $@

# run test for vector
test-vector:
	make
	./$(VECTOR)

# clean target.
# - removes the .o object files and the project's executable
# - marked phony, because it's just a recipe and not a file
.PHONY: clean
clean:
	$(RM) $(RMFLAGS) *.o $(PROJECT)
