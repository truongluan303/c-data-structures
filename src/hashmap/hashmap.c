#include "hashmap.h"

#include <limits.h>
#include <stdlib.h>
#include <time.h>

#define INITIAL_CAPACITY    23
#define MAX_CAPACITY        1<<31

//===========================================================================//
//                              Struct Definitions                           //
//===========================================================================//

typedef struct _callbacks {
    hashmap_keysequal   keq;    // Callback to check if keys equal.
    hashmap_keycopy     kcopy;  // Callback to copy a key.
    hashmap_keyfree     kfree;  // Callback to free a key.
    hashmap_valcopy     vcopy;  // Callback to copy a value.
    hashmap_valfree     vfree;  // Callback to free a value.
} callbacks;

typedef struct _node {
    void*           key;
    void*           value;
    struct _node*   next;
} node;

typedef struct _hashmap {
    hashfunction    hashfunc;   // The hash function.
    node**          heads;      // The bucket array.
    size_t          size;       // Number of key-value pairs in the map.
    size_t          capacity;   // Number of buckets.
    size_t          seed;       // The seed.
    callbacks       cbs;        // The callback functions
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

static size_t get_bucket_index(hashmap* hmap, void* key) {
    return hmap->hashfunc(key, hmap->seed) % hmap->capacity;
}

static void rehash(hashmap* hmap) {

}

static void deallocate_buckets(hashmap* hmap) {
    for (size_t i = 0; i < hmap->capacity; i++) {
        if (hmap->heads[i] == NULL) continue;

        node* curr = hmap->heads[i];
        node* next = NULL;
        do {
            hmap->cbs.kfree(curr->key);
            hmap->cbs.vfree(curr->value);
            next = curr->next;
            free(curr);
            curr = next;
        } while(curr != NULL);
    }
    free(hmap->heads);
}

//===========================================================================//
//                            Function Definitions                           //
//===========================================================================//

hashmap* hashmap_construct(hashfunction hash, hashmap_keysequal keq) {
    if (hash == NULL || keq == NULL) return NULL;

    hashmap* hmap   = (hashmap*)malloc(sizeof(*hmap));

    hmap->size      = 0;
    hmap->capacity  = INITIAL_CAPACITY;
    hmap->hashfunc  = hash;
    hmap->heads     = (node**)calloc(hmap->capacity, sizeof(*hmap->heads));

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

    deallocate_buckets(*hmap);
    free(*hmap);

    *hmap = NULL;
    return HASHMAP_SUCCESS;
}

int hashmap_set(hashmap* hmap, void* key, void* value) {
    if (hmap == NULL) return HASHMAP_FAILURE;

    rehash(hmap);

    size_t index = get_bucket_index(hmap, key);

    node* curr = hmap->heads[index];
    while (curr != NULL && !hmap->cbs.keq(curr->key, key)) {
        curr = curr->next;
    }

    if (curr == NULL) { // If key did not exist, add the key value pair
        node* n             = (node*)malloc(sizeof(*n));
        n->value            = value;
        n->key              = key;
        n->next             = hmap->heads[index];
        hmap->heads[index]  = n;
        hmap->size++;
    } else { // If key already exists, modify the value
        hmap->cbs.vfree(curr->value);
        curr->value = value;
    }
    return HASHMAP_SUCCESS;
}

int hashmap_contains(hashmap* hmap, void* key) {
    void* _;
    return (hashmap_get(hmap, key, &_) == HASHMAP_SUCCESS)
        ? HASHMAP_TRUE
        : HASHMAP_FALSE;
}

int hashmap_remove(hashmap* hmap, void* key) {
    if (hmap == NULL) return HASHMAP_FAILURE;

    size_t index = get_bucket_index(hmap, key);

    node* curr = hmap->heads[index];
    node* prev = NULL;
    while (curr != NULL && !hmap->cbs.keq(curr->key, key)) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) return HASHMAP_FALSE;

    if (prev == NULL) { // if the node to be deleted is the head of the list
        hmap->heads[index] = curr->next;
    } else {
        prev->next = curr->next;
    }

    // free the deleted node
    hmap->cbs.kfree(curr->key);
    hmap->cbs.vfree(curr->value);
    free(curr);

    hmap->size--;
    return HASHMAP_TRUE;
}

int hashmap_get(hashmap* hmap, void* key, void** outvalue) {
    if (hmap == NULL) return HASHMAP_FAILURE;

    size_t index = get_bucket_index(hmap, key);

    node* tmp = hmap->heads[index];
    while (tmp != NULL && !hmap->cbs.keq(tmp->key, key)) tmp = tmp->next;
    if (tmp == NULL) return HASHMAP_FAILURE;

    *outvalue = tmp->value;

    return HASHMAP_SUCCESS;
}

unsigned long hashmap_size(hashmap* hmap) {
    return hmap->size;
}

int hashmap_clear(hashmap* hmap) {
    if (hmap == NULL) return HASHMAP_FAILURE;

    deallocate_buckets(hmap);

    hmap->size      = 0;
    hmap->capacity  = INITIAL_CAPACITY;
    hmap->heads     = (node**)calloc(hmap->capacity, sizeof(*hmap->heads));

    return HASHMAP_SUCCESS;
}

void** hashmap_keys(hashmap* hmap) {
    if (hmap == NULL || hmap->size == 0) return NULL;

    void** result   = calloc(hmap->size, sizeof(void*));
    size_t i        = 0;

    for (size_t bucket_idx = 0; bucket_idx < hmap->capacity; bucket_idx++) {
        node* curr = hmap->heads[bucket_idx];
        while (curr != NULL) {
            result[i++] = curr->key;
            curr = curr->next;
        }
    }
    return result;
}

void** hashmap_values(hashmap* hmap) {
    if (hmap == NULL || hmap->size == 0) return NULL;

    void** result   = calloc(hmap->size, sizeof(void*));
    size_t i        = 0;

    for (size_t bucket_idx = 0; bucket_idx < hmap->capacity; bucket_idx++) {
        node* curr = hmap->heads[bucket_idx];
        while (curr != NULL) {
            result[i++] = curr->value;
            curr = curr->next;
        }
    }
    return result;
}

hashmap_iterator* hashmap_iter(hashmap* hmap) {
    if (hmap == NULL) return NULL;

    hashmap_iterator* it    = malloc(sizeof(*it));
    it->hmap                = hmap;
    return it;
}

int hashmap_iter_next(hashmap_iterator* it, void** outkey, void** outvalue) {
    if (it == NULL || it->idx >= it->hmap->capacity) return HASHMAP_FALSE;

    if (it->cur == NULL) {
        while (it->idx < it->hmap->capacity &&
               it->hmap->heads[it->idx] == NULL) {
            it->idx++;
        }
        if (it->idx >= it->hmap->capacity) return HASHMAP_FALSE;

        it->cur = it->hmap->heads[it->idx];
        it->idx++;
    }
    *outkey     = it->cur->key;
    *outvalue   = it->cur->value;
    it->cur     = it->cur->next;

    return HASHMAP_TRUE;
}

int hashmap_iter_destroy(hashmap_iterator** it) {
    if (*it == NULL) return HASHMAP_FAILURE;

    free(*it);
    *it = NULL;
    return HASHMAP_SUCCESS;
}
