#include <necklet/bowling.h>

#include <string.h>

uint32_t count_score(const char *input, size_t size)
{
    uint32_t sum = 0;
    uint32_t double_ = 0;
    uint32_t current = 0;
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
	    if (double_ > 0) {
		current += (input[i] - '0') * 2;
		double_ -= 1;
	    } else {
	        current += input[i] - '0'; 
	    }
	    break;
	case '-':
	    if (double_ > 0) {
                double_ -= 1;
	    }
	    break;
	case ' ':
            sum += current;
	    current = 0;
	    break;
	case '/':
	    current = 10; 
	    double_ = 1;
	    break;
	case 'X':
	    current = 10; 
	    double_ = 2;
	    break;
	default:
	    break;
	}
    }
    return sum + current;
}
