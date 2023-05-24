#include "trie.h"

#include "deque.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHARS   256


typedef struct _trie_node {
    bool                is_terminal;
    struct _trie_node*  children[NUM_CHARS];
} trie_node;

typedef struct _trie {
    trie_node*          root;
    size_t              count;
} trie;


//===========================================================================//
//                          Private Helper Functions                         //
//===========================================================================//

static trie_node* create_node() {
    trie_node* node = malloc(sizeof(*node));

    for (unsigned short i = 0; i < NUM_CHARS; i++) {
        node->children[i] = NULL;
    }
    node->is_terminal = false;
    return node;
}

static void deallocate_node(trie_node* node) {
    if (node == NULL) return;

    for (unsigned short i = 0; i < NUM_CHARS; i++) {
        deallocate_node(node->children[i]);
    }
    free(node);
}

static trie_node* get_last_node_from_string(trie* t, char* str) {
    unsigned char* ustr     = (unsigned char*)str;
    trie_node* curnode      = t->root;
    int strsize             = strlen(str);

    for (int i = 0; i < strsize; i++) {
        if (curnode->children[ustr[i]] == NULL) return NULL;
        curnode = curnode->children[ustr[i]];
    }
    return curnode;
}

// static trie_node* remove_str_rec(trie_node* node,
//                                  unsigned char* str,
//                                  bool* deleted) {

// }

//===========================================================================//
//                          Functions Implementations                        //
//===========================================================================//

trie* trie_construct() {
    trie* newtrie   = malloc(sizeof(*newtrie));
    newtrie->root   = create_node();
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
            curnode->children[ustr[i]] = create_node();
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
        // if (curnode->is_terminal == true) {
        //     vector_pushback(result, (void*))
        // }
    }
    deque_destroy(&node_queue);
    deque_destroy(&prefix_queue);
}
