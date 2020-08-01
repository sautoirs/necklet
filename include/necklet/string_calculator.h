#ifndef STRING_CALCULATOR_H
#define STRING_CALCULATOR_H

#include <stddef.h>

/// Add numbers in a string and return the result as a string
///
/// The input numbers are coma separated.
void add(const char *input, size_t input_size, char *output, size_t output_size);

#endif

