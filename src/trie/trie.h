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
 *
 * @return      TRIE_SUCCESS if the destruction succeed,
 *              TRIE_FAILURE otherwise.
 */
int trie_destroy(trie** t);

/**
 * @brief Add a new string to a trie.
 *
 * @param t     The trie to add new string to.
 * @param str   The string to be added to the given trie.
 *
 * @return      TRIE_SUCCESS if the addition is successful,
 *              TRIE_FAILURE otherwise.
 */
int trie_add(trie* t, char* str);

/**
 * @brief Check if a trie contains a string.
 *
 * @param t     The trie to be checked.
 * @param str   The string to be checked if contained within the given trie.
 *
 * @return      TRIE_TRUE if the trie contains the given string,
 *              TRIE_FALSE if not,
 *              TRIE_FAILURE if the operation fails.
 */
int trie_contains(trie* t, char* str);

/**
 * @brief Check if a trie contains a string prefix.
 *
 * @param t     The trie to be checked.
 * @param str   The prefix to be checked if contained within the given trie.
 *
 * @return      TRIE_TRUE if the trie contains the given prefix,
 *              TRIE_FALSE if not,
 *              TRIE_FAILURE if the operation fails.
 */
int trie_contains_prefix(trie* t, char* prefix);

/**
 * @brief Remove a string from a trie.
 *
 * @param t     The trie to remove a string from.
 * @param str   The string to be removed from the given trie.
 *
 * @return      TRIE_TRUE if the string is successfully removed,
 *              TRIE_FALSE if the string already did not exist in the trie,
 *              TRIE_FAILURE if the operation fails.
 */
int trie_remove(trie* t, char* str);

/**
 * @brief Check if a trie is empty.
 *
 * @param t     The trie to be checked.
 *
 * @return      TRIE_TRUE if the trie is empty,
 *              TRIE_FALSE if the trie is not empty,
 *              TRIE_FAILURE if the operation fails.
 */
int trie_is_empty(trie* t);

/**
 * @brief Get number of strings in a trie.
 *
 * @param t     The trie to get the size from.
 *
 * @return      The size of the trie, or TRIE_FAILURE if the operation fails.
 */
long trie_size(trie* t);

vector* trie_get_strings_with_prefix(trie* t, char* prefix);

#endif
