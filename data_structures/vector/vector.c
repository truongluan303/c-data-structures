#include "vector.h"


//===========================================================================//
//                          Helper Functions Prototypes                      //
//===========================================================================//

int     vector_resize(vector* v, size_t new_capacity);


//===========================================================================//
//                          Vector Functions Definitions                     //
//===========================================================================//

int construct_vector(v)
    vector*         v;
{
    v->capacity     = MIN_CAPACITY;
    v->count        = 0;
    v->buf          = malloc(sizeof(void*) * v->capacity);

    return SUCCESS;
}


void* vector_get(v, index)
    vector*         v;
    size_t          index;
{
    if (v == NULL) return NULL;
    if (index < v->count) return v->buf[index];
    return NULL;
}


int vector_set(v, index, data)
    vector*         v;
    size_t          index;
    void*           data;
{
    if (v == NULL) return FAILURE;

    if (index < v->count)
    {
        v->buf[index] = data;
        return SUCCESS;
    }
    return FAILURE;
}


int vector_pushback(v, data)
    vector*         v;
    void*           data;
{
    if (v->count == v->capacity) vector_resize(v, v->capacity * 2);
    return vector_set(v, v->count++, data);
}


int vector_pushfront(v, data)
    vector*         v;
    void*           data;
{
    if (v == NULL) return FAILURE;

    if (v->count == v->capacity) vector_resize(v, v->capacity * 2);

    // shift the elements to make room at the front
    for (size_t i = v->count; i > 0; i--) v->buf[i] = v->buf[i - 1];

    vector_set(v, 0, data);
    v->count++;
    return SUCCESS;
}


void* vector_popback(v)
    vector*         v;
{
    return vector_delete(v, v->count - 1);
}


void* vector_popfront(v)
    vector*         v;
{
    return vector_delete(v, 0);
}


void* vector_delete(v, index)
    vector*         v;
    size_t          index;
{
    if (v == NULL || index >= v->count) return NULL;

    void* deleted_value = v->buf[index];
    v->buf[index] = NULL;

    // shift the elements to fill the gap
    for (size_t i = index; i < v->count - 1; i++)
    {
        v->buf[i]       = v->buf[i + 1];
        v->buf[i + 1]   = NULL;
    }
    v->count--;

    if (v->count > 0 && v->count == v->capacity / 4)
    {
        size_t new_capacity = v->count / 2;
        if (new_capacity >= MIN_CAPACITY) vector_resize(v, new_capacity);
    }
    return deleted_value;
}


BOOLEAN vector_contains(v, data)
    vector*         v;
    void*           data;
{
    if (vector_find(v, data) == NOT_EXIST) return FALSE;
    return TRUE;
}


int vector_find(v, data)
    vector*         v;
    void*           data;
{
    for (size_t i = 0; i < v->count; i++) {
        if (vector_get(v, i) == data) return i;
    }
    return NOT_EXIST;
}


void vector_clear(v)
    vector*         v;
{
    free(v->buf);
    v->buf      = malloc(sizeof(void*) * MIN_CAPACITY);
    v->count    = 0;
}


int vector_free(v)
    vector*         v;
{
    if (v == NULL) return FAILURE;

    free(v->buf);
    v->buf = NULL;
    return SUCCESS;
}


//===========================================================================//
//                          Helper Functions Definitions                     //
//===========================================================================//

int vector_resize(v, new_capacity)
    vector*         v;
    size_t          new_capacity;
{
    if (v == NULL) return FAILURE;

    int     status  = FAILURE;
    void**  buf     = realloc(v->buf, sizeof(void*) * new_capacity);

    if (buf)
    {
        v->buf      = buf;
        v->capacity = new_capacity;
        status      = SUCCESS;
    }
    return status;
}
