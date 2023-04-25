#include "singly_linked_list.h"

#include <stdlib.h>


typedef struct _singly_linked_list {
    singly_linked_node* head;
    singly_linked_node* tail;
    size_t              count;
} singly_linked_list;


typedef struct _singly_linked_node {
    void*               value;
    singly_linked_node* next;
} singly_linked_node;


singly_linked_node* create_node(void* value);


singly_linked_list* sllist_construct() {
    singly_linked_list* list = malloc(sizeof(list));
    if (list == NULL) return NULL;

    list->head  = NULL;
    list->tail  = NULL;
    list->count = 0;
    return list;
}


int sllist_destroy(singly_linked_list** list) {
    if (list == NULL) return SINGLY_LINKED_LIST_FAILURE;

    singly_linked_node* head = (*list)->head;
    singly_linked_node* tmp;

    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    free(*list);
    *list = NULL;

    return SINGLY_LINKED_LIST_SUCCESS;
}


unsigned int sllist_size(singly_linked_list* list) {
    return list->count;
}


singly_linked_node* sllist_pushback(singly_linked_list* list, void* value) {
    if (list == NULL) return NULL;

    singly_linked_node* newnode = create_node(value);
    if (list->count == 0) {
        list->head          = newnode;
        list->tail          = newnode;
    } else {
        list->tail->next    = newnode;
        list->tail          = newnode;
    }
    list->count++;
    return list->tail;
}


singly_linked_node* sllist_pushfront(singly_linked_list* list,
                                                 void* value) {
    if (list == NULL) return NULL;

    singly_linked_node* newnode = create_node(value);
    if (list->count == 0) {
        list->head      = newnode;
        list->tail      = newnode;
    } else {
        newnode->next   = list->head;
        list->head      = newnode;
    }
    list->count++;
    return list->head;
}


singly_linked_node* sllist_insert_after_index(singly_linked_list* list,
                                              unsigned int index,
                                              void* value) {
    if (list == NULL || index >= list->count) return NULL;
    if (list->count == 0) return sllist_pushfront(list, value);

    singly_linked_node* node    = sllist_node_at(list, index);
    singly_linked_node* newnode = create_node(value);
    newnode->next               = node->next;
    node->next                  = newnode;
    list->count++;
    return newnode;
}


singly_linked_node* sllist_insert_after_node(singly_linked_list* list,
                                             singly_linked_node* node,
                                             void* value) {
    if (list == NULL || node == NULL) return NULL;

    singly_linked_node* newnode = create_node(value);
    newnode->next               = node->next;
    node->next                  = newnode;
    list->count++;
    return newnode;
}


singly_linked_node* sllist_insert_before_index(singly_linked_list* list,
                                               unsigned int index,
                                               void* value) {
    if (list == NULL || index >= list->count) return NULL;
    return index == 0
        ? sllist_pushfront(list, value)
        : sllist_insert_after_index(list, index - 1, value);
}


void* sllist_front_value(singly_linked_list* list) {
    return (list == NULL || list->count == 0) ? NULL : list->head->value;
}


void* sllist_back_value(singly_linked_list* list) {
    return (list == NULL || list->count == 0) ? NULL : list->tail->value;
}


singly_linked_node* sllist_front_node(singly_linked_list* list) {
    return (list == NULL || list->count == 0) ? NULL : list->head;
}


singly_linked_node* sllist_back_node(singly_linked_list* list) {
    return (list == NULL || list->count == 0) ? NULL : list->tail;
}


void* sllist_value_at(singly_linked_list* list, unsigned int index) {
    singly_linked_node* node = sllist_node_at(list, index);
    return node == NULL ? NULL : node->value;
}


singly_linked_node* sllist_node_at(singly_linked_list* list,
                                   unsigned int index) {
    return slnode_advance(list->head, index);
}


void* sllist_popfront(singly_linked_list* list) {
    if (list == NULL || list->count == 0) return NULL;

    void* front_val                 = list->head->value;
    singly_linked_node* front_node  = list->head;
    list->head                      = list->head->next;
    list->count--;
    free(front_node);
    return front_val;
}


void* sllist_remove_at(singly_linked_list* list, unsigned int index) {
    if (list == NULL || list->count == 0 || index >= list->count) return NULL;

    if (index == 0) return sllist_popfront(list);

    singly_linked_node* curnode = list->head;
    singly_linked_node* prevnode = NULL;

    for (size_t i = 0; i < index; i++) {
        prevnode        = curnode;
        curnode         = curnode->next;
    }
    void* deleted_value = curnode->value;
    prevnode->next      = curnode->next;
    free(curnode);
    list->count--;
    return deleted_value;
}


void* sllist_remove_after_node(singly_linked_list* list,
                               singly_linked_node* node) {
    if (list == NULL || node == NULL || node->next == NULL) return NULL;

    singly_linked_node* node_to_remove  = node->next;
    void* returned_value                = node_to_remove->value;
    node->next                          = node->next->next;
    free(node_to_remove);
    list->count--;
    return returned_value;
}


void* slnode_value(singly_linked_node* node) {
    return node->value;
}


singly_linked_node* slnode_advance(singly_linked_node* node,
                                   unsigned int step_count) {
    singly_linked_node* curnode = node;

    for (size_t i = 0; i < step_count; i++) {
        if (curnode == NULL) return NULL;
        curnode = curnode->next;
    }
    return curnode;
}


int slnode_set_value(singly_linked_node* node, void* value) {
    if (node == NULL) return SINGLY_LINKED_LIST_FAILURE;

    node->value = value;
    return SINGLY_LINKED_LIST_SUCCESS;
}


singly_linked_node* create_node(void* value) {
    singly_linked_node* newnode = malloc(sizeof(newnode));
    newnode->value              = value;
    newnode->next               = NULL;
}
