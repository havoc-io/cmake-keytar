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
    // Set up testing constants
    const std::string service("keytar-test-service");
    const std::string account("keytar@example.org");
    const std::string password("$uP3RseCr1t!");
    const std::string alternate_password("Ub3R$3CrE7!?!");

    // Create buffer for retrieval
    std::string password_retrieved;

    // Try to add a password
    mu_assert("error: unable to add password",
              keytar::AddPassword(service, account, password));

    // Try to get the password
    mu_assert("error: unable to get password",
              keytar::GetPassword(service, account, &password_retrieved));
    mu_assert("error: retrieved password doesn't match password stored",
              password_retrieved == password);

    // Try to find the password
    mu_assert("error: unable to find password",
              keytar::FindPassword(service, &password_retrieved));
    mu_assert("error: found password doesn't match password stored",
              password_retrieved == password);

    // Try to replace the password
    mu_assert("error: unable to replace password",
              keytar::ReplacePassword(service, account, alternate_password));
    mu_assert("error: unable to get replaced password",
              keytar::GetPassword(service, account, &password_retrieved));
    mu_assert("error: retrieved password doesn't match new password",
              password_retrieved == alternate_password);

    // Try to delete the password
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
