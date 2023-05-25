#include "trie.h"
#include "tester/tester.h"

int main(int argc, char **argv)
{
    tester_init();

    trie* t;
    TRY { t = trie_construct(); } ENDTRY;
    TEST_ASSERT(t != NULL);

    TEST(trie_add(t, "hello"), TRIE_SUCCESS);
    TEST(trie_add(t, "he"), TRIE_SUCCESS);
    TEST(trie_add(t, "world"), TRIE_SUCCESS);
    TEST(trie_add(t, "word"), TRIE_SUCCESS);

    TEST_ASSERT(trie_contains(t, "hello"));
    TEST_ASSERT(trie_contains(t, "he"));
    TEST_ASSERT(trie_contains(t, "world"));
    TEST_ASSERT(trie_contains(t, "word"));

    TEST(trie_destroy(&t), TRIE_SUCCESS);
    TEST(t, NULL);

    tester_report(stdout, argv[0]);
    return tester_result();
}
