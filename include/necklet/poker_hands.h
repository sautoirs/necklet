#ifndef POKER_HANDS_H
#define POKER_HANDS_H

#include <stddef.h>
#include <stdint.h>

enum PlayerId {
    PLAYER_1,
    PLAYER_2,
};

struct Player;

/// Initialize a poker player from a given name and a deck of cards.
/// 
/// e.g. Player_Init("Black", "2H 3D 5S 9C KD");
struct Player *Player_Init(enum PlayerId player_id, const char *name, const char *deck);

/// Compare two player hands and write the result in the given buffer.
size_t Player_PrettyCompare(const struct Player *self, const struct Player *other, char *output, size_t size);

#endif

