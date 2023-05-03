#include "heap.h"

#include <stdlib.h>


typedef struct _node {
    void*   value;
    node*   left;
    node*   right;
} node;


typedef struct _heap {
    node*   head;
    size_t  count;
} heap;


void free_tree(node* head) {
    if (head == NULL) return;

    free_tree(head->left);
    free_tree(head->right);

    free(head);
}


heap* heap_construct(bool ismin) {
    heap* h     = malloc(sizeof(h));
    h->head     = 0;
    h->count    = 0;
    return h;
}


int heap_destroy(heap** h) {
    if (h == NULL) return HEAP_FAILURE;

    free_tree((*h)->head);
    free(*h);
    *h = NULL;
    return HEAP_SUCCESS;
}


unsigned int heap_size(heap* h) {
    if (h == NULL) return 0;
    return h->count;
}


int heap_empty(heap* h) {
    if (h == NULL) return HEAP_FAILURE;
    return h->count == 0 ? HEAP_TRUE : HEAP_FALSE;
}


int heap_clear(heap* h) {
    if (h == NULL) return HEAP_FAILURE;

    free_tree(h->head);
    h->head = NULL;
    h->count = 0;
    return HEAP_SUCCESS;
}
