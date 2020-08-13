#include <necklet/roman_numerals.h>

#include <stdbool.h>

struct number {
    uint32_t arabic;
    char roman;
};

const struct number *get_closest_basic(uint32_t arabic);
bool in_range(const struct number *self, uint32_t arabic);

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
    int32_t remaining = arabic;
    do {
        const struct number *basic = get_closest_basic(remaining);
        output[written] = basic->roman;
        written += 1;
        remaining -= basic->arabic;
    } while (remaining > 0);
    return written;
}

const struct number *get_closest_basic(uint32_t arabic)
{
    for (size_t i = sizeof(BASICS) / sizeof(BASICS[0]); i >= 0; i--) {
        const struct number *basic = &BASICS[i];
        if (in_range(basic, arabic)) {
            return basic;
        }
    }
    return NULL;
}

bool in_range(const struct number *self, uint32_t arabic)
{
    if (self->arabic <= arabic) {
        return true;
    } else {
        return false;
    }
}

