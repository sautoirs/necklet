#include <necklet/fizzbuzz.h>

#include <stdio.h>

size_t fizzbuzz(int n, char *buffer, size_t size)
{
    size_t written = 0;
    if ((n % 3 == 0) && (n % 5 == 0)) {
	written = snprintf(buffer, size, "FizzBuzz");
    } else if (n % 3 == 0) {
	written = snprintf(buffer, size, "Fizz");
    } else if (n % 5 == 0) {
	written = snprintf(buffer, size, "Buzz");
    } else {
        written = snprintf(buffer, size, "%d", n);
    }
    return written;
}

