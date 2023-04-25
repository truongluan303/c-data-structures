#include "vector.h"
#include "tester/tester.h"

int main(int argc, char **argv)
{
    tester_init();

    vector* v;
    TRY { v = vector_construct(); } ENDTRY;

    // test pushback and push front
    vector_pushback(v, (void*)1);
    vector_pushback(v, (void*)2);
    vector_pushback(v, (void*)3);
    vector_pushfront(v, (void*)-1);
    TEST(vector_size(v), 4);
    TEST(vector_get(v, 0), (int*)-1);
    TEST(vector_get(v, 1), (int*)1);
    TEST(vector_get(v, 3), (int*)3);

    // test contains
    TEST(vector_contains(v, (void*)-1), TRUE);
    TEST(vector_contains(v, (void*)1), TRUE);
    TEST(vector_contains(v, (void*)3), TRUE);
    TEST(vector_contains(v, (void*)5), FALSE);

    // test find
    TEST(vector_find(v, (void*)-1), 0);
    TEST(vector_find(v, (void*)2), 2);
    TEST(vector_find(v, (void*)3), 3);

    // test delete
    TEST(vector_delete(v, 1), (int*)1);
    TEST(vector_size(v), 3);
    TEST(vector_get(v, 1), (int*)2);

    // test popback
    TEST(vector_popback(v), (int*)3);
    TEST(vector_size(v), 2);

    // test popfront
    vector_pushfront(v, (void*)0);
    TEST(vector_popfront(v), (int*)0);
    TEST(vector_size(v), 2);

    // test clear
    vector_clear(v);
    TEST(vector_size(v), 0);
    TEST(vector_pushback(v, (void*)1), SUCCESS);

    // implicitly test vector resizing by adding and removing many elements
    for (size_t i = 0; i < 10000; i++) vector_pushback(v, (void*)i);
    for (size_t _ = 0; _ < 5000; _++) vector_popback(v);

    vector_destroy(&v);

    tester_report(stdout, argv[0]);
    return tester_result();
}
