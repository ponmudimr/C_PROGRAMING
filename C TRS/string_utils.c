#include "string_utils.h"
#include <ctype.h>
#include <string.h>

void reverse_string(char *str) {
    if (!str) return;
    size_t len = strlen(str);
    if (len <= 1) return;

    size_t i = 0;
    size_t j = len - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

bool is_palindrome(const char *str) {
    if (!str) return false;
    size_t len = strlen(str);
    if (len == 0) return true;

    int left = 0;
    int right = (int)len - 1;

    while (left < right) {
        while (left < right && !isalnum((unsigned char)str[left])) {
            left++;
        }
        while (left < right && !isalnum((unsigned char)str[right])) {
            right--;
        }
        if (left < right) {
            if (tolower((unsigned char)str[left]) != tolower((unsigned char)str[right])) {
                return false;
            }
            left++;
            right--;
        }
    }
    return true;
}

void trim_whitespace(char *str) {
    if (!str) return;
    size_t len = strlen(str);
    if (len == 0) return;

    size_t start = 0;
    while (str[start] != '\0' && isspace((unsigned char)str[start])) {
        start++;
    }

    if (str[start] == '\0') {
        str[0] = '\0';
        return;
    }

    size_t end = len - 1;
    while (end > start && isspace((unsigned char)str[end])) {
        end--;
    }

    size_t i = 0;
    for (size_t j = start; j <= end; j++) {
        str[i++] = str[j];
    }
    str[i] = '\0';
}

int count_words(const char *str) {
    if (!str) return 0;

    int count = 0;
    bool in_word = false;

    while (*str) {
        if (!isspace((unsigned char)*str)) {
            if (!in_word) {
                count++;
                in_word = true;
            }
        } else {
            in_word = false;
        }
        str++;
    }

    return count;
}

void to_uppercase(char *str) {
    if (!str) return;
    while (*str) {
        *str = (char)toupper((unsigned char)*str);
        str++;
    }
}
