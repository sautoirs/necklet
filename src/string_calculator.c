#include <necklet/string_calculator.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_SEPARATOR ","
#define DEFAULT_ENDLINE "\n"

// Returns true is the given char is a given separator or an end of line
bool is_separator(const char *c, const char *separator, size_t sep_size);
// Returns the separator if the given string contains one, otherwise return the default separator
const char *parse_separator(const char *buffer, size_t size, const char **separator, size_t *sep_size);
// Returns true if the given buffer ends with a separator
bool ends_with_separator(const char *buffer, size_t size, const char *separator, size_t sep_size); 
// Returns the next number token or NULL if the separator is not valid
const char *get_next_number_token(const char *next, const char *separator, size_t sep_size);

void add(const char *input, size_t input_size, char *output, size_t output_size)
{
    if (input_size == 0) {
        snprintf(output, output_size, "0");
        return;
    }
    const char *separator = NULL;
    size_t sep_size = 0;
    double sum = 0.0;
    const char *token = parse_separator(input, input_size, &separator, &sep_size);
    const char *begin = token;
    char *next = NULL;
    if (ends_with_separator(input, input_size, separator, sep_size)) {
        snprintf(output, output_size, "Number expected but EOF found.");
        return;
    }
    while (token < &input[input_size]) {
	if (!isdigit(*token)) {
	    snprintf(output, output_size, "Number expected but '%c' found at position %ld.",
	        *token, token - begin);
	    return;
	}
	double number = strtod(token, &next);
	sum += number;
	if (next >= &input[input_size]) {
	    break;
	}
	token = get_next_number_token(next, separator, sep_size);
	if (token == NULL) {
	    snprintf(output, output_size, "'%.*s' expected but '%.*s' found at position %ld.",
		(int)sep_size, separator, (int)sep_size, next, next - begin);
	    return;
	}
    };
    snprintf(output, output_size, "%lg", sum);
}

bool is_separator(const char *c, const char *separator, size_t sep_size)
{
    return memcmp(c, separator, sep_size) == 0 
	|| memcmp(c, DEFAULT_ENDLINE, strlen(DEFAULT_ENDLINE)) == 0;
}

const char *parse_separator(const char *buffer, size_t size, const char **separator, size_t *sep_size)
{
    if (size < 4) {
	*sep_size = strlen(DEFAULT_SEPARATOR);
	*separator = DEFAULT_SEPARATOR;
        return buffer;
    }
    if (memcmp(buffer, "//", strlen("//")) == 0) {
        for (size_t i = 3; i < size; i++) {
	    if (buffer[i] == '\n') {
		*sep_size = i - 2;
		*separator = &buffer[2];
		return &buffer[i + 1];
	    }
	}
    }
    *sep_size = strlen(DEFAULT_SEPARATOR);
    *separator = DEFAULT_SEPARATOR;
    return buffer;
}

bool ends_with_separator(const char *buffer, size_t size, const char *separator, size_t sep_size)
{
    return size >= sep_size
	&& is_separator(&buffer[size - sep_size], separator, sep_size);
}

const char *get_next_number_token(const char *next, const char *separator, size_t sep_size)
{
    const char *token;
    if (memcmp(next, separator, sep_size) == 0) {
        token = next + sep_size;
    } else if (memcmp(next, DEFAULT_ENDLINE, strlen(DEFAULT_ENDLINE)) == 0) {
        token = next + strlen(DEFAULT_ENDLINE);
    } else {
	token = NULL;
    }
    return token;
}

