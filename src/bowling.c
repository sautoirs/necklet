#include <necklet/bowling.h>

#include <string.h>

uint32_t count_score(const char *input, size_t size)
{
    uint32_t sum = 0;
    for (size_t i = 0; i < size; i++) {
        switch (input[i]) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
	    sum += input[i] - '0'; 
	    break;
	case ' ':
	    break;
	default:
	    break;
	}
    }
    return sum;
}
