#include "atf.h"
#include <signal.h>

TEST_SUITE(External_Suite) {
    TEST(Should_handle_SIGABRT) {
        raise(SIGABRT);
    }
}
