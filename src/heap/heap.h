#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

#define HEAP_SUCCESS    0
#define HEAP_FAILURE    -1
#define HEAP_TRUE       1
#define HEAP_FALSE      0

typedef struct _heap heap;

heap* heap_construct(bool ismin);

int heap_destroy(heap** h);

unsigned int heap_size(heap* h);

int heap_empty(heap* h);

int heap_push(heap* h, void* data);

void* heap_pop(heap* h);

int heap_clear(heap* h);

#endif
