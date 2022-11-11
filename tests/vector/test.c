#include "../../data_structures/vector/vector.h"
#include <stdio.h>

int main()
{
    vector v;
    construct_vector(&v);

    vector_pushback(&v, (void*)1);
    vector_pushback(&v, (void*)2);
    vector_pushback(&v, (void*)3);
    vector_pushfront(&v, (void*)-1);

    vector_free(&v);
}
