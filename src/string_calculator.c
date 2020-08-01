#include <necklet/string_calculator.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns true is the given char is a given separator or a \n
bool is_separator(char c, char separator);
// Returns true if the given buffer ends with a separator
bool ends_with_separator(const char *buffer, size_t size, char separator); 

void add(const char *input, size_t input_size, char *output, size_t output_size)
{
    if (input_size == 0) {
        snprintf(output, output_size, "0");
        return;
    }
    if (ends_with_separator(input, input_size, ',')) {
        snprintf(output, output_size, "Number expected but EOF found.");
        return;
    }
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

bool is_separator(char c, char separator) {
    return c == separator || c == '\n';
}

bool ends_with_separator(const char *buffer, size_t size, char separator) {
    return size > 0 && is_separator(buffer[size - 1], separator);
}
