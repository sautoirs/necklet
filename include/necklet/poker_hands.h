#ifndef POKER_HANDS_H
#define POKER_HANDS_H

#include <stddef.h>
#include <stdint.h>

enum Player {
    PLAYER_1,
    PLAYER_2,
};

struct PokerHand;

/// Initialize a poker hand from a given player name and a deck of cards.
/// 
/// e.g. PokerHand_Init("Black", "2H 3D 5S 9C KD");
struct PokerHand *PokerHand_Init(enum Player player, const char *name, const char *deck);

/// Compare two poker hands and write the result in the given buffer.
size_t PokerHand_PrettyCompare(const struct PokerHand *self, const struct PokerHand *other, char *output, size_t size);

#endif

