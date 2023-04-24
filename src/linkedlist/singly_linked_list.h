#ifndef VECTOR_H
#define VECTOR_H

#define SINGLY_LINKED_LIST_SUCCESS  0
#define SINGLY_LINKED_LIST_FAILURE  -1
#define SINGLY_LINKED_LIST_TRUE     1
#define SINGLY_LINKED_LIST_FALSE    0

typedef struct _singly_linked_list singly_linked_list;

typedef struct _singly_linked_node singly_linked_node;

singly_linked_list* singly_linked_list_construct();

int singly_linked_list_destroy(singly_linked_list** list);

int singly_linked_list_pushback(singly_linked_list* list, void* value);

int singly_linked_list_pushfront(singly_linked_list* list, void* value);

singly_linked_node* singly_linked_list_insert_after(singly_linked_list* list,
                                                    unsigned int index,
                                                    void* value);

singly_linked_node* singly_linked_list_insert_after(singly_linked_list* list,
                                                    singly_linked_node* node,
                                                    void* value);

singly_linked_node* singly_linked_list_insert_before(singly_linked_list* list,
                                                     unsigned int index,
                                                     void* value);

void* singly_linked_list_front_value(singly_linked_list* list);

void* singly_linked_list_back_value(singly_linked_list* list);

void* singly_linked_list_value_at(singly_linked_list* list,
                                  unsigned int index);

singly_linked_node* singly_linked_list_front_node(singly_linked_list* list);

singly_linked_node* singly_linked_list_back_node(singly_linked_list* list);

singly_linked_node* singly_linked_list_node_at(singly_linked_list* list,
                                               unsigned int index);

void* singly_linked_list_popfront(singly_linked_list* list);

void* singly_linked_list_remove_at(singly_linked_list* list,
                                   unsigned int index);

void* singly_linked_node_value(singly_linked_node* node);

singly_linked_node* singly_linked_node_advance(singly_linked_node* node,
                                               unsigned int step_count);

singly_linked_node* singly_linked_node_advance(singly_linked_node* node);

#endif
