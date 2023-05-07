#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define MIN_CAPACITY        32
#define NOT_EXIST           -1

#define SUCCESS             0
#define FAILURE             1

/******************************************************************************
 * @brief       Represents a boolean state
 *****************************************************************************/
typedef enum {
    FALSE,
    TRUE
}
BOOLEAN;

/******************************************************************************
 * @brief       Represents the vector/list data structure.
 *****************************************************************************/
typedef struct _vector vector;

/******************************************************************************
 * @brief       Construct a new vector.
 *
 * @return      The newly constructed vector.
 *****************************************************************************/
vector* vector_construct();

/******************************************************************************
 * @brief       Get the number of elements in a vector.
 *
 * @return      Number of elements in the given vector.
 *****************************************************************************/
size_t vector_size(vector* v);

/******************************************************************************
 * @brief       Get the element at a given index in the vector.
 *
 * @param v             The vector to get data from.
 * @param index         The index to get data from.
 *
 * @return      The data at the given index.
 *****************************************************************************/
void* vector_get(vector* v, size_t index);

/******************************************************************************
 * @brief       Set the data at a given index in the vector.
 *
 * @param v             The vector to set data.
 * @param index         The index where data will be set.
 * @param data          The data to be assigned.
 *
 * @return      0 if successful, 1 otherwise.
 *****************************************************************************/
int vector_set(vector* v, size_t index, void* data);

/******************************************************************************
 * @brief       Add a new element to the end of the vector.
 *
 * @param v             The vector to be added to.
 * @param data          The data to be added.
 *
 * @return      0 if successful, 1 otherwise.
 *****************************************************************************/
int vector_pushback(vector* v, void* data);

/******************************************************************************
 * @brief       Add a new element to the front of the vector.
 *
 * @param v             The vector to be added to.
 * @param data          The data to be added.
 *
 * @return      0 if successful, 1 otherwise.
 *****************************************************************************/
int vector_pushfront(vector* v, void* data);

/******************************************************************************
 * @brief       Remove the element at the end of the vector.
 *
 * @param v             The vector to remove element from.
 *
 * @return      The data removed.
 *****************************************************************************/
void* vector_popback(vector* v);

/******************************************************************************
 * @brief       Remove the element at the front of the vector.
 *
 * @param v             The vector to remove element from.
 *
 * @return      The data removed.
 *****************************************************************************/
void* vector_popfront(vector* v);

/******************************************************************************
 * @brief       Remote the element at the given index.
 *
 * @param v             The vector to remove the element from.
 * @param index         The index of the element to be removed.
 *
 * @return      The value of the deleted element.
*/
void* vector_delete(vector* v, size_t index);

/******************************************************************************
 * @brief       Check if the vector contains a specific data value.
 *
 * @param v             The vector to be searched.
 * @param data          The data to be searched.
 *
 * @return      `TRUE` if the vector contains the given data, `FALSE`
 *              otherwise.
 *****************************************************************************/
BOOLEAN vector_contains(vector* v, void* data);

/******************************************************************************
 * @brief       Find the index of an element in a vector.
 *
 * @param v             The vector to be initialized
 * @param data_size     The size of each data element
 *
 * @return      The index of the first occurence of the given data, -1 if the
 *              given data does not exist.
 *****************************************************************************/
int vector_find(vector* v, void* data);

/******************************************************************************
 * @brief       Empty the vector.
 *
 * @param v             The vector to be emptied.
 *****************************************************************************/
void vector_clear(vector* v);

/******************************************************************************
 * @brief       Swap the elements at given indices in the vector.
 *
 * @param v             The vector to swap elements.
 * @param lidx          The left index.
 * @param ridx          The right index.
 *
 * @return      0 if the swap is successful, 1 otherwise.
 *****************************************************************************/
int vector_swap(vector* v, size_t lidx, size_t ridx);

/******************************************************************************
 * @brief       Get an array representation of the vector. Since the result
 *              array is dynamically allocated, make sure it is properly freed
 *              after being used.
 *
 * @param v             The vector to get the array presentation for.
 *
 * @return      The array representation of the vector.
 *****************************************************************************/
void** vector_to_arr(vector* v);

/******************************************************************************
 * @brief       Deallocates the memory allocated for the vector.
 *
 * @return      0 if successful, 1 otherwise
******************************************************************************/
int vector_destroy(vector** v);

#endif
