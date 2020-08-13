#include <necklet/roman_numerals.h>

#include <stdbool.h>
#include <stdio.h>

struct number {
    uint32_t arabic;
    char roman;
};

bool is_basic(uint32_t arabic);
char get_basic(uint32_t arabic);

const struct number BASICS[] = {
    {1, 'I'},
    {5, 'V'},
    {10, 'X'},
    {50, 'L'},
    {100, 'C'},
    {500, 'D'},
    {1000, 'M'},
};

size_t to_roman(char *output, size_t size, uint32_t arabic)
{
    size_t written = 0;
    if (is_basic(arabic)) {
        char roman = get_basic(arabic);
        snprintf(output, size, "%c", roman);
        written += 1;
    }
    return written;
}

bool is_basic(uint32_t arabic)
{
    for (size_t i = 0; i < sizeof(BASICS) / sizeof(BASICS[0]); i++) {
        const struct number *basic = &BASICS[i];
        if (basic->arabic == arabic) {
            return true;
        }
    }
    return false;
}

char get_basic(uint32_t arabic)
{
    for (size_t i = 0; i < sizeof(BASICS) / sizeof(BASICS[0]); i++) {
        const struct number *basic = &BASICS[i];
        if (basic->arabic == arabic) {
            return basic->roman;
        }
    }
    return '!';
}

