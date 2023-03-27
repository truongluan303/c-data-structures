#ifndef DEQUE_H
#define DEQUE_H

#define SUCCESS     0
#define FAILURE     -1
#define TRUE        1
#define FALSE       0

typedef struct _deque deque;

deque* deque_construct();

int deque_destroy(deque* d);

unsigned int deque_size(deque* d);

int deque_pushback(deque* d, void* value);

int deque_pushfront(deque* d, void* value);

void* deque_popback(deque* d);

void* deque_popfront(deque* d);

void* deque_front(deque* d);

void* deque_back(deque* d);

int deque_contains(deque* d, void* value);

int deque_remove(deque* d, void* value);

#endif
