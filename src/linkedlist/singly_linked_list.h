#ifndef VECTOR_H
#define VECTOR_H

#define SINGLY_LINKED_LIST_SUCCESS  0
#define SINGLY_LINKED_LIST_FAILURE  -1
#define SINGLY_LINKED_LIST_TRUE     1
#define SINGLY_LINKED_LIST_FALSE    0

typedef struct _singly_linked_list singly_linked_list;

typedef struct _singly_linked_node singly_linked_node;

singly_linked_list* sllist_construct();

int sllist_destroy(singly_linked_list** list);

unsigned int sllist_size(singly_linked_list* list);

singly_linked_node* sllist_pushback(singly_linked_list* list, void* value);

singly_linked_node* sllist_pushfront(singly_linked_list* list, void* value);

singly_linked_node* sllist_insert_after_index(singly_linked_list* list,
                                              unsigned int index,
                                              void* value);

singly_linked_node* sllist_insert_after_node(singly_linked_list* list,
                                             singly_linked_node* node,
                                             void* value);

singly_linked_node* sllist_insert_before_index(singly_linked_list* list,
                                               unsigned int index,
                                               void* value);

void* sllist_front_value(singly_linked_list* list);

void* sllist_back_value(singly_linked_list* list);

void* sllist_value_at(singly_linked_list* list, unsigned int index);

singly_linked_node* sllist_front_node(singly_linked_list* list);

singly_linked_node* sllist_back_node(singly_linked_list* list);

singly_linked_node* sllist_node_at(singly_linked_list* list,
                                   unsigned int index);

void* sllist_popfront(singly_linked_list* list);

void* sllist_remove_at(singly_linked_list* list, unsigned int index);

void* sllist_remove_after_node(singly_linked_list* list,
                               singly_linked_node* node);

void* slnode_value(singly_linked_node* node);

singly_linked_node* slnode_advance(singly_linked_node* node,
                                   unsigned int step_count);

int slnode_set_value(singly_linked_node* node, void* value);

#endif
