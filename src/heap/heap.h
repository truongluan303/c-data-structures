#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

#define HEAP_SUCCESS    0
#define HEAP_FAILURE    -1
#define HEAP_TRUE       1
#define HEAP_FALSE      0

/**
 * @brief Represent the heap data structure.
 */
typedef struct _heap heap;

/**
 * @brief Construct a heap.
 *
 * @param ismin         Whether the heap is a min heap (or max heap).
 * @param comparator    The compare function for the heap value type.
 *
 * @return The newly constructed heap.
 */
heap* heap_construct(bool ismin,
                     int (*comparator)(const void* val1, const void* val2));

/**
 * @brief Destroy (De-allocate) a heap.
 *
 * @param h             The heap to be destroyed.
 *
 * @return HEAP_SUCCESS if the destruction is successful,
 *         HEAP_FAILURE otherwise.
 */
int heap_destroy(heap** h);

/**
 * @brief Get the size of a heap.
 *
 * @param h             The heap to get the size from.
 *
 * @return The size of the given heap.
 */
unsigned int heap_size(heap* h);

/**
 * @brief Check if a heap is empty.
 *
 * @param h             The heap to check whether empty or not.
 *
 * @return HEAP_TRUE if the heap is empty, HEAP_FALSE if not, HEAP_FAILURE
 *         if the operation fails.
 */
int heap_empty(heap* h);

/**
 * @brief Push new data to the heap.
 *
 * @param h             The heap to add new data to.
 * @param data          The new data to be added.
 *
 * @return HEAP_SUCCESS if the new data is successfully added, HEAP_FAILURE
 *         otherwise.
 */
int heap_push(heap* h, void* data);

/**
 * @brief Pop the data at the head of a heap.
 *
 * @param h             The heap to pop head data from.
 *
 * @return The data at the head of the heap that is just removed, NULL if the
 *         operation fails.
 */
void* heap_pop(heap* h);

/**
 * @brief Check if a heap contains the given value.
 *
 * @param h             The heap to be checked.
 * @param value         The value to be checked.
 *
 * @return HEAP_TRUE if the value is found in the heap, HEAP_FALSE if not,
 *         HEAP_FAILURE if the operation fails.
 */
int heap_contains(heap* h, void* value);

/**
 * @brief Get the data at the head of a heap.
 *
 * @param h             The heap to get data from.
 *
 * @return The data at the head of the heap, NULL if the operation fails.
 */
void* heap_top(heap* h);

/**
 * @brief Get n largest values from the heap.
 *
 * @param h             The heap to get data from.
 * @param n             Number of largest values.
 *
 * @return An array containing n largest values of the heap.
 */
void** heap_nlargest(heap* h, unsigned int n);

/**
 * @brief Get n smallest values from the heap.
 *
 * @param h             The heap to get data from.
 * @param n             Number of smallest values.
 *
 * @return An array containing n smallest values of the heap.
 */
void** heap_nsmallest(heap* h, unsigned int n);

/**
 * @brief Get an array representation of a heap.
 *
 * @param h             The heap to get the array representation for.
 *
 * @return An array representation of the heap.
 */
void** heap_to_arr(heap* h);

/**
 * @brief Remove all values from the heap.
 *
 * @param h             The heap to be cleared.
 *
 * @return HEAP_SUCCESS if the heap is successfully cleared, HEAP_FAILURE if
 *         the operation fails.
 */
int heap_clear(heap* h);

/**
 * @brief A comparator for integer values.
 *
 * @param val1          The first value.
 * @param val2          The second value.
 *
 * @return -1 if val1 is smaller, 1 if val2 is smaller, 0 if the values equal.
 */
int int_comparator(const void* val1, const void* val2);

/**
 * @brief A basic comparator for string values.
 *
 * @param val1          The first value.
 * @param val2          The second value.
 *
 * @return 0 if both strings equal, -1 if the first non-matching character in
 *         val1 is smaller than that of val2, 1 if the first non-matching
 *         character in val1 is greater than that of val2.
 */
int str_comparator(const void* val1, const void* val2);

#endif
