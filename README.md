# Aardvark Test Framework

A minimal unit testing framework for C distributed as a single-header library.

# License

This program is distributed under the terms of the ISC license as described in
[LICENSE.md](LICENSE.md)

# Installation

Simply copy [atf.h](atf.h) to a suitable include path for the desired project.

# Macro API

The framework is controlled through an extremely minimal set of C preprocessor 
macros. The macros are used to define test suites, define tests within suites,
and to perform actual conditional checks as part of the test. Below is a 
comprehensive list of the macros provided and their function.

```C
TEST_SUITE(name) {}         // Define a new test suite with the given name
TEST(desc) {}               // Define a new test with the given description
CHECK(cond)                 // Check that condition is true and mark test is failed if false
IGNORE(msg)                 // Mark a test as ignored with a message and skip its execution
EXPECT_EXIT {}              // Setup test to expect the mock exit function to be called
CHECK_EXITCODE(code)        // Checks that the mock exit function received the given exit code
RUN_TEST_SUITE(name)        // Runs the specified test suite
RUN_EXTERN_TEST_SUITE(name) // Runs the specified test suite, the suite is externed first
INCLUDE_DEFS                // Instructs the header to also include definitions of the API functions on include
```

# Example Usage

```C
#define INCLUDE_DEFS
#include <atf.h>

TEST_SUITE(ExampleTests) {
    TEST(Check that 1 < 2) {
        CHECK(1 < 2);
    }
    
    TEST(Check that exit is called with 42) {
        EXPECT_EXIT { exit(42); }
        CHECK_EXITCODE(42);
    }
    
    TEST(This test is ignored) {
        IGNORE("Practice ignore");
    }
}

int main(int argc, char** argv) {
    atf_init(argc, argv);
    RUN_TEST_SUITE(ExampleTests);
    return atf_print_results();
}
```

