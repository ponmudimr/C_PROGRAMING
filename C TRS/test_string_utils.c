#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "string_utils.h"

void test_reverse_string(void) {
    char s1[] = "hello";
    reverse_string(s1);
    assert(strcmp(s1, "olleh") == 0);

    char s2[] = "C";
    reverse_string(s2);
    assert(strcmp(s2, "C") == 0);

    char s3[] = "";
    reverse_string(s3);
    assert(strcmp(s3, "") == 0);

    printf("  [PASS] test_reverse_string\n");
}

void test_is_palindrome(void) {
    assert(is_palindrome("racecar") == true);
    assert(is_palindrome("RaceCar") == true);
    assert(is_palindrome("hello") == false);
    assert(is_palindrome("A man a plan a canal Panama") == true);
    assert(is_palindrome("") == true);

    printf("  [PASS] test_is_palindrome\n");
}

void test_trim_whitespace(void) {
    char s1[] = "  hello world  ";
    trim_whitespace(s1);
    assert(strcmp(s1, "hello world") == 0);

    char s2[] = "  ";
    trim_whitespace(s2);
    assert(strcmp(s2, "") == 0);

    printf("  [PASS] test_trim_whitespace\n");
}

void test_count_words(void) {
    assert(count_words("Hello world from C") == 4);
    assert(count_words("   Multiple   spaces   between  ") == 3);
    assert(count_words("") == 0);
    assert(count_words("   ") == 0);

    printf("  [PASS] test_count_words\n");
}

void test_to_uppercase(void) {
    char s1[] = "Hello World 123!";
    to_uppercase(s1);
    assert(strcmp(s1, "HELLO WORLD 123!") == 0);

    printf("  [PASS] test_to_uppercase\n");
}

int main(void) {
    printf("--- Running String Utilities Test Suite ---\n");
    test_reverse_string();
    test_is_palindrome();
    test_trim_whitespace();
    test_count_words();
    test_to_uppercase();
    printf("=== ALL STRING UTILITY TESTS PASSED ===\n");
    return 0;
}
