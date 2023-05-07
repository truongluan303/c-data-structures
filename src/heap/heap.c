#include "heap.h"

#include <stdlib.h>
#include <string.h>

#include <vector.h>


//===========================================================================//
//                         Heap Struct Implementation                        //
//===========================================================================//
typedef struct _heap {
    vector* arr;
    bool ismin;
    int (*comparator)(const void* val1, const void* val2);
} heap;


//===========================================================================//
//                            Helper Functions                               //
//===========================================================================//


void heapify(heap* h, size_t idx) {
    size_t target   = idx;
    size_t lidx     = idx * 2 + 1;
    size_t ridx     = idx * 2 + 2;

    void* targetval = vector_get(h->arr, target);
    void* lchildval = vector_get(h->arr, lidx);
    void* rchildval = vector_get(h->arr, ridx);

    // Find the min element if min heap or max element if max heap
    if (h->comparator(lchildval, targetval) == (h->ismin ? -1 : 1)) {
        target      = lidx;
        targetval   = lchildval;
    }
    if (h->comparator(rchildval, targetval) == (h->ismin ? -1 : 1)) {
        target      = ridx;
        targetval   = rchildval;
    }
    // Swap the elements at target and current index
    vector_swap(h->arr, target, idx);
}


//===========================================================================//
//                        Heap Functions Implementation                      //
//===========================================================================//


heap* heap_construct(bool ismin,
                     int (*comparator)(const void* val1, const void* val2)) {
    heap* h         = malloc(sizeof(h));
    h->arr          = vector_construct();
    h->ismin        = ismin;
    h->comparator   = comparator;
    return h;
}


int heap_destroy(heap** h) {
    if (h == NULL) return HEAP_FAILURE;

    vector_destroy(&(*h)->arr);
    free(*h);
    *h = NULL;
    return HEAP_SUCCESS;
}


unsigned int heap_size(heap* h) {
    return (h == NULL) ? 0 : vector_size(h->arr);
}


int heap_empty(heap* h) {
    if (h == NULL) return HEAP_FAILURE;
    return vector_size(h->arr) == 0 ? HEAP_TRUE : HEAP_FALSE;
}


int heap_push(heap* h, void* data) {
    if (h == NULL) return HEAP_FAILURE;

    if (vector_pushback(h->arr, data) == 1) return HEAP_FAILURE;

    for (int i = (vector_size(h->arr) - 1) / 2 - 1; i >= 0; i--) heapify(h, i);

    return HEAP_SUCCESS;
}


void* heap_pop(heap* h) {
    if (h == NULL || vector_size(h->arr) == 0) return NULL;

    void* headval = vector_get(h->arr, 0);
    vector_set(h->arr, 0, vector_popback(h->arr));

    size_t size = vector_size(h->arr);
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(h, i);
    }
    return headval;
}


int heap_contains(heap* h, void* value) {
    return h == NULL ? HEAP_FAILURE : (int)vector_contains(h->arr, value);
}


void* heap_top(heap* h) {
    return (h == NULL || vector_size(h->arr) == 0)
        ? NULL
        : vector_get(h->arr, 0);
}


void** heap_nlargest(heap* h, unsigned int n) {
    if (h == NULL || n > heap_size(h) || n == 0) return NULL;

    void** result = calloc(n, sizeof(void*));

    for (size_t i = 0; i < n; i++) {
        result[i] = !h->ismin ? vector_get(h->arr, i)
                              : vector_get(h->arr, n - i - 1);
    }
    return result;
}


void** heap_nsmallest(heap* h, unsigned int n) {
    if (h == NULL || n > heap_size(h) || n == 0) return NULL;

    void** result = calloc(n, sizeof(void*));

    for (size_t i = 0; i < n; i++) {
        result[i] = h->ismin ? vector_get(h->arr, i)
                             : vector_get(h->arr, n - i - 1);
    }
    return result;
}


void** heap_to_arr(heap* h) {
    return (h == NULL || vector_size(h->arr) == 0)
        ? NULL
        : vector_to_arr(h->arr);
}


int heap_clear(heap* h) {
    if (h == NULL) return HEAP_FAILURE;

    vector_clear(h->arr);
    return HEAP_SUCCESS;
}


int int_comparator(const void* val1, const void* val2) {
    int ival1 = *(int*)(&val1);
    int ival2 = *(int*)(&val2);

    if (ival1 < ival2)          return -1;
    else if (ival1 == ival2)    return 0;
    else                        return 1;
}


int str_comparator(const void* val1, const void* val2) {
    int cmpres = strcmp(*(char**)(&val1), *(char**)(&val2));
    return cmpres == 0 ? 0 : (cmpres < 0 ? -1 : 1);
}
