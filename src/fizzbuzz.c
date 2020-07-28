#include <necklet/fizzbuzz.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool is_fizz(int n);
bool is_buzz(int n);

size_t fizzbuzz(int n, char *buffer, size_t size)
{
    size_t written = 0;
    if (is_fizz(n) && is_buzz(n)) {
	written = snprintf(buffer, size, "FizzBuzz");
    } else if (is_fizz(n)) {
	written = snprintf(buffer, size, "Fizz");
    } else if (is_buzz(n)) {
	written = snprintf(buffer, size, "Buzz");
    } else {
        written = snprintf(buffer, size, "%d", n);
    }
    return written;
}

bool is_fizz(int n)
{
    char buffer[16];
    snprintf(buffer, sizeof(buffer) * sizeof(buffer[0]), "%d", n);
    return ((n % 3) == 0) || (strchr(buffer, '3') != NULL);
}

bool is_buzz(int n)
{
    char buffer[16];
    snprintf(buffer, sizeof(buffer) * sizeof(buffer[0]), "%d", n);
    return ((n % 5) == 0) || (strchr(buffer, '5') != NULL);

}

