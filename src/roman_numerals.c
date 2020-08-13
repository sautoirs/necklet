#include <necklet/roman_numerals.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct number {
    uint32_t arabic;
    char roman[5];
};

const struct number get_closest_digit(uint32_t arabic);
void generate_basic_combination(char *output, uint32_t unit, size_t i);

const struct number BASICS[] = {
    {1, "I"},
    {5, "V"},
    {10, "X"},
    {50, "L"},
    {100, "C"},
    {500, "D"},
    {1000, "M"},
};

size_t to_roman(char *output, size_t size, uint32_t arabic)
{
    size_t written = 0;
    int32_t remaining = arabic;
    do {
        const struct number digit = get_closest_digit(remaining);
        strcpy(&output[written], digit.roman);
        written += strlen(digit.roman);
        remaining -= digit.arabic;
    } while (remaining > 0);
    return written;
}

const struct number get_closest_digit(uint32_t arabic)
{
    struct number number = {0, ""};
    size_t basic_size = sizeof(BASICS) / sizeof(BASICS[0]);
    for (size_t i = 0; i < basic_size; i += 2) {
        size_t ri = (((basic_size - 1) / 2) * 2) - i;
        uint32_t power = pow(10, ri / 2);
        uint32_t unit = arabic / power;
        if (unit > 0) {
            generate_basic_combination(number.roman, unit, ri);
            number.arabic = unit * power;
            return number;
        }
    }
    return number;
}

void generate_basic_combination(char *output, uint32_t unit, size_t i)
{
    char one = BASICS[i].roman[0];
    char five = BASICS[i + 1].roman[0];
    char ten = BASICS[i + 2].roman[0];
    switch (unit) {
        case 1:
            sprintf(output, "%c", one);
            break;
        case 2:
            sprintf(output, "%c%c", one, one);
            break;
        case 3:
            sprintf(output, "%c%c%c", one, one, one);
            break;
        case 4:
            sprintf(output, "%c%c", one, five);
            break;
        case 5:
            sprintf(output, "%c", five);
            break;
        case 6:
            sprintf(output, "%c%c", five, one);
            break;
        case 7:
            sprintf(output, "%c%c%c", five, one, one);
            break;
        case 8:
            sprintf(output, "%c%c%c%c", five, one, one, one);
            break;
        case 9:
            sprintf(output, "%c%c", one, ten);
            break;
    }
}
