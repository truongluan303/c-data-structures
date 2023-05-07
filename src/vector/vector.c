#include "vector.h"


//===========================================================================//
//                          Helper Functions Prototypes                      //
//===========================================================================//

int vector_resize(vector* v, size_t new_capacity);


//===========================================================================//
//                          Vector Struct Definition                         //
//===========================================================================//
typedef struct _vector {
    void**  buf;            /* the array */
    size_t  capacity;       /* the capacity of the array */
    size_t  count;          /* number of elements currently in the array */
}
vector;


//===========================================================================//
//                          Vector Functions Definitions                     //
//===========================================================================//

vector* vector_construct() {
    vector* v       = malloc(sizeof(v));
    v->capacity     = MIN_CAPACITY;
    v->count        = 0;
    v->buf          = malloc(sizeof(void*) * v->capacity);

    return v;
}


size_t vector_size(vector* v) {
    return v->count;
}


int vector_destroy(vector** v) {
    if (v == NULL) return FAILURE;

    free((*v)->buf);
    (*v)->buf = NULL;
    free(*v);
    *v = NULL;
    return SUCCESS;
}


void* vector_get(vector* v, size_t index) {
    if (v == NULL) return NULL;
    if (index < v->count) return v->buf[index];
    return NULL;
}


int vector_set(vector* v, size_t index, void* data) {
    if (v == NULL) return FAILURE;

    if (index < v->count) {
        v->buf[index] = data;
        return SUCCESS;
    }
    return FAILURE;
}


int vector_pushback(vector* v, void* data) {
    if (v->count == v->capacity) vector_resize(v, v->capacity * 2);
    return vector_set(v, v->count++, data);
}


int vector_pushfront(vector* v, void* data) {
    if (v == NULL) return FAILURE;
    if (v->count == v->capacity) vector_resize(v, v->capacity * 2);

    // shift the elements to make room at the front
    for (size_t i = v->count; i > 0; i--) v->buf[i] = v->buf[i - 1];

    vector_set(v, 0, data);
    v->count++;
    return SUCCESS;
}


void* vector_popback(vector* v) {
    return vector_delete(v, v->count - 1);
}


void* vector_popfront(vector* v) {
    return vector_delete(v, 0);
}


void* vector_delete(vector* v, size_t index) {
    if (v == NULL || index >= v->count) return NULL;

    void* deleted_value = v->buf[index];
    v->buf[index] = NULL;

    // shift the elements to fill the gap
    for (size_t i = index; i < v->count - 1; i++) {
        v->buf[i]       = v->buf[i + 1];
        v->buf[i + 1]   = NULL;
    }
    v->count--;

    if (v->count > 0 && v->count == v->capacity / 4) {
        size_t new_capacity = v->count / 2;
        if (new_capacity >= MIN_CAPACITY) vector_resize(v, new_capacity);
    }
    return deleted_value;
}


BOOLEAN vector_contains(vector* v, void* data) {
    return vector_find(v, data) == NOT_EXIST ? FALSE : TRUE;
}


int vector_find(vector* v, void* data) {
    for (size_t i = 0; i < v->count; i++) {
        if (vector_get(v, i) == data) return i;
    }
    return NOT_EXIST;
}


int vector_swap(vector* v, size_t lidx, size_t ridx) {
    if (v == NULL || lidx >= v->count || ridx >= v->count) return FAILURE;

    void* temp      = v->buf[lidx];
    v->buf[lidx]    = v->buf[ridx];
    v->buf[ridx]    = temp;
}


void** vector_to_arr(vector* v) {
    void** result = calloc(v->count, sizeof(void*));

    for (size_t i = 0; i < v->count; i++) {
        result[i] = v->buf[i];
    }
    return result;
}


void vector_clear(vector* v) {
    free(v->buf);
    v->buf          = malloc(sizeof(void*) * MIN_CAPACITY);
    v->count        = 0;
}


//===========================================================================//
//                          Helper Functions Definitions                     //
//===========================================================================//

int vector_resize(vector* v, size_t new_capacity) {
    if (v == NULL) return FAILURE;

    int     status  = FAILURE;
    void**  buf     = realloc(v->buf, sizeof(void*) * new_capacity);

    if (buf) {
        v->buf      = buf;
        v->capacity = new_capacity;
        status      = SUCCESS;
    }
    return status;
}
