#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define MIN_CAPACITY        32
#define NOT_EXIST           -1

/******************************************************************************
 * @brief       Represents a boolean state
 *****************************************************************************/
typedef enum {
    TRUE,
    FALSE
}
BOOLEAN;

/******************************************************************************
 * @brief       Represents the vector. Containing an array, the array's
 *              capacity, the actual elements count in the array, and the size
 *              of each data element.
 *****************************************************************************/
typedef struct _vector {
    void*   buf;            /* the array */
    size_t  capacity;       /* the capacity of the array */
    size_t  count;          /* number of elements currently in the array */
    size_t  data_size;      /* size of each data element */
}
vector;

/******************************************************************************
 * @brief       Initialize a vector.
 * 
 * @param v             The vector to be initialized.
 * @param data_size     The size of the data type.
 *****************************************************************************/
void    construct_vector(vector* v, size_t data_size);

/******************************************************************************
 * @brief       Get the element at a given index in the vector.
 * 
 * @param v             The vector to get data from.
 * @param index         The index to get data from.
 * 
 * @return      The data at the given index.
 *****************************************************************************/
void*   get(vector* v, size_t index);

/******************************************************************************
 * @brief       Set the data at a given index in the vector.
 * 
 * @param v             The vector to set data.
 * @param data_size     The index where data will be set.
 * @param data          The data to be assigned.
 *****************************************************************************/
void    set(vector* v, size_t index, const void* data);

/******************************************************************************
 * @brief       Add a new element to the end of the vector.
 * 
 * @param v             The vector to be initialized.
 * @param data          The data to be added.
 *****************************************************************************/
void    append(vector* v, const void* data);

/******************************************************************************
 * @brief       Remove the element at the end of the vector.
 * 
 * @param v             The vector to remove element from.
 * 
 * @return      The data removed.
 *****************************************************************************/
void*   popback(vector* v);

/******************************************************************************
 * @brief       Check if the vector contains a specific data value.
 * 
 * @param v             The vector to be searched.
 * @param data          The data to be searched.
 * 
 * @return      TRUE if the vector contains the given data, FALSE otherwise.
 *****************************************************************************/
BOOLEAN contains(vector* v, const void* data);

/******************************************************************************
 * @brief       Find the location 
 * 
 * @param v             The vector to be initialized
 * @param data_size     The size of each data element
 * 
 * @return      The index of the first occurence of the given data, -1 if the
 *              given data does not exist.
 *****************************************************************************/
int     find(vector* v, const void* data);

#endif