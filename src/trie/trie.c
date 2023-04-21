#include "trie.h"

#include <stdlib.h>
#include <string.h>

#define NULL        0
#define NUM_CHARS   256


trie_node* create_node();

void deallocate_node(trie_node* node);

trie_node* get_last_node_from_string(trie* t, char* str);


typedef enum { TRUE, FALSE } boolean;


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
    // TODO: implement this
    return 0;
}


char** trie_get_with_prefix(trie* t, char* prefix) {
    // TODO: implement this
    return NULL;
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
    unsigned char* ustr     = (unsigned char*)str;
    trie_node* curnode      = t->root;
    int strsize             = strlen(str);

    for (int i = 0; i < strsize; i++) {
        if (curnode->children[ustr[i]] == NULL) return NULL;
        curnode = curnode->children[ustr[i]];
    }
    return curnode;
}