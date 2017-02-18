#define INCLUDE_DEFS
#include <atf.h>

TEST_SUITE(Local_Suite) {
    TEST(Ignored Test) {
        IGNORE("This test is ignored");
        CHECK(false); // Will not run
    }
    
    TEST(Passing Test) {
        CHECK(true);
    }

    TEST(Failing Test) {
        CHECK(false);
    }
}

int main(int argc, char** argv) {
    atf_init(argc,argv);
    RUN_TEST_SUITE(Local_Suite);
    RUN_EXTERN_TEST_SUITE(External_Suite);
    return atf_print_results();
}

TEST_SUITE(External_Suite) {
    TEST(Should_handle_SIGABRT) {
        raise(SIGABRT);
    }
}
