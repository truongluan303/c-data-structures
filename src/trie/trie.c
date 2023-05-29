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
    unsigned int        count;
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

//===========================================================================//
//                          Functions Implementations                        //
//===========================================================================//

trie* trie_construct() {
    trie* newtrie   = malloc(sizeof(*newtrie));
    newtrie->root   = create_node();
    newtrie->count  = 0;
    return newtrie;
}

int trie_destroy(trie** t) {
    if (t == NULL || *t == NULL) return TRIE_FAILURE;

    deallocate_node((*t)->root);
    free(*t);
    *t = NULL;

    return TRIE_SUCCESS;
}

int trie_add(trie* t, char* str) {
    if (t == NULL || t->root == NULL) return TRIE_FAILURE;

    unsigned char* ustr     = (unsigned char*)str;
    trie_node* curnode      = t->root;
    unsigned int strsize    = strlen(str);

    for (unsigned int i = 0; i < strsize; i++) {
        if (curnode->children[ustr[i]] == NULL) {
            curnode->children[ustr[i]] = create_node();
        }
        curnode = curnode->children[ustr[i]];
    }
    curnode->is_terminal = true;
    t->count++;

    return TRIE_SUCCESS;
}

int trie_contains(trie* t, char* str) {
    if (t == NULL || t->root == NULL) return TRIE_FAILURE;

    trie_node* lastnode = get_last_node_from_string(t, str);
    return lastnode != NULL ? lastnode->is_terminal : TRIE_FALSE;
}

int trie_contains_prefix(trie* t, char* prefix) {
    if (t == NULL || t->root == NULL) return TRIE_FAILURE;

    trie_node* lastnode = get_last_node_from_string(t, prefix);
    return lastnode != NULL ? TRIE_TRUE : TRIE_FALSE;
}

int trie_is_empty(trie* t) {
    if (t == NULL) return TRIE_FAILURE;
    return t->count == 0 ? TRIE_TRUE : TRIE_FALSE;
}

long trie_size(trie* t) {
    return t == NULL ? TRIE_FAILURE : t->count;
}
