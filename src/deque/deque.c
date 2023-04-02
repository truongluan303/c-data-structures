#include "deque.h"

#include <stdlib.h>


typedef unsigned int uint;

static const unsigned short MIN_CAPACITY    = 32;
static const short INITIAL_FRONT_IDX        = -1;
static const short INITIAL_REAR_IDX         = 0;


typedef struct _deque {
    void**      buf;            // The array
    uint        count;          // The array's current number of items
    uint        capacity;       // The array's maximum capacity
    int         fidx;           // Front index
    int         ridx;           // Rear index
} deque;


int deque_resize(deque* d, uint new_capacity) {
    if (d == NULL) return DEQUE_FAILURE;

    void** current_data = malloc(sizeof(void*) * d->count);
    uint bufidx         = d->fidx;
    for (uint i = 0; i < d->count; i++) {
        current_data[i] = d->buf[bufidx];
        if (++bufidx == d->capacity)  bufidx = 0;
    }

    void** buf = realloc(d->buf, sizeof(void*) * new_capacity);
    if (!buf) return DEQUE_FAILURE;

    for (uint i = 0; i < d->count; i++) {
        buf[i] = current_data[i];
    }
    free(current_data);

    d->buf      = buf;
    d->capacity = new_capacity;
    d->fidx     = 0;
    d->ridx     = d->count - 1;
    return DEQUE_SUCCESS;
}


deque* deque_construct() {
    deque* d        = malloc(sizeof(*d));
    d->capacity     = MIN_CAPACITY;
    d->count        = 0;
    d->buf          = malloc(sizeof(void*) * d->capacity);
    d->fidx         = INITIAL_FRONT_IDX;
    d->ridx         = INITIAL_REAR_IDX;

    return d->buf != NULL ? d : NULL;
}


int deque_destroy(deque** d) {
    if (d == NULL) return DEQUE_FAILURE;
    free((*d)->buf);
    (*d)->buf = NULL;
    free(*d);
    *d = NULL;
    return DEQUE_SUCCESS;
}


unsigned int deque_size(deque* d) {
    return d->count;
}


int deque_pushback(deque* d, void* value) {
    if (d == NULL) return DEQUE_FAILURE;
    if (d->count == d->capacity) deque_resize(d, d->capacity * 2);

    if (d->count == 0) {
        d->fidx = 0;
    }
    else if (++d->ridx == d->capacity) {
        d->ridx = 0;
    }
    d->buf[d->ridx] = value;
    d->count++;
    return DEQUE_SUCCESS;
}


int deque_pushfront(deque* d, void* value) {
    if (d == NULL) return DEQUE_FAILURE;
    if (d->count == d->capacity) deque_resize(d, d->capacity * 2);

    if (d->count == 0) {
        d->fidx = 0;
    }
    else if (--d->fidx == -1) {
        d->fidx = d->capacity - 1;
    }
    d->buf[d->fidx] = value;
    d->count++;
    return DEQUE_SUCCESS;
}


void* deque_popback(deque* d) {
    if (d == NULL || d->count == 0) return NULL;

    void* result = deque_back(d);

    d->buf[d->ridx] = NULL;
    d->count--;
    if (d->fidx == d->ridx) {
        d->fidx = INITIAL_FRONT_IDX;
        d->ridx = INITIAL_REAR_IDX;
    }
    else if (--d->ridx == -1) {
        d->ridx = d->capacity - 1;
    }
    if (d->count == d->capacity / 4) deque_resize(d, d->capacity / 2);
    return result;
}


void* deque_popfront(deque* d) {
    if (d == NULL || d->count == 0) return NULL;

    void* result = deque_front(d);

    d->buf[d->fidx] = NULL;
    d->count--;
    if (d->fidx == d->ridx) { // if the removed element is the only element in deque.
        d->fidx = INITIAL_FRONT_IDX;
        d->ridx = INITIAL_REAR_IDX;
    }
    else if (++d->fidx == d->capacity) {
        d->fidx = 0;
    }
    if (d->count == d->capacity / 4) deque_resize(d, d->capacity / 2);
    return result;
}


void* deque_front(deque* d) {
    return (d != NULL && d->count > 0) ? d->buf[d->fidx] : NULL;
}


void* deque_back(deque* d) {
    return (d != NULL && d->count > 0) ? d->buf[d->ridx] : NULL;
}


int deque_contains(deque* d, void* value) {
    if (d == NULL) return DEQUE_FAILURE;

    uint idx = d->fidx;

    for (uint _ = 0; _ < d->count; _++) {
        if (d->buf[idx] == value) return DEQUE_TRUE;
        if (++idx == d->capacity) idx = 0;
    }
    return DEQUE_FALSE;
}
