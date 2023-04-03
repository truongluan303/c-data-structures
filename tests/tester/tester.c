#define _GNU_SOURCE     /* get strsignal def */

#include "tester.h"

struct tester_global_data TesterData;


static void
tester_sighandler(int signal)
{
    if (TesterData.escape_hatch_active) {
        TesterData.escape_hatch_active = 0;
        longjmp(TesterData.escape_hatch, signal);
    }
}

void
tester_init(void)
{
    TesterData.escape_hatch_active = 0;
    TesterData.tests = 0;
    TesterData.errors = 0;
    TesterData.signals = 0;
    TesterData.user_fails = 0;

    signal(SIGSEGV, tester_sighandler);
    signal(SIGILL, tester_sighandler);
    signal(SIGFPE, tester_sighandler);
    signal(SIGALRM, tester_sighandler);
    signal(SIGBUS, tester_sighandler);
    signal(SIGABRT, tester_sighandler);
}

void
tester_report(FILE *f, const char *preamble)
{
    if (TesterData.errors != 0 || TesterData.signals != 0) {
        fprintf(f, "%s: errors %d/%d, signals %d, FAILs %d\n",
                preamble,
                TesterData.errors,
                TesterData.tests,
                TesterData.signals,
                TesterData.user_fails);
    } else {
        fprintf(f, "ALL TESTS PASSED!\n");
    }
}

int
tester_result(void)
{
    return TesterData.errors;
}

void
tester_set_time_limit(int t)
{
    TesterData.time_limit = t;
}
