#include <necklet/leap_years.h>

#include <stdbool.h>

bool is_leap_years(int n)
{
    bool leap_year = false;
    if ((n % 400) == 0) {
	leap_year = true;
    }
    if ((n % 100 == 0) && (n % 400 != 0)) { 
	leap_year = false;
    }
    if ((n % 4 == 0) && (n % 100 != 0)) {
	leap_year = true;
    }
    return leap_year;
}

