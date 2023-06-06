#include "vector.h"

#include <time.h>

#include "tester/tester.h"


typedef struct _custom_data {
    int intval;
    int index;
} custom_data;


short custom_data_comparator(const void* leftval, const void* rightval) {
    custom_data* leftdata = (custom_data*)leftval;
    custom_data* rightdata = (custom_data*)rightval;

    if (leftdata->intval < rightdata->intval) {
        return -1;
    } else if (leftdata->intval == rightdata->intval) {
        return 0;
    } else {
        return 1;
    }
}


void test_vector_sort() {
    vector* v;
    TRY { v = vector_construct(); } ENDTRY;
    srand(time(NULL));

    for (size_t _ = 0; _ < 100; _++) {
        vector_pushback(v, (void*)rand());
    }
    vector_sort(v, NULL);
    for (size_t i = 1; i < 100; i++) {
        TEST_ASSERT(vector_get(v, i - 1) <= vector_get(v, i));
    }

    vector_destroy(&v);
    TRY { v = vector_construct(); } ENDTRY;

    for (size_t _ = 0; _ < 10000; _++) {
        vector_pushback(v, (void*)rand());
    }
    vector_sort(v, NULL);
    for (size_t i = 1; i < 10000; i++) {
        TEST_ASSERT(vector_get(v, i - 1) <= vector_get(v, i));
    }

    vector_destroy(&v);
    TRY { v = vector_construct(); } ENDTRY;

    for (size_t i = 0; i < 10000; i++) {
        custom_data data = {rand(), i};
        vector_pushback(v, (void*)&data);
    }
    vector_sort(v, NULL);
    for (size_t i = 1; i < 10000; i++) {
        short cmp_result = custom_data_comparator(vector_get(v, i - 1),
                                                  vector_get(v, i));
        TEST_ASSERT(cmp_result <= 0);
    }

    vector_destroy(&v);
}


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
    vector_clear(v);
    for (size_t i = 0; i < 10000; i++) {
        vector_pushback(v, (void*)i);
    }
    for (size_t i = 0; i < 10000; i++) {
        TEST(vector_get(v, i), i);
    }
    for (size_t _ = 0; _ < 5000; _++) {
        vector_popback(v);
    }
    vector_clear(v);

    vector_destroy(&v);
    TEST(v, NULL);

    test_vector_sort();

    tester_report(stdout, argv[0]);
    return tester_result();
}
