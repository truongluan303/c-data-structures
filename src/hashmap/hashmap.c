#include "hashmap.h"

#include <limits.h>
#include <stdlib.h>
#include <time.h>

#define INITIAL_CAPACITY    32
#define MAX_CAPACITY        1<<31

//===========================================================================//
//                              Struct Definitions                           //
//===========================================================================//

typedef struct _callbacks {
    hashmap_keysequal   keq;
    hashmap_keycopy     kcopy;
    hashmap_keyfree     kfree;
    hashmap_valcopy     vcopy;
    hashmap_valfree     vfree;
} callbacks;

typedef struct _node {
    void*   key;
    void*   value;
    node*   next;
} node;

typedef struct _hashmap {
    hashfunction    hashfunc;
    node**          heads;
    size_t          size;
    size_t          capacity;
    size_t          seed;
    callbacks       cbs;
} hashmap;

typedef struct _hashmap_iterator {
    hashmap*    hmap;
    node*       cur;
    size_t      idx;
} hashmap_iterator;


//===========================================================================//
//                         Private Helper Functions                          //
//===========================================================================//

static void* default_copy(void* x) { return x; }

static void default_free(void* v) { return; }

static void rehash(hashmap* hmap) {
    if (hmap->size + 1 < (size_t)(hmap->capacity * 0.75) ||
        hmap->capacity >= MAX_CAPACITY) return;

    size_t capacity = hmap->capacity;
    node** heads    = hmap->heads;

    hmap->capacity  <<= 1;
    hmap->heads     = realloc(hmap->heads, sizeof(void*) * hmap->capacity);
}

static void add_to_bucket(hashmap* hmap, void* key, void* val, bool isrehash) {
}

//===========================================================================//
//                            Function Definitions                           //
//===========================================================================//

hashmap* hashmap_construct(hashfunction hash, hashmap_keysequal keq) {
    if (hash == NULL || keq == NULL) return NULL;

    hashmap* hmap   = malloc(sizeof(*hmap));

    hmap->size      = 0;
    hmap->capacity  = INITIAL_CAPACITY;
    hmap->hashfunc  = hash;
    hmap->heads     = calloc(hmap->capacity, sizeof(*hmap->heads));

    hmap->cbs.keq   = keq;
    hmap->cbs.kcopy = default_copy;
    hmap->cbs.vcopy = default_copy;
    hmap->cbs.kfree = default_free;
    hmap->cbs.vfree = default_free;

    hmap->seed      = (size_t)time(NULL);
    hmap->seed      ^= ((size_t)hashmap_construct << 16) | (size_t)hmap;
    hmap->seed      ^= (size_t)&hmap->seed;

    return hmap;
}

int hashmap_set_callbacks(hashmap* hmap,
                          hashmap_keycopy kcopy,
                          hashmap_keyfree kfree,
                          hashmap_valcopy vcopy,
                          hashmap_valfree vfree) {
    if (hmap == NULL) return HASHMAP_FAILURE;

    hmap->cbs.kcopy = kcopy;
    hmap->cbs.kfree = kfree;
    hmap->cbs.vcopy = vcopy;
    hmap->cbs.vfree = vfree;
    return HASHMAP_SUCCESS;
}

int hashmap_destroy(hashmap** hmap) {
    if (*hmap == NULL) return HASHMAP_FAILURE;

    for (size_t i = 0; i < (*hmap)->capacity; i++) {
        if ((*hmap)->heads[i] == NULL ||
            (*hmap)->heads[i]->key == NULL) continue;

        node* curr = (*hmap)->heads[i];
        node* next = NULL;
        do {
            (*hmap)->cbs.kfree(curr->key);
            (*hmap)->cbs.vfree(curr->value);
            next = curr->next;
            free(curr);
            curr = next;
        } while(curr != NULL);
    }
    free((*hmap)->heads);
    free(*hmap);

    *hmap = NULL;
    return HASHMAP_SUCCESS;
}

int hashmap_insert(hashmap* hmap, void* key, void* value) {
    if (hmap == NULL || key == NULL) return HASHMAP_FAILURE;

    rehash(hmap);

}

int hashmap_contains(hashmap* hmap, void* key);

int hashmap_remove(hashmap* hmap, void* key);

int hashmap_get(hashmap* hmap, void* key, void** outvalue);
