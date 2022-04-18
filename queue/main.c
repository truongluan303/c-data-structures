#include "linkedqueue.c"

/*===========================================================================*/
/* main                     Perform tests on the queue implementations       */
/*===========================================================================*/
int main(argc, argv)
    int         argc;       /* arguments count */
    char**      argv;       /* arguments vector */
{
    queue q1;
    construct_queue(&q1);

    int data1 = 100, data2 = 20;
    enqueue(&q1, data1, sizeof(data1));
    enqueue(&q1, data2, sizeof(data2));

    printf("%d\n", dequeue(&q1));
    printf("%d\n", dequeue(&q1));
    printf("%d\n", dequeue(&q1));

    queue q2;
    construct_queue(&q2);

    enqueue(&q2, "0123456789", sizeof(10));
    enqueue(&q2, "12345", sizeof(5));

    printf("%s\n", dequeue(&q2));
    printf("%s\n", dequeue(&q2));

    return 0;
}