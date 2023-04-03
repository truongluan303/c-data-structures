#include "deque.h"
#include <stdio.h>
#include <assert.h>

int main() {
    deque* d = deque_construct(d);

    // deque_pushback(d, (void*)1);
    // deque_pushback(d, (void*)2);
    // deque_pushback(d, (void*)3);
    // deque_pushfront(d, (void*)-1);

    // debug(d);

    // for (int i = 0; i < 4; i++) {
    //     printf("%d\n", (int)deque_popback(d));
    //     debug(d);
    // }
    // printf("DONE\n");

    for (int i = 0; i < 100; i++) {
        deque_pushfront(d, (void*)i);
    }

    // for (int i = 0; i < 100; i++) {
    //     printf("%d\n", (int)deque_popfront(d));
    // }

    deque_destroy(&d);

    return 0;
}
