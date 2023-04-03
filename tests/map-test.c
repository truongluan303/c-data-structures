#include "map.h"
#include "tester/tester.h"


int main(int argc, char **argv)
{
    tester_init();

    tester_report(stdout, argv[0]);

    return tester_result();
}
