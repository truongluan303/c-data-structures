#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#define SINGLY_LINKED_LIST_SUCCESS  0
#define SINGLY_LINKED_LIST_FAILURE  -1
#define SINGLY_LINKED_LIST_TRUE     1
#define SINGLY_LINKED_LIST_FALSE    0

/**
 * @brief Represents the singly linked list.
 */
typedef struct _singly_linked_list singly_linked_list;

/**
 * @brief Represents the singly linked list node.
 */
typedef struct _singly_linked_node singly_linked_node;

/**
 * @brief Construct a new singly linked list.
 *
 * @return The newly constructed list.
 */
singly_linked_list* sllist_construct();

/**
 * @brief Free a singly linked list.
 *
 * @param list Reference to the singly linked list to be free.
 * @return SINGLY_LINKED_LIST_SUCCESS if the list is successfully destroyed,
 *         SINGLY_LINKED_LIST_FAILURE otherwise.
 */
int sllist_destroy(singly_linked_list** list);

/**
 * @brief Get number of nodes in a singly linked list.
 *
 * @param list The singly linked list to get the size from.
 * @return Number of nodes in the given singly linked list.
 */
unsigned int sllist_size(singly_linked_list* list);

/**
 * @brief Add a new node to the end of the given singly linked list.
 *
 * @param list The list to append new node to.
 * @param value The value of the new node.
 * @return The newly added node, NULL if the operation fails.
 */
singly_linked_node* sllist_pushback(singly_linked_list* list, void* value);

/**
 * @brief Add a new node to the beginning of the given singly linked list.
 *
 * @param list The singly linked list to add new node to.
 * @param value The value of the new node.
 * @return The newly added node, NULL if the operation fails.
 */
singly_linked_node* sllist_pushfront(singly_linked_list* list, void* value);

/**
 * @brief Add a new node after a given position.
 *        For example, after appending value 2 to index 1, list `0,1,3` will
 *        become `0,1,2,3`.
 *
 * @param list The singly linked list to add new node to.
 * @param index The position to append the new node to.
 * @param value The value of the new node.
 * @return The newly added node, NULL if the operation fails.
 */
singly_linked_node* sllist_insert_after_index(singly_linked_list* list,
                                              unsigned int index,
                                              void* value);

/**
 * @brief Add a new node after the given node.
 *        For example, after appending value 2 to the first node, list `1,3`
 *        will become `1,2,3`.
 *
 * @param list The singly linked list to add new node to.
 * @param node The node to append new node to.
 * @param value The value of the new node.
 * @return The newly added node, NULL if the operation fails.
 */
singly_linked_node* sllist_insert_after_node(singly_linked_list* list,
                                             singly_linked_node* node,
                                             void* value);

/**
 * @brief Add a new node before a given position.
 *
 * @param list The singly linked list to add new node to.
 * @param index The position to prepend the new node to.
 * @param value The value of the new node.
 * @return The newly added node, NULL if the operation fails.
 */
singly_linked_node* sllist_insert_before_index(singly_linked_list* list,
                                               unsigned int index,
                                               void* value);

/**
 * @brief Get the value of the front (first) node in a singly linked list.
 *
 * @param list The singly linked list to get the value from.
 * @return The value at the front node of the given singly linked list.
 */
void* sllist_front_value(singly_linked_list* list);

/**
 * @brief Get the value of the back (last) node in a singly linked list.
 *
 * @param list The singly linked list to get the value from.
 * @return The value at the back node of the given singly linked list.
 */
void* sllist_back_value(singly_linked_list* list);

/**
 * @brief Get the value of the node at the given position in a singly linked
 *        list.
 *
 * @param list The singly linked list to get the value from.
 * @param index The position of the node to get value from.
 * @return The value of the node at the given position.
 */
void* sllist_value_at(singly_linked_list* list, unsigned int index);

/**
 * @brief Get the front (first) node of the singly linked list.
 *
 * @param list The singly linked list to get the node from.
 * @return The front node of the given list, NULL if the operation fails.
 */
singly_linked_node* sllist_front_node(singly_linked_list* list);

/**
 * @brief Get the back (last) node of the singly linked list.
 *
 * @param list The singly linked list to get the node from.
 * @return The back node of the given list, NULL if the operation fails.
 */
singly_linked_node* sllist_back_node(singly_linked_list* list);

/**
 * @brief Get the node at a position in a singly linked list.
 *
 * @param list The singly linked list to get the node from.
 * @param index The position where the node is at.
 * @return The node at the given position, NULL if the operation fails.
 */
singly_linked_node* sllist_node_at(singly_linked_list* list,
                                   unsigned int index);

/**
 * @brief Remove the front (first) node from a singly linked list.
 *
 * @param list The singly linked list to remove the node from.
 * @return The value of the removed node.
 */
void* sllist_popfront(singly_linked_list* list);

/**
 * @brief Remove the node at the given position from a singly linked list.
 *
 * @param list The singly linked list to remove the node from.
 * @param index The position of the node to be removed.
 * @return The value of the removed node.
 */
void* sllist_remove_at(singly_linked_list* list, unsigned int index);

/**
 * @brief Remove the given node's next node from a singly linked list.
 *
 * @param list The singly linked list to remove the node from.
 * @param node The node whose next node will be removed.
 * @return The value of the removed node.
 */
void* sllist_remove_after_node(singly_linked_list* list,
                               singly_linked_node* node);

/**
 * @brief Get the value of a node.
 *
 * @param node The node to get value from.
 * @return The value of the given node.
 */
void* slnode_value(singly_linked_node* node);

/**
 * @brief Get the next node of a node.
 *
 * @param node The node to get next node from.
 * @return The next node of the given node.
 */
singly_linked_node* slnode_next_node(singly_linked_node* node);

/**
 * @brief Advance to the next node(s). For example, advanceing 2 steps from node
 *        1 in list `1,2,3,4` will result in node 3.
 *
 * @param node The node to advance from.
 * @param step_count Number of steps to advance.
 * @return The node that is advanced to.
 */
singly_linked_node* slnode_advance(singly_linked_node* node,
                                   unsigned int step_count);

/**
 * @brief Set the value of a node.
 *
 * @param node The node whose value to be set.
 * @param value The new value for the node.
 * @return SINGLY_LINKED_NODE_SUCCESS if the node is successfully set,
 *         SINGLY_LINKED_NODE_FALSE otherwise.
 */
int slnode_set_value(singly_linked_node* node, void* value);

#endif
