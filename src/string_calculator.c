#include <necklet/string_calculator.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(const char *input, size_t input_size, char *output, size_t output_size)
{
    double sum = 0.0;
    const char *token = input;
    char *next = NULL;
    while (token < &input[input_size]) {
	if (!isdigit(*token)) {
	    snprintf(output, output_size, "Number expected but '%c' found at position %ld.", *token, token - input);
	    return;
	}
	double number = strtod(token, &next);
	sum += number;
	token = next + 1;
    };
    snprintf(output, output_size, "%lg", sum);
}

