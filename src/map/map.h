#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <stdlib.h>

#define MAP_SUCCESS     0
#define MAP_FAILURE     -1
#define MAP_TRUE        1
#define MAP_FALSE       0

typedef struct _map map;

map* map_construct();

int map_destroy(map** m);

int map_set(map* m, void* key, void* value);

void* map_get(map* m, void* key);

int map_del(map* m, void* key);

int map_contains_key(map* m, void* key);

int map_contains_value(map* m, void* value);

int map_sort(map* m,
             int(*keysort_callback)(void* lkey, void* rkey) = NULL,
             int(*valsort_callback)(void* lval, void* rval) = NULL);

void** map_keys(map* m);

void** map_values(map* m);

#endif
