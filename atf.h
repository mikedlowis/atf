/**
    Aardvark Test Framework - A minimalistic unit testing framework for C.

    Copyright 2014 Michael D. Lowis
    
    Permission to use, copy, modify, and/or distribute this software
    for any purpose with or without fee is hereby granted, provided
    that the above copyright notice and this permission notice appear
    in all copies.
    
    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
    OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
    PERFORMANCE OF THIS SOFTWARE.
*/
#ifndef ATF_H
#define ATF_H

#include <stddef.h>
#include <stdbool.h>

extern char* Curr_Test;
void atf_init(int argc, char** argv);
void atf_test_start(char* file, unsigned int line, char* name);
bool atf_test_assert(bool success, char* expr_str, char* file, int line);
void atf_test_fail(char* expr, char* file, int line);
int atf_print_results(void);

#define IGNORE(msg) \
    printf("%s:%d:%s:IGNORE:\n\t%s\n", __FILE__, __LINE__, Curr_Test, msg); break

#define CHECK(expr) \
    if(atf_test_assert((expr), #expr, __FILE__, __LINE__)) break

#define TEST_SUITE(name) \
    void name(void)

#define TEST(desc) \
    for(atf_test_start(__FILE__,__LINE__,#desc); Curr_Test != NULL; Curr_Test = NULL)

#define RUN_TEST_SUITE(name) \
    name();

#define RUN_EXTERN_TEST_SUITE(name) \
    do { extern TEST_SUITE(name); RUN_TEST_SUITE(name); } while(0)

#define PRINT_TEST_RESULTS \
    atf_print_results

/* Function Definitions
 *****************************************************************************/
#ifdef INCLUDE_DEFS
#include <stdio.h>
#include <stdlib.h>
#ifndef NO_SIGNALS
#include <signal.h>
#endif

char* Curr_Test = NULL;
char* Curr_File = NULL;
unsigned int Curr_Line = 0;
static unsigned int Total = 0;
static unsigned int Failed = 0;

#ifndef NO_SIGNALS
static void handle_signal(int sig) {
    /* Determine the signal name */
    char* sig_name = NULL;
    switch(sig) {
        case SIGABRT: sig_name = "SIGABRT"; break;
        case SIGBUS:  sig_name = "SIGBUS";  break;
        case SIGFPE:  sig_name = "SIGFPE";  break;
        case SIGILL:  sig_name = "SIGILL";  break;
        case SIGSEGV: sig_name = "SIGSEGV"; break;
        case SIGSYS:  sig_name = "SIGSYS";  break;
        /* If we don't recognize it then just return and let the default handler
           catch it. */
        default:      return;
    }
    /* Error and exit. No summary will be printed but the user will know which
       test has crashed. */
    fprintf(stderr,"%s:%d:0:%s:CRASH (signal: %d - %s)\n", Curr_File, Curr_Line, Curr_Test, sig, sig_name);
    Failed++;
    (void)atf_print_results();
    exit(1);
}
#endif

void atf_init(int argc, char** argv) {
    /* I reserve the right to use these later */
    (void)argc;
    (void)argv;

#ifndef NO_SIGNALS
    /* Init signal handler */
    signal(SIGABRT, handle_signal);
    signal(SIGBUS,  handle_signal);
    signal(SIGFPE,  handle_signal);
    signal(SIGILL,  handle_signal);
    signal(SIGSEGV, handle_signal);
    signal(SIGSYS,  handle_signal);
#endif
}

void atf_test_start(char* file, unsigned int line, char* name) {
    Curr_File = file;
    Curr_Line = line;
    Curr_Test = name;
    Total++;
}

bool atf_test_assert(bool success, char* expr, char* file, int line) {
    bool failed = !success;
    if (failed) atf_test_fail(expr,file,line);
    return failed;
}

void atf_test_fail(char* expr, char* file, int line) {
    Failed++;
    printf("%s:%d:0:%s:FAIL:( %s )\n", file, line, Curr_Test, expr); \
}

int atf_print_results(void) {
    static const char* results_string =
    "\nUnit Test Summary"
    "\n-----------------"
    "\nTotal:  %d"
    "\nPassed: %d"
    "\nFailed: %d"
    "\n\n";
    printf(results_string, Total, Total - Failed, Failed);
    return Failed;
}

#undef INCLUDE_DEFS
#endif

#endif /* ATF_H */
