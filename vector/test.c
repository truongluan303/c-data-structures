#include "vector.h"
#include <stdio.h>

int main(int argc, char** argv) 
{
    // ignore program name
    argc--;
    argv++;

    vector v;
    construct_vector(&v, sizeof(int));

    append(&v, 10);
    append(&v, 20);
    append(&v, 30);

    //printf("%d", popback(&v));

    free(v.buf);
}