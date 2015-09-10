// Standard includes
#include <string>
#include <iostream>

// keytar includes
#include <keytar.h>

// MinUnit includes
#include "minunit.h"


// Required MinUnit definitions
int tests_run = 0;


// Make sure GetPassword doesn't succeed for a non-existent service/account
const char * test_non_existent_get() {
    std::string password;
    mu_assert("error: got non-existent password",
              !keytar::GetPassword("keytar-test-bad-service",
                                   "keytar-test-bad-account",
                                   &password));
    return 0;
}


// Make sure FindPassword doesn't succeed for a non-existent service
const char * test_non_existent_find() {
    std::string password;
    mu_assert("error: found non-existent password",
              !keytar::FindPassword("keytar-test-bad-service",
                                    &password));
    return 0;
}


// Make sure the standard add/get/find/delete
const char * test_password_lifecycle() {
    const std::string service("keytar-test-service");
    const std::string account("keytar@example.org");
    const std::string password("$uP3RseCr1t!");
    std::string password_got;
    std::string password_found;
    mu_assert("error: unable to add password",
              keytar::AddPassword(service, account, password));
    mu_assert("error: unable to get password",
              keytar::GetPassword(service, account, &password_got));
    mu_assert("error: retrieved password doesn't match password stored",
              password == password_got);
    mu_assert("error: unable to find password",
              keytar::FindPassword(service, &password_found));
    mu_assert("error: found password doesn't match password stored",
              password == password_found);
    mu_assert("error: unable to delete password",
              keytar::DeletePassword(service, account));
    return 0;
}


// Test registry
const char * all_tests() {
    mu_run_test(test_non_existent_get);
    mu_run_test(test_non_existent_find);
    mu_run_test(test_password_lifecycle);
    return 0;
}


// Main entry point
int main(int argc, char **argv) {
    // Run tests
    const char *result = all_tests();

    // Watch for errors
    if (result != 0) {
        std::cerr << result << std::endl;
    }
    else {
        std::cout << "All tests passed" << std::endl;
    }
    std::cout << "Tests run: " << tests_run << std::endl;

    // Check result
    return result != 0;
}
