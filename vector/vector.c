#include "vector.h"
#include <string.h>

/*===========================================================================*/
/* construct_vector                                                          */
/*===========================================================================*/
void construct_vector(v, data_size)

    vector*         v;
    size_t          data_size;

{
    v->capacity     = MIN_CAPACITY;
    v->count        = 0;
    v->data_size    = data_size;
    v->buf          = malloc(data_size * v->capacity);
}

/*===========================================================================*/
/* get                                                                       */
/*===========================================================================*/
void* get(v, index)

    vector*         v;
    size_t          index;

{
    return v->buf + index;
}

/*===========================================================================*/
/* set                                                                       */
/*===========================================================================*/
void set(v, index, data)

    vector*         v;
    size_t          index;
    const void*     data;

{
    size_t loc = index * v->data_size;
    memcpy(v->buf + loc, data, v->data_size);
}

/*===========================================================================*/
/* append                                                                    */
/*===========================================================================*/
void append(v, data)

    vector*         v;
    const void*     data;

{
    // reallocate more memory if the capacity is reached
    if (v->count == v->capacity) {
        printf("expanding...\n");
        v->capacity = v->capacity * 2;
        v->buf      = realloc(v->buf, sizeof(*v->buf) * v->capacity);
    }
    printf("adding %d to array...\n", data);
    set(v, v->count++, data);
}

/*===========================================================================*/
/* popback                                                                   */
/*===========================================================================*/
void* popback(v)

    vector*         v;

{
    void* result = get(v, --v->count);
    return result;
}

/*===========================================================================*/
/* contains                                                                  */
/*===========================================================================*/
BOOLEAN contains(v, data)

    vector*         v;
    const void*     data;

{
    if (find(v, data) == NOT_EXIST) {
        return FALSE;
    }
    return TRUE;
}

/*===========================================================================*/
/* find                                                                      */
/*===========================================================================*/
int find(v, data)

    vector*         v;
    const void*     data;

{
    for (size_t i = 0; i < v->count; i++) {
        if (get(v, i) == data) {
            return i;
        }
    }
    return NOT_EXIST;
}