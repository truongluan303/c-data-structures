#include "heap.h"
#include "tester/tester.h"


void test_comparators() {
    TEST(int_comparator(1, 2), -1);
    TEST(int_comparator(1, 1), 0);
    TEST(int_comparator(1, -1), 1);

    TEST(str_comparator("string", "string"), 0);
    TEST(str_comparator("string 1a", "string 2b"), -1);
    TEST(str_comparator("123 b string", "123 a string"), 1);
}

#include <stdio.h>
void test_heap() {
    heap* h;
    TRY { h = heap_construct(true, int_comparator); } ENDTRY;
    TEST_ASSERT(h != NULL);
    TEST(heap_size(h), 0);
    TEST(heap_empty(h), HEAP_TRUE);

    heap_push(h, (void*)5);
    heap_push(h, (void*)1);
    heap_push(h, (void*)3);
    heap_push(h, (void*)10);

    TEST(heap_size(h), 4);
    TEST(heap_empty(h), HEAP_FALSE);
    TEST(heap_top(h), 1);

    void** arr = heap_to_arr(h);
    int expected_arr[4] = {1, 3, 5, 10};
    for (unsigned short i = 0; i < 4; i++) { TEST(arr[i], expected_arr[i]); }

    TEST(heap_pop(h), 1);
    TEST(heap_size(h), 3);
    TEST(heap_pop(h), 3);

    heap_destroy(&h);
    TEST(h, NULL);
}


int main(int argc, char **argv)
{
    tester_init();

    test_comparators();
    test_heap();

    tester_report(stdout, argv[0]);
    return tester_result();
}