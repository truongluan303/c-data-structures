#ifndef DEQUE_H
#define DEQUE_H

#define DEQUE_SUCCESS   0
#define DEQUE_FAILURE   -1
#define DEQUE_TRUE      1
#define DEQUE_FALSE     0

typedef struct _deque deque;

/**
 * @brief Construct a new deque.
 *
 * @return The newly constructed deque.
 */
deque* deque_construct();

/**
 * @brief Destroy a deque.
 *
 * @param d     Reference to the deque to be destroyed.
 * @return      DEQUE_SUCCESS if the destruction succeed,
 *              DEQUE_FAILURE otherwise.
 */
int deque_destroy(deque** d);

/**
 * @brief Get number of elements in a deque.
 *
 * @param d     The deque to get the number of elements.
 * @return      The number of elements in the deque.
 */
unsigned int deque_size(deque* d);

/**
 * @brief Add a new value to the back of the deque.
 *
 * @param d     The deque to add new value to.
 * @param value The new value to be added.
 * @return      DEQUE_SUCCESS if the new value addition succeed,
 *              DEQUE_FAILURE otherwise.
 */
int deque_pushback(deque* d, void* value);

/**
 * @brief Add a new value to the front of the deque.
 *
 * @param d     The deque to add new value to.
 * @param value The new value to be added.
 * @return      DEQUE_SUCCESS if the new value addition succeed,
 *              DEQUE_FAILURE otherwise.
 */
int deque_pushfront(deque* d, void* value);

/**
 * @brief Remove and return the value at the back of the deque.
 *
 * @param d     The deque from which back value is popped.
 * @return      The value popped, NULL if the deque is empty or the operation
 *              fails.
 */
void* deque_popback(deque* d);

/**
 * @brief Remove and return the value at the front of the deque.
 *
 * @param d     The deque from which front value is popped.
 * @return      The value popped, NULL if the deque is empty or the operation
 *              fails.
 */
void* deque_popfront(deque* d);

/**
 * @brief Get the value at the front of the deque.
 *
 * @param d     The deque to get value from.
 * @return      The value at the front of the deque.
 */
void* deque_front(deque* d);

/**
 * @brief Get the value at the back of the deque.
 *
 * @param d     The deque to get value from.
 * @return      The value at the back of the deque.
 */
void* deque_back(deque* d);

/**
 * @brief Check if the deque contains a specific value
 *
 * @param d     The deque to check if value exists.
 * @param value The value to be checked.
 * @return      DEQUE_TRUE if the value exists in the deque, DEQUE_FALSE if
 *              not, DEQUE_FAILURE if the operation fails.
 */
int deque_contains(deque* d, void* value);

#endif
