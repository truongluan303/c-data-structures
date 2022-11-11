#include <assert.h>
#include <stdio.h>

#include "../../data_structures/vector/vector.h"


int main()
{
    vector v;
    construct_vector(&v);

    // test pushback and push front
    vector_pushback(&v, (void*)1);
    vector_pushback(&v, (void*)2);
    vector_pushback(&v, (void*)3);
    vector_pushfront(&v, (void*)-1);
    assert(v.count == 4);
    assert(vector_get(&v, 0) == (int*)-1);
    assert(vector_get(&v, 1) == (int*)1);
    assert(vector_get(&v, 3) == (int*)3);

    // test contains
    assert(vector_contains(&v, (void*)-1) == TRUE);
    assert(vector_contains(&v, (void*)1) == TRUE);
    assert(vector_contains(&v, (void*)3) == TRUE);
    assert(vector_contains(&v, (void*)5) == FALSE);

    // test find
    assert(vector_find(&v, (void*)-1) == 0);
    assert(vector_find(&v, (void*)2) == 2);
    assert(vector_find(&v, (void*)3) == 3);

    // test delete
    assert(vector_delete(&v, 1) == (int*)1);
    assert(v.count == 3);
    assert(vector_get(&v, 1) == (int*)2);

    // test popback
    assert(vector_popback(&v) == (int*)3);
    assert(v.count == 2);

    // test popfront
    vector_pushfront(&v, (void*)0);
    assert(vector_popfront(&v) == (int*)0);
    assert(v.count == 2);

    // test clear
    vector_clear(&v);
    assert(v.count == 0);
    assert(vector_pushback(&v, (void*)1) == SUCCESS);

    // implicitly test vector resizing by adding and removing many elements
    for (size_t i = 0; i < 10000; i++) vector_pushback(&v, (void*)i);
    for (size_t _ = 0; _ < 5000; _++) vector_popback(&v);

    vector_free(&v);

    printf("=== All Passed! ===\n");
    return 0;
}

