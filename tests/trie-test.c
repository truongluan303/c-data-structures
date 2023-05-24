#include "trie.h"
#include "tester/tester.h"

int main(int argc, char **argv)
{
    tester_init();

    trie* t;
    TRY { trie_construct(t); } ENDTRY;

    trie_destroy(&t);

    tester_report(stdout, argv[0]);
    return tester_result();
}
