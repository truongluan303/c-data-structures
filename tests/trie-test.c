#include "trie.h"
#include "tester/tester.h"

int main(int argc, char **argv)
{
    tester_init();

    trie* t;
    TRY { t = trie_construct(); } ENDTRY;
    TEST_ASSERT(t != NULL);
    TEST_ASSERT(trie_is_empty(t));

    TEST(trie_add(t, "hello"), TRIE_SUCCESS);
    TEST(trie_add(t, "he"), TRIE_SUCCESS);
    TEST(trie_add(t, "world"), TRIE_SUCCESS);
    TEST(trie_add(t, "word"), TRIE_SUCCESS);

    TEST_ASSERT(!trie_is_empty(t));

    TEST_ASSERT(trie_contains(t, "hello"));
    TEST_ASSERT(trie_contains(t, "he"));
    TEST_ASSERT(trie_contains(t, "world"));
    TEST_ASSERT(trie_contains(t, "word"));
    TEST_ASSERT(!trie_contains(t, "hell"));
    TEST_ASSERT(!trie_contains(t, "h"));
    TEST_ASSERT(!trie_contains(t, "helloworld"));
    TEST_ASSERT(!trie_contains(t, "wor"));

    TEST_ASSERT(trie_contains_prefix(t, "hello"));
    TEST_ASSERT(trie_contains_prefix(t, "he"));
    TEST_ASSERT(trie_contains_prefix(t, "world"));
    TEST_ASSERT(trie_contains_prefix(t, "word"));
    TEST_ASSERT(trie_contains_prefix(t, "hell"));
    TEST_ASSERT(trie_contains_prefix(t, "h"));
    TEST_ASSERT(trie_contains_prefix(t, "wo"));
    TEST_ASSERT(trie_contains_prefix(t, "worl"));
    TEST_ASSERT(!trie_contains_prefix(t, "hellow"));
    TEST_ASSERT(!trie_contains_prefix(t, "hey"));
    TEST_ASSERT(!trie_contains_prefix(t, "wow"));
    TEST_ASSERT(!trie_contains_prefix(t, "a"));

    TEST(trie_destroy(&t), TRIE_SUCCESS);
    TEST(t, NULL);

    tester_report(stdout, argv[0]);
    return tester_result();
}
