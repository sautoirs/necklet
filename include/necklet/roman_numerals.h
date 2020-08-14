#ifndef ROMAN_NUMERALS_H
#define ROMAN_NUMERALS_H

#include <stddef.h>
#include <stdint.h>

/// Write the number in the given buffer as a roman number and return the number of bytes written
size_t to_roman(char *output, size_t size, uint32_t number);

/// Return the given roman numeral translated into arabic
uint32_t to_arabic(const char *input, size_t size);

#endif

