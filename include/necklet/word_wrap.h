#ifndef WORD_WRAP_H
#define WORD_WRAP_H

#include <stddef.h>
#include <stdint.h>

/// Split that paragraph into lines of `col` colums and return the number of char written 
size_t word_wrap(const char *input, size_t input_size, char *output, size_t output_size, uint32_t col);

#endif

