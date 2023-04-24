#include "trie.h"

#include "deque.h"

#include <stdlib.h>
#include <string.h>

#define NUM_CHARS   256


trie_node* create_node();

void deallocate_node(trie_node* node);

trie_node* get_last_node_from_string(trie* t, char* str);

trie_node* remove_str_rec(trie_node* node, unsigned char* str, bool* deleted);


typedef enum { FALSE, TRUE } boolean;


typedef struct _trie_node {
    boolean             is_terminal;
    struct trie_node*   children[NUM_CHARS];
} trie_node;


typedef struct _trie {
    trie_node*          root;
    size_t              count;
} trie;


trie* trie_construct() {
    trie* newtrie   = malloc(sizeof(*newtrie));
    newtrie->root   = trie_create_node();
    newtrie->count  = 0;
}


int trie_destroy(trie** t) {
    deallocate_node((*t)->root);
    free(*t);
    *t = NULL;
}


int trie_add(trie* t, char* str) {
    if (t == NULL || t->root == NULL) return TRIE_FAILURE;

    unsigned char* ustr     = (unsigned char*)str;
    trie_node* curnode      = t->root;
    int strsize             = strlen(str);

    for (int i = 0; i < strsize; i++) {
        if (curnode->children[ustr[i]] == NULL) {
            curnode->children[ustr[i]] = trie_create_node();
        }
        curnode = curnode->children[ustr[i]];
    }
    return TRIE_SUCCESS;
}


int trie_contains(trie* t, char* str) {
    if (t == NULL || t->root == NULL) return EXIT_FAILURE;

    trie_node* lastnode = get_last_node_from_string(t, str);
    return lastnode != NULL ? lastnode->is_terminal : TRIE_FALSE;
}


int trie_contains_prefix(trie* t, char* prefix) {
    if (t == NULL || t->root == NULL) return EXIT_FAILURE;

    trie_node* lastnode = get_last_node_from_string(t, prefix);
    return lastnode != NULL ? TRIE_TRUE : TRIE_FALSE;
}


int trie_remove(trie* t, char* str) {
    if (t == NULL || t->root == NULL || str == NULL) return TRIE_FAILURE;

    unsigned char* ustr = (unsigned char*)str;

    bool result = 1;
    return 0;
}


vector* trie_get_strings_with_prefix(trie* t, char* prefix) {
    trie_node* curnode = get_last_node_from_string(t, prefix);
    if (curnode == NULL) return NULL;

    vector* result = vector_construct();

    deque* node_queue = deque_construct();
    deque* prefix_queue = deque_construct();
    deque_pushback(node_queue, (void*)curnode);
    deque_pushback(prefix_queue, (void*)prefix);

    while(deque_size(node_queue) > 0) {
        curnode = (trie_node*)deque_popfront(node_queue);
        char* cur_prefix = (char*)deque_popfront(prefix_queue);

        for (unsigned short i = 0; i < NUM_CHARS; i++) {
            if (curnode->children[i] == NULL) continue;

            // size_t cur_prefix_len   = strlen(cur_prefix);
            // char* next_prefix       = malloc(cur_prefix_len + 1);

            // strcpy(next_prefix, cur_prefix);
            // next_prefix[cur_prefix_len] = i;

            // deque_pushback(node_queue, (void*)curnode->children[i]);
            // deque_pushback(prefix_queue, (void*)next_prefix);
        }
        // if (curnode->is_terminal == TRUE) {
        //     vector_pushback(result, (void*))
        // }
    }
    deque_destroy(node_queue);
    deque_destroy(prefix_queue);
}


trie_node* create_node() {
    trie_node* node = malloc(sizeof(*node));

    for (unsigned short i = 0; i < NUM_CHARS; i++) {
        node->children[i] = NULL;
    }
    node->is_terminal = FALSE;
    return node;
}


void deallocate_node(trie_node* node) {
    if (node == NULL) return;

    for (unsigned short i = 0; i < NUM_CHARS; i++) {
        deallocate_node(node->children[i]);
    }
    free(node);
}


trie_node* get_last_node_from_string(trie* t, char* str) {
    if (t == NULL || str == NULL) return EXIT_FAILURE;

    unsigned char* ustr     = (unsigned char*)str;
    trie_node* curnode      = t->root;
    int strsize             = strlen(str);

    for (int i = 0; i < strsize; i++) {
        if (curnode->children[ustr[i]] == NULL) return NULL;
        curnode = curnode->children[ustr[i]];
    }
    return curnode;
}

trie_node* remove_str_rec(trie_node* node, unsigned char* str, bool* deleted) {
    
}