#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>

#define HASHMAP_SUCCESS     0
#define HASHMAP_FAILURE     -1
#define HASHMAP_TRUE        1
#define HASHMAP_FALSE       0


//===========================================================================//
//                               Structs                                     //
//===========================================================================//

typedef struct _hashmap hashmap;

typedef struct _hashmap_iterator hashmap_iterator;

//===========================================================================//
//                                Call Backs                                 //
//===========================================================================//

typedef unsigned long (*hashfunction) (const void* key, unsigned long seed);

typedef bool (*hashmap_keysequal) (const void* key1, const void* key2);

typedef void* (*hashmap_keycopy) (void* key);

typedef void (*hashmap_keyfree) (void* key);

typedef void* (*hashmap_valcopy) (void* value);

typedef void (*hashmap_valfree) (void* value);

//===========================================================================//
//                              Functions                                    //
//===========================================================================//

hashmap* hashmap_construct(hashfunction hash, hashmap_keysequal keq);

int hashmap_set_callbacks(hashmap* hmap,
                          hashmap_keycopy kcopy,
                          hashmap_keyfree kfree,
                          hashmap_valcopy vcopy,
                          hashmap_valfree vfree);

int hashmap_destroy(hashmap** hmap);

int hashmap_insert(hashmap* hmap, void* key, void* value);

int hashmap_contains(hashmap* hmap, void* key);

int hashmap_remove(hashmap* hmap, void* key);

int hashmap_get(hashmap* hmap, void* key, void** outvalue);

//===========================================================================//
//                                Enumeration                                //
//===========================================================================//

hashmap_iterator* hashmap_iter(hashmap* hmap);

int hashmap_iter_next(hashmap_iterator* it, void** outkey, void** outvalue);

int hashmap_iter_destroy(hashmap_iterator** it);

#endif // ifndef HASHMAP_H
