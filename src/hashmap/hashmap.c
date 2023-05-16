#include "hashmap.h"

#include <stdlib.h>


typedef struct _entry {
    char*           key;
    unsigned int    keylen;
    void*           value;
    struct entry*   next;
} entry;


typedef struct _hashmap {
    unsigned int    size;
    hashfunction*   hash;
    entry**         elements;
} hashmap;


static unsigned int hashmap_index(hashmap* hmap, const char* key) {
    return hmap->hash(key, strlen(key)) % hmap->size;
}

hashmap* hashmap_construct(unsigned int size, hashfunction* hash) {
    hashmap* hmap   = malloc(sizeof(*hmap));
    hmap->size      = size;
    hmap->hash      = hash;
    hmap->elements  = calloc(sizeof(entry*), hmap->size);
    return hmap;
}

int hashmap_destroy(hashmap** hmap) {
    if (*hmap == NULL) return HASHMAP_FAILURE;

    free((*hmap)->elements);
    free(*hmap);
    *hmap = NULL;

    return HASHMAP_SUCCESS;
}

int hashmap_insert(hashmap* hmap, const char* key, void* value) {
    if (hmap == NULL || key == NULL) return HASHMAP_FAILURE;

    unsigned int index = hashmap_index(hmap, key);

    if (hashmap_contains(hmap, key)) return HASHMAP_FAILURE;

    // create a new entry
    entry* e    = malloc(sizeof(*e));
    e->value    = value;
    e->key      = malloc(strlen(key) + 1);
    strcpy(e->key, key);

    // insert entry
    e->next                 = hmap->elements[index];
    hmap->elements[index]   = e;

    return HASHMAP_SUCCESS;
}

int hashmap_contains(hashmap* hmap, const char* key) {
    if (hmap == NULL || key == NULL) return HASHMAP_FAILURE;

    void* _;
    return hashmap_get(hmap, key, &_) != NULL ? HASHMAP_TRUE : HASHMAP_FALSE;
}

int hashmap_remove(hashmap* hmap, const char* key) {
    if (hmap == NULL || key == NULL) return HASHMAP_FAILURE;

    unsigned int index = hashmap_index(hmap, key);

    entry* tmp  = hmap->elements[index];
    entry* prev = NULL;
    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        prev    = tmp;
        tmp     = tmp->next;
    }
    if (tmp == NULL) return HASHMAP_FAILURE;

    if (prev == NULL) { // if the to-be-remove node is the head of the list
        hmap->elements[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    return HASHMAP_SUCCESS;
}

int hashmap_get(hashmap* hmap, const char* key, void** value) {
    if (hmap == NULL || key == NULL) return HASHMAP_FAILURE;

    unsigned int index = hashmap_index(hmap, key);

    entry* tmp = hmap->elements[index];
    while (tmp != NULL && strcmp(tmp->key, key) != 0) {
        tmp = tmp->next;
    }
    if (tmp == NULL) return HASHMAP_FAILURE;

    *value = tmp->value;
    return HASHMAP_SUCCESS;
}
