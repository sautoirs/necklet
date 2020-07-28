#ifndef FIZZBUZZ_H
#define FIZZBUZZ_H

#include <stddef.h>

/// Fill a buffer with Fizz, Buzz, FizzBuzz or the given number
/// 
/// @return the size of the string written in the buffer
size_t fizzbuzz(int n, char *buffer, size_t size);

#endif

