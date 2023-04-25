#include "singly_linked_list.h"
#include "tester/tester.h"

#include <assert.h>
#include <stdio.h>


int main(int argc, char **argv)
{
    tester_init();

    singly_linked_list* llist;

    //=========================================================================
    // TEST 1
    // Make sure the singly linked list can be constructed successfully.
    //
    TRY { llist = sllist_construct(); } ENDTRY;

    TEST_ASSERT(llist != NULL);

    //=========================================================================
    // TEST 2
    // Make sure pushback and popfront functions work.
    //
    sllist_pushback(llist, (void*)5);
    sllist_pushback(llist, (void*)6);
    sllist_pushfront(llist, (void*)4);
    sllist_pushfront(llist, (void*)3);

    TEST(sllist_size(llist), 4);

    TEST_ASSERT(sllist_front_node(llist) != NULL);
    TEST_ASSERT(sllist_back_node(llist) != NULL);

    TEST((int)sllist_front_value(llist), 3);
    TEST((int)sllist_back_value(llist), 6);
    TEST((int)sllist_value_at(llist, 0), 3);
    TEST((int)sllist_value_at(llist, 1), 4);
    TEST((int)sllist_value_at(llist, 2), 5);
    TEST((int)sllist_value_at(llist, 3), 6);
    TEST(sllist_node_at(llist, 4), NULL);
    TEST(sllist_value_at(llist, 4), NULL);

    TEST(slnode_value(sllist_node_at(llist, 0)), 3);
    TEST(slnode_value(sllist_node_at(llist, 1)), 4);
    TEST(slnode_value(sllist_node_at(llist, 2)), 5);
    TEST(slnode_value(sllist_node_at(llist, 3)), 6);

    //=========================================================================
    // TEST 3
    // Make sure insert functionalities work.
    //
    TEST_ASSERT(sllist_insert_after_index(llist, 3, (void*)9) != NULL);
    TEST_ASSERT(sllist_insert_after_index(llist, 3, (void*)7) != NULL);
    TEST_ASSERT(sllist_insert_before_index(llist, 0, (void*)0) != NULL);
    TEST_ASSERT(sllist_insert_before_index(llist, 1, (void*)2) != NULL);

    TEST(sllist_insert_after_index(llist, 8, (void*)-1), NULL);
    TEST(sllist_insert_after_index(llist, 9, (void*)-1), NULL);

    TEST_ASSERT(
        sllist_insert_after_node(llist,
                                sllist_node_at(llist, 6),
                                (void*)8) != NULL);
    TEST_ASSERT(
        sllist_insert_after_node(llist,
                                 sllist_front_node(llist),
                                 (void*)1) != NULL);

    TEST(sllist_insert_before_index(llist, 10, (void*)-1), NULL);
    TEST(sllist_insert_before_index(llist, 11, (void*)-1), NULL);

    TEST(sllist_size(llist), 10);
    TEST((int)sllist_value_at(llist, 0), 0);
    TEST((int)sllist_value_at(llist, 1), 1);
    TEST((int)sllist_value_at(llist, 2), 2);
    TEST((int)sllist_value_at(llist, 3), 3);
    TEST((int)sllist_value_at(llist, 4), 4);
    TEST((int)sllist_value_at(llist, 5), 5);
    TEST((int)sllist_value_at(llist, 6), 6);
    TEST((int)sllist_value_at(llist, 7), 7);
    TEST((int)sllist_value_at(llist, 8), 8);
    TEST((int)sllist_value_at(llist, 9), 9);

    //=========================================================================
    // TEST 4
    // Make sure remove functionalities work.
    //
    TEST((int)sllist_popfront(llist), 0);
    TEST((int)sllist_popfront(llist), 1);
    TEST(sllist_size(llist), 8);

    TEST((int)sllist_remove_at(llist, 0), 2);
    TEST((int)sllist_remove_at(llist, 2), 5);
    TEST((int)sllist_remove_at(llist, 4), 8);
    TEST((int)sllist_remove_at(llist, 4), 9);
    TEST(sllist_remove_at(llist, 4), NULL);
    TEST(sllist_remove_at(llist, 5), NULL);
    TEST(sllist_size(llist), 4);

    TEST((int)sllist_value_at(llist, 0), 3);
    TEST((int)sllist_value_at(llist, 1), 4);
    TEST((int)sllist_value_at(llist, 2), 6);
    TEST((int)sllist_value_at(llist, 3), 7);

    TEST((int)sllist_remove_after_node(llist, sllist_front_node(llist)), 4);
    TEST((int)sllist_remove_after_node(llist, sllist_node_at(llist, 1)), 7);
    TEST(sllist_size(llist), 2);

    singly_linked_list* empty_list = sllist_construct();
    TEST(sllist_popfront(empty_list), NULL);
    TEST(sllist_remove_at(empty_list, 0), NULL);

    //=========================================================================
    // TEST
    // Make sure singly linked list is successfully destroyed.
    //
    TEST(sllist_destroy(&llist), SINGLY_LINKED_LIST_SUCCESS);
    TEST(llist, NULL);

    tester_report(stdout, argv[0]);
    return tester_result();
}
