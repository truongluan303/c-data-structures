/******************************************************************************
 * @brief       A queue implementation using linked list.
 * 
 * @version     1.0.0   
 *****************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 * @brief       Represents a boolean.
******************************************************************************/
typedef enum {
    TRUE,
    FALSE
}
BOOLEAN;

/******************************************************************************
 * @brief       A queue's node, containing 2 portions including the value
 *              and the pointer to the next node.
 *****************************************************************************/
typedef struct _node {
    void*           value;      // the node's value
    struct _node*   next;       // points to next node
}
node;

/******************************************************************************
 * @brief       Containing two ends of a queue, front and tail.
 *****************************************************************************/
typedef struct _queue {
    node*           front;      // the front of the queue
    node*           tail;       // the tail of the queue
}
queue;

/******************************************************************************
 * @brief       Initialize a queue.
 * 
 * @oaram q             The queue to initialize
 *****************************************************************************/
void construct_queue(q)
    queue*      q;
{
    q->front    = NULL;
    q->tail     = NULL;
}

/******************************************************************************
 * @brief       Free all the elements in the queue.
 * 
 * @param q             The queue to free
 *****************************************************************************/
void destroy_queue(q)
    queue*      q;
{
    node* current = (q != NULL) ? q->front : NULL;
    while (current) {
        node* next_node = current->next;    // save the next node
        free(current->value);               // free the current node's value
        free(current);                      // free the current node
        current = next_node;                // move on to next node
    }
}

/******************************************************************************
 * @brief       Add a new node to the tail of the queue.
 * 
 * @param q             The queue to enqueue new value to.
 * @param new_data      The new value to be added.
 * @param data_size     The size of the data type.
 * 
 * @return      `FALSE` if unable to allocate more memory, `TRUE` otherwise.
 *****************************************************************************/
BOOLEAN enqueue(q, new_data, data_size)
    queue*      q;
    void*       new_data;
    size_t      data_size;
{
    // allocate a new node
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        // return false in case we cannot allocate more memory
        return FALSE;
    }
    // initialize the new node
    new_node->next          = NULL;
    new_node->value         = malloc(data_size);
    memcpy(new_node->value, new_data, data_size);

    if (q->front == NULL) {
        // initialize front and tail with new node
        q->front            = new_node;
        q->tail             = new_node;
    }
    else {
        // append new node to the end of the queue
        q->tail->next       = new_node;
        q->tail             = new_node;
    }
    return TRUE;
}

/******************************************************************************
 * @brief       Pop and return the value at the front of the queue.
 * 
 * @param q             The queue to perform dequeue on.
 *****************************************************************************/
void* dequeue(q)
    queue*      q;
{ 
    // cannot dequeue if the queue is empty
    if (q->front == NULL) {
        return NULL;
    }
    void*   result      = q->front->value;
    node*   temp        = q->front;
    
    // remove the temp node
    q->front = q->front->next;
    if (q->front == NULL) {
        q->tail = NULL;
    }
    free(temp->value);
    free(temp);

    return result;
}

/******************************************************************************
 * @brief       Return the value at the front of the queue (without popping)
 * 
 * @param q             The queue to perform peek on.
 * 
 * @return      The value at the front of the queue
 *****************************************************************************/
void* peek(q)
    queue*      q;
{
    // cannot peek if the queue is empty
    if (q->front == NULL) {
        return NULL;
    }
    return q->front->value;
}

/******************************************************************************
 * @brief       Check if a queue is empty.
 * 
 * @param q             The queue to be checked.
 * 
 * @return      `TRUE` if queue is empty, `FALSE` otherwise
 *****************************************************************************/
BOOLEAN is_empty(q)
    queue*      q;
{
    if (q->front == NULL) {
        return TRUE;
    }
    return FALSE;
}
