#include <necklet/string_calculator.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(const char *input, size_t input_size, char *output, size_t output_size)
{
    double sum = 0.0;
    const char *token = input;
    char *next = NULL;
    while (token < &input[input_size]) {
	double number = strtod(token, &next);
	if (token != next) {
	    sum += number;
	}
	token = next + 1;
    };
    snprintf(output, output_size, "%lg", sum);
}

