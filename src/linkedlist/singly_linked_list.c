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


singly_linked_node* create_node();


singly_linked_list* singly_linked_list_construct() {
    singly_linked_list* list = malloc(sizeof(list));
    if (list == NULL) return NULL;

    list->head  = NULL;
    list->tail  = NULL;
    list->count = 0;
    return list;
}


int singly_linked_list_destroy(singly_linked_list** list) {
    if (list == NULL) return SINGLY_LINKED_LIST_FAILURE;

    singly_linked_node* curnode = (*list)->head;

    while (curnode != NULL) {
        singly_linked_node* nextnode = curnode->next;
        free(curnode);
        curnode = nextnode;
    }
    free(*list);
    *list = NULL;

    return SINGLY_LINKED_LIST_SUCCESS;
}


int singly_linked_list_pushback(singly_linked_list* list, void* value) {
    if (list == NULL) return SINGLY_LINKED_LIST_FAILURE;

    singly_linked_node* newnode = create_node();
    if (list->count == 0) {
        list->head          = newnode;
        list->tail          = newnode;
    } else {
        list->tail->next    = newnode;
        list->tail          = newnode;
    }
    list->count++;
    return SINGLY_LINKED_LIST_SUCCESS;
}


int singly_linked_list_pushfront(singly_linked_list* list, void* value) {
    if (list == NULL) return SINGLY_LINKED_LIST_FAILURE;

    singly_linked_node* newnode = create_node();
    if (list->count == 0) {
        list->head      = newnode;
        list->tail      = newnode;
    } else {
        newnode->next   = list->head;
        list->head      = newnode;
    }
    list->count++;
    return SINGLY_LINKED_LIST_SUCCESS;
}


singly_linked_node* singly_linked_list_insert_after(singly_linked_list* list,
                                                    unsigned int index,
                                                    void* value) {
    if (list == NULL || index < 0 || index > list->count) {
        return NULL;
    }
    if (list->count == 0) {
        return singly_linked_list_pushfront(list, value);
    }
    singly_linked_node* node    = singly_linked_list_node_at(index);
    singly_linked_node* newnode = create_node();
    node->next                  = node->next;
    node->next                  = newnode;
    return newnode;
}


singly_linked_node* singly_linked_list_insert_after(singly_linked_list* list,
                                                    singly_linked_node* node,
                                                    void* value) {
    if (list == NULL || node == NULL) return NULL;

    singly_linked_node* newnode = create_node();
    newnode->next               = node->next;
    node->next                  = newnode;
    return newnode;
}


singly_linked_node* singly_linked_list_insert_before(singly_linked_list* list,
                                                     unsigned int index,
                                                     void* value) {
    return singly_linked_list_insert_after(list, index - 1, value);
}


void* singly_linked_list_front_value(singly_linked_list* list) {
    return (list == NULL || list->count == 0) ? NULL : list->head->value;
}


void* singly_linked_list_back_value(singly_linked_list* list) {
    return (list == NULL || list->count == 0) ? NULL : list->tail->value;
}


singly_linked_node* singly_linked_list_front_node(singly_linked_list* list) {
    return (list == NULL || list->count == 0) ? NULL : list->head;
}


singly_linked_node* singly_linked_list_back_node(singly_linked_list* list) {
    return (list == NULL || list->count == 0) ? NULL : list->tail;
}


void* singly_linked_list_value_at(singly_linked_list* list,
                                  unsigned int index) {
    return singly_linked_list_node_at(list, index)->value;
}


singly_linked_node* singly_linked_list_node_at(singly_linked_list* list,
                                               unsigned int index) {
    return singly_linked_node_advance(list->head, index);
}


void* singly_linked_list_popfront(singly_linked_list* list) {
    if (list == NULL || list->count == 0) return NULL;

    void* front_val                 = list->head->value;
    singly_linked_node* front_node  = list->head;
    list->head                      = list->head->next;
    list->count--;
    free(front_node);
    return front_val;
}


void* singly_linked_list_remove_at(singly_linked_list* list,
                                   unsigned int index) {
    if (list == NULL ||
        list->count == 0 ||
        index < 0 ||
        index >= list->count) {
        return NULL;
    }
    singly_linked_node* curnode = list->head;
    singly_linked_node* prevnode = NULL;

    for (size_t i = 0; i < index; i++) {
        prevnode        = curnode;
        curnode         = curnode->next;
    }
    void* deleted_value = curnode->value;
    prevnode->next      = curnode->next;
    free(curnode);
    return deleted_value;
}


void* singly_linked_list_remove_after(singly_linked_list* list,
                                      singly_linked_node* node) {
    if (list == NULL || node == NULL || node->next == NULL) return NULL;

    singly_linked_node* node_to_remove  = node->next;
    void* returned_value                = node->value;
    node->next                          = node->next->next;
    free(node_to_remove);
    return returned_value;
}


void* singly_linked_node_value(singly_linked_node* node) {
    return node->value;
}


singly_linked_node* singly_linked_node_advance(singly_linked_node* node,
                                               unsigned int step_count) {
    singly_linked_node* curnode = node;

    for (size_t i = 0; i < step_count; i++) {
        if (curnode == NULL) return NULL;
        curnode = curnode->next;
    }
    return curnode;
}


singly_linked_node* singly_linked_node_advance(singly_linked_node* node) {
    return singly_linked_node_advance(node, 1);
}


singly_linked_node* create_node() {
    singly_linked_node* newnode = malloc(sizeof(newnode));
    newnode->next               = NULL;
    newnode->value              = NULL;
}
