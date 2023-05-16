#ifndef HASHMAP_H
#define HASHMAP_H

#define HASHMAP_SUCCESS     0
#define HASHMAP_FAILURE     -1
#define HASHMAP_TRUE        1
#define HASHMAP_FALSE       0

typedef unsigned long (hashfunction) (const char*, unsigned long);

typedef struct _hashmap hashmap;

hashmap* hashmap_construct(unsigned int size, hashfunction* hash);

int hashmap_destroy(hashmap** hmap);

int hashmap_insert(hashmap* hmap, const char* key, void* value);

int hashmap_contains(hashmap* hmap, const char* key);

int hashmap_remove(hashmap* hmap, const char* key);

int hashmap_get(hashmap* hmap, const char* key, void** value);

#endif
