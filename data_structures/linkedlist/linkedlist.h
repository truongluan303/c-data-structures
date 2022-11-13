#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>


typedef struct _linked_node
{
    void*                   data;
    struct _linked_node*    next;
}
linked_node;


typedef struct _linkedlist
{
    linked_node*            head;
    linked_node*            tail;
    size_t                  count;
}
linkedlist;


short linkedlist_construct(linkedlist* ll);

short linkedlist_free(linkedlist* ll);

short linkedlist_append(linkedlist* ll, void* data);

short linkedlist_prepend(linkedlist* ll, void* data);

short linkedlist_insert_at(linkedlist* ll, size_t index, void* data);

void* linkedlist_get(linkedlist* ll, size_t index);

void* linkedlist_set(linkedlist* ll, size_t index, void* data);

size_t linkedlist_find(linkedlist* ll, void* data);

size_t* linkedlist_find_all(linkedlist* ll, void* data);

short linkedlist_contains(linkedlist* ll, void* data);


#endif
