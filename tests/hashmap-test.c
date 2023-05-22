#include "hashmap.h"
#include "tester/tester.h"

#define STRESS_TEST_COUNT       10000


/** @brief A custom data struct for testing purpose. */
struct custom_data_type {
    int myint;
    char* mystring;
};

/** @brief Hash function for integer type. */
static unsigned long int_hashfunc(const void* x, unsigned long _) {
    return ((*(int*)(&x) * 2654435761) % 2^32);
}

/** @brief Check equal function for integer type. */
static bool int_eq(const void* a, const void* b) {
    return *(int*)(&a) == *(int*)(&b);
}

/** @brief Hash function for string type. */
static unsigned long str_hashfunc(const void* x, unsigned long _) {
    unsigned long hash = 5381;
    int c;
    unsigned char* s = (unsigned char*)x;

    while (c = *s++) hash = ((hash << 5) + hash) + c;
    return hash;
}

static bool str_eq(const void* a, const void* b) {
    return strcmp((char*)a, (char*)b) == 0;
}

static unsigned long custom_data_type_hashfunc(const void* x,
                                               unsigned long _) {
    struct custom_data_type cdt = *(struct custom_data_type*)(&x);
    return int_hashfunc((void*)cdt.myint, 0);
}


void test_hashmap() {
    hashmap* hmap;

    // Construct a hashmap with integer keys
    TRY { hmap = hashmap_construct(&int_hashfunc, &int_eq); } ENDTRY;

    TEST(hashmap_size(hmap), 0);

    // Test set
    for (int i = 0; i <= 5; i++) {
        TEST(hashmap_set(hmap, (void*)i, (void*)(i * 2)), HASHMAP_SUCCESS);
    }
    TEST(hashmap_size(hmap), 6);
    for (int i = 0; i <= 5; i++) {
        TEST_ASSERT(hashmap_contains(hmap, (void*)i));
        void* outval;
        TEST(hashmap_get(hmap, (void*)i, &outval), HASHMAP_SUCCESS);
        TEST(outval, (void*)(i * 2));
    }

    // Test remove
    TEST_ASSERT(hashmap_remove(hmap, (void*)0));
    TEST_ASSERT(hashmap_remove(hmap, (void*)5));
    TEST_ASSERT(!hashmap_contains(hmap, (void*)0));
    TEST_ASSERT(!hashmap_contains(hmap, (void*)5));
    TEST(hashmap_size(hmap), 4);
    TEST_ASSERT(!hashmap_remove(hmap, (void*)0));
    TEST_ASSERT(!hashmap_remove(hmap, (void*)5));
    TEST_ASSERT(!hashmap_remove(hmap, (void*)10));

    // Test set on existed keys
    TEST(hashmap_set(hmap, (void*)1, (void*)1), HASHMAP_SUCCESS);
    TEST(hashmap_set(hmap, (void*)2, (void*)2), HASHMAP_SUCCESS);
    void* outval;
    TEST(hashmap_get(hmap, (void*)1, &outval), HASHMAP_SUCCESS);
    TEST(*(int*)(&outval), 1);
    TEST(hashmap_get(hmap, (void*)2, &outval), HASHMAP_SUCCESS);
    TEST(*(int*)(&outval), 2);

    // Test clear
    TEST(hashmap_clear(hmap), HASHMAP_SUCCESS);
    TEST(hashmap_size(hmap), 0);
    TEST_ASSERT(!hashmap_contains(hmap, (void*)1));
    TEST_ASSERT(!hashmap_contains(hmap, (void*)2));
    TEST_ASSERT(!hashmap_contains(hmap, (void*)3));
    TEST_ASSERT(!hashmap_contains(hmap, (void*)4));

    // Stress test
    for (unsigned int i = 0; i < STRESS_TEST_COUNT; i++) {
        TEST(hashmap_set(hmap, (void*)i, (void*)i), HASHMAP_SUCCESS);
    }

    hashmap_destroy(&hmap);
    TEST(hmap, NULL);
}

void test_hashmap_with_custom_data_types() {

}


int main(int argc, char **argv)
{
    tester_init();

    test_hashmap();
    test_hashmap_with_custom_data_types();

    tester_report(stdout, argv[0]);
    return tester_result();
}
