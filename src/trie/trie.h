#ifndef TRIE_H
#define TRIE_H

#include "vector.h"

#define TRIE_SUCCESS    0
#define TRIE_FAILURE    -1
#define TRIE_TRUE       1
#define TRIE_FALSE      0

typedef struct _trie trie;

/**
 * @brief Construct a new trie.
 *
 * @return The newly constructed trie.
 */
trie* trie_construct();

/**
 * @brief Destroy a trie.
 *
 * @param d     Reference to the trie to be destroyed.
 * @return      TRIE_SUCCESS if the destruction succeed,
 *              TRIE_FAILURE otherwise.
 */
int trie_destroy(trie** t);

int trie_add(trie* t, char* str);

int trie_contains(trie* t, char* str);

int trie_contains_prefix(trie* t, char* prefix);

int trie_remove(trie* t, char* str);

vector trie_get_strings_with_prefix(trie* t, char* prefix);

#endif
