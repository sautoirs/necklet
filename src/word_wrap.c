#include <necklet/word_wrap.h>

#include <string.h>

#define DEFAULT_ENDLINE "\n"

// Return a pointer to the char on the next line of max `col` size. Return NULL if it is the last line.
const char *next_line(const char *buffer, size_t size, uint32_t col);
// Append the input buffer to the output and return the number of bytes written.
size_t append(char *output, const char *buffer, size_t size);

size_t word_wrap(const char *input, size_t input_size, char *output, size_t output_size, uint32_t col)
{
    const char *token = input;
    size_t token_size = input_size;
    size_t i = 0;
    while (token != NULL) {
        const char *next = next_line(token, token_size, col);
	if (next != NULL) {
	    size_t size = next - token;
	    i += append(&output[i], token, size);
	    i += append(&output[i], DEFAULT_ENDLINE, strlen(DEFAULT_ENDLINE));
	    token = next;
	    token_size -= size;
	} else {
	    size_t size = token_size;
	    i += append(&output[i], token, size);
            token = NULL;
	}
    }
    return i;
}

const char *next_line(const char *buffer, size_t size, uint32_t col)
{
    if (col > size) {
        return NULL;
    }
    return buffer + col;
}

size_t append(char *output, const char *buffer, size_t size)
{
    memcpy(output, buffer, size);
    return size;
}

