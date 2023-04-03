#include "deque.h"
#include "tester/tester.h"


#define STRESS_TEST_COUNT       10000


int main(int argc, char **argv)
{
    tester_init();

    deque* d;
    TRY { d = deque_construct(); } ENDTRY;

    TEST(deque_front(d), NULL);
    TEST(deque_back(d), NULL);
    TEST(deque_size(d), 0);

    // Make sure "pushback" works
    for (unsigned int i = 0; i < STRESS_TEST_COUNT; i++) {
        TEST(deque_pushback(d, (void*)i), DEQUE_SUCCESS);
        TEST(deque_front(d), 0);
        TEST(deque_back(d), i);
    }
    TEST(deque_size(d), STRESS_TEST_COUNT);

    // Make sure "pushfront" works
    for (unsigned short i = 0; i < STRESS_TEST_COUNT; i++) {
        TEST(deque_pushfront(d, (void*)i), DEQUE_SUCCESS);
        TEST(deque_front(d), i);
        TEST(deque_back(d), STRESS_TEST_COUNT - 1);
    }
    TEST(deque_size(d), STRESS_TEST_COUNT * 2);

    // Make sure "contains" works
    for (unsigned short i = 0; i < STRESS_TEST_COUNT; i++) {
        TEST(deque_contains(d, (void*)i), DEQUE_TRUE);
    }
    for (unsigned short i = STRESS_TEST_COUNT + 1; i < STRESS_TEST_COUNT * 2; i++) {
        TEST(deque_contains(d, (void*)i), DEQUE_FALSE);
    }

    // Make sure "popback" and "popfront" work
    for (int i = STRESS_TEST_COUNT - 1; i >= 0; i--) {
        TEST((int)deque_popback(d), i);
        TEST((int)deque_popfront(d), i);
    }
    TEST(deque_size(d), 0);
    TEST(deque_contains(d, 1), DEQUE_FALSE);

    // Make sure deque destruction works
    TEST(deque_destroy(&d), DEQUE_SUCCESS);
    TEST(d, NULL);

    tester_report(stdout, argv[0]);

    return tester_result();
}
