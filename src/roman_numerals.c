#include <necklet/roman_numerals.h>

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct number {
    uint32_t arabic;
    char roman[5];
};

static const struct number get_closest_digit(uint32_t arabic);
static void generate_basic_combination(char *output, uint32_t unit, size_t i);
static uint32_t get_next_roman_number(const char **next, size_t size);
static uint32_t get_digit(const char **next, size_t i);

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
    while (remaining > 0) {
        const struct number digit = get_closest_digit(remaining);
        strcpy(&output[written], digit.roman);
        written += strlen(digit.roman);
        remaining -= digit.arabic;
    };
    return written;
}

uint32_t to_arabic(const char *input, size_t size)
{
    uint32_t arabic = 0;
    const char *token = input;
    size_t remaining = size;
    while (remaining > 0) {
        const char *next = token;
        arabic += get_next_roman_number(&next, size);
        if (next != NULL) {
            remaining -= next - token;
            token = next;
        }
    }
    return arabic;
}

static const struct number get_closest_digit(uint32_t arabic)
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

static void generate_basic_combination(char *output, uint32_t unit, size_t i)
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

static uint32_t get_next_roman_number(const char **next, size_t size)
{
    uint32_t arabic = 0;
    for (size_t i = 0; i < sizeof(BASICS) / sizeof(BASICS[0]); i += 2) {
        uint32_t digit = get_digit(next, i);
        if (digit > 0) {
            arabic = digit * pow(10, i / 2);
            break;
        }
    }
    return arabic;
}

static uint32_t get_digit(const char **next, size_t i)
{
    uint32_t digit = 0;
    char one = BASICS[i].roman[0];
    char five = BASICS[i + 1].roman[0];
    char ten = BASICS[i + 2].roman[0];
    if (**next == one) {
        *next += 1;
        if (**next == one) {
            *next += 1;
            if (**next == one) {
                *next += 1;
                digit = 3;
            } else {
                digit = 2;
            }
        } else if (**next == five) {
            *next += 1;
            digit = 4;
        } else if (**next == ten) {
            *next += 1;
            digit = 9;
        } else {
            digit = 1;
        }
    } else if (**next == five) {
        *next += 1;
        if (**next == one) {
            *next += 1;
            if (**next == one) {
                *next += 1;
                if (**next == one) {
                    *next += 1;
                    digit = 8;
                } else {
                    digit = 7;
                }
            } else {
                digit = 6;
            }
        } else {
            digit = 5;
        }
    }
    return digit;
}

