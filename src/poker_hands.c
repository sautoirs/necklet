#include <necklet/poker_hands.h>

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALUE_SIZE 6
#define NUMBER_OF_CARDS 5
#define NUMBER_OF_PLAYERS 2

#define _ERROR(format, ...) error(__FILE__, __func__, __LINE__, format, __VA_ARGS__)
#define ERROR(...) _ERROR(__VA_ARGS__, 0);

enum Value {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    JACK,
    QUEEN,
    KING,
    ACE,
};

enum Suit {
    DIAMOND,
    CLUB,
    HEART,
    SPADE,
};

struct Card {
    enum Value value;
    enum Suit suit;
};

struct CardDeck {
    struct Card cards[NUMBER_OF_CARDS];
};

struct Player {
    const char *name;
    struct CardDeck deck;
};

struct StringBuffer {
    char *buffer;
    size_t size;
    size_t written;
};

enum PokerHandType {
    NO_HAND,
    HIGH_CARD,
    PAIR,
    TWO_PAIRS,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    HIGHEST_HAND,
};

struct PokerHand;

struct PokerHandMethods {
    int (*Compare)(const struct PokerHand *, const struct PokerHand *);
    enum PokerHandType (*GetType)(const struct PokerHand *);
    void (*ToString)(const struct PokerHand *, char *);
};

struct PokerHand {
    const struct PokerHandMethods *vtable;
    union {
        struct {
            struct Card card;
        } HighCard;
        struct {
            struct Card card;
        } Pair;
        struct {
            struct Card firstCard;
            struct Card secondCard;
        } TwoPairs;
        struct {
            struct Card card;
        } ThreeOfAKind;
        struct {
            struct Card card;
        } Straight;
        struct {
            struct Card card;
        } Flush;
    } value;
};

static void error(const char *file, const char *function, size_t line, const char *format, ...);
static enum Value Value_FromString(const char *string);
static void Value_ToString(enum Value self, char *output);
static enum Suit Suit_FromString(const char *string);
static void StringBuffer_Init(struct StringBuffer *self, char *buffer, size_t size);
static void StringBuffer_Write(struct StringBuffer *self, const char *format, ...);
static size_t StringBuffer_GetWritten(const struct StringBuffer *self);
static void CardDeck_Init(struct CardDeck *self, const char *deck);
static void CardDeck_Copy(struct CardDeck *self, const struct CardDeck *other);
static int CardDeck_Compare(const struct CardDeck *self, const struct CardDeck *other, struct PokerHand *hand);
static struct PokerHand CardDeck_GetHighestPokerHand(const struct CardDeck *self);
static struct PokerHand CardDeck_GetHighestPokerHandLowerThan(const struct CardDeck *self, const struct PokerHand *limit);
static void CardDeck_Sort(struct CardDeck *self);
static void Card_Init(struct Card *self, enum Value value, enum Suit suit);
static void Card_Copy(struct Card *self, const struct Card *other);
static void Card_FromString(struct Card *self, const char *string);
static int Card_Compare(const struct Card *self, const struct Card *other);
static bool Card_DoesFollow(const struct Card *self, const struct Card *other);
static bool Card_SuitEquals(const struct Card *self, const struct Card *other);
static enum Value Card_GetValue(const struct Card *self);
static enum Suit Card_GetSuit(const struct Card *self);
static int PokerHand_Compare(const struct PokerHand *self, const struct PokerHand *other);
static void NoHand_Default(struct PokerHand *self);
static int NoHand_Compare(const struct PokerHand *self, const struct PokerHand *other);
static enum PokerHandType NoHand_GetType(const struct PokerHand *self);
static void NoHand_ToString(const struct PokerHand *self, char *output);
static void HighCard_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit);
static int HighCard_Compare(const struct PokerHand *self, const struct PokerHand *other);
static enum PokerHandType HighCard_GetType(const struct PokerHand *self);
static void HighCard_ToString(const struct PokerHand *self, char *output);
static void Pair_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit);
static const struct Card *Pair_GetHighestPair(const struct Card *cards);
static const struct Card *Pair_GetHighestPairLowerThan(const struct Card *cards, const struct Card *limit);
static int Pair_Compare(const struct PokerHand *self, const struct PokerHand *other);
static enum PokerHandType Pair_GetType(const struct PokerHand *self);
static void Pair_ToString(const struct PokerHand *self, char *output);
static void TwoPairs_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit);
static int TwoPairs_Compare(const struct PokerHand *self, const struct PokerHand *other);
static enum PokerHandType TwoPairs_GetType(const struct PokerHand *self);
static void TwoPairs_ToString(const struct PokerHand *self, char *output);
static void ThreeOfAKind_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit);
static const struct Card *ThreeOfAKind_GetHighestThreeOfAKind(const struct Card *cards);
static const struct Card *ThreeOfAKind_GetHighestThreeOfAKindLowerThan(const struct Card *cards, const struct Card *limit);
static int ThreeOfAKind_Compare(const struct PokerHand *self, const struct PokerHand *other);
static enum PokerHandType ThreeOfAKind_GetType(const struct PokerHand *self);
static void ThreeOfAKind_ToString(const struct PokerHand *self, char *output);
static void Straight_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit);
static const struct Card *Straight_GetStraight(const struct Card *cards);
static int Straight_Compare(const struct PokerHand *self, const struct PokerHand *other);
static enum PokerHandType Straight_GetType(const struct PokerHand *self);
static void Straight_ToString(const struct PokerHand *self, char *output);
static void Flush_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit);
static const struct Card *Flush_GetFlush(const struct Card *cards);
static int Flush_Compare(const struct PokerHand *self, const struct PokerHand *other);
static enum PokerHandType Flush_GetType(const struct PokerHand *self);
static void Flush_ToString(const struct PokerHand *self, char *output);
static void HighestHand_Default(struct PokerHand *self);
static int HighestHand_Compare(const struct PokerHand *self, const struct PokerHand *other);
static enum PokerHandType HighestHand_GetType(const struct PokerHand *self);
static void HighestHand_ToString(const struct PokerHand *self, char *output);

static struct Player g_players[NUMBER_OF_PLAYERS];

struct Player *Player_Init(enum PlayerId player_id, const char *name, const char *deck)
{
    size_t i = (size_t)player_id;
    if (i >= NUMBER_OF_PLAYERS) {
        return NULL;
    }
    struct Player *self = &g_players[i];
    self->name = name;
    CardDeck_Init(&self->deck, deck);
    return self;
}

size_t Player_PrettyCompare(const struct Player *self, const struct Player *other, char *output, size_t size)
{
    size_t written = 0;
    struct StringBuffer buffer;
    StringBuffer_Init(&buffer, output, size);
    struct PokerHand hand;
    int sign = CardDeck_Compare(&self->deck, &other->deck, &hand);
    if (sign == 0) {
        StringBuffer_Write(&buffer, "Tie.");
        return StringBuffer_GetWritten(&buffer);
    }
    const struct Player *winner = sign > 0 ? self : other;
    char string[64];
    hand.vtable->ToString(&hand, string);
    StringBuffer_Write(&buffer, "%s wins. - with %s", winner->name, string);
    return StringBuffer_GetWritten(&buffer);
}

static void error(const char *file, const char *function, size_t line, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Error: '");
    vfprintf(stderr, format, args);
    fprintf(stderr, "' in %s() from %s:%lu\n", function, file, line);
    va_end(args);
    exit(1);
}

static enum Value Value_FromString(const char *string)
{
    enum Value value = TWO;
    switch (string[0]) {
        case '2':
            value = TWO;
            break;
        case '3':
            value = THREE;
            break;
        case '4':
            value = FOUR;
            break;
        case '5':
            value = FIVE;
            break;
        case '6':
            value = SIX;
            break;
        case '7':
            value = SEVEN;
            break;
        case '8':
            value = EIGHT;
            break;
        case '9':
            value = NINE;
            break;
        case 'J':
            value = JACK;
            break;
        case 'Q':
            value = QUEEN;
            break;
        case 'K':
            value = KING;
            break;
        case 'A':
            value = ACE;
            break;
        default:
            ERROR("Unhandled case '%c'", string[0]);
            break;
    }
    return value;
}

static void Value_ToString(enum Value self, char *output)
{
    switch (self) {
        case TWO:
        case THREE:
        case FOUR:
        case FIVE:
        case SIX:
        case SEVEN:
        case EIGHT:
        case NINE:
            sprintf(output, "%d", self + 2);
            break;
        case JACK:
            sprintf(output, "Jack");
            break;
        case QUEEN:
            sprintf(output, "Queen");
            break;
        case KING:
            sprintf(output, "King");
            break;
        case ACE:
            sprintf(output, "Ace");
            break;
        default:
            ERROR("Unhandled case '%c'", self);
            break;
    }
}

static enum Suit Suit_FromString(const char *string)
{
    enum Suit suit = DIAMOND;
    switch (string[0]) {
        case 'D':
            suit = DIAMOND;
            break;
        case 'C':
            suit = CLUB;
            break;
        case 'H':
            suit = HEART;
            break;
        case 'S':
            suit = SPADE;
            break;
        default:
            ERROR("Unhandled case '%c'", string[0]);
            break;
    }
    return suit;
}

static void StringBuffer_Init(struct StringBuffer *self, char *buffer, size_t size)
{
    self->buffer = buffer;
    self->size = size;
    self->written = 0;
}

static void StringBuffer_Write(struct StringBuffer *self, const char *format, ...)
{
    size_t remaining = self->size - self->written;
    va_list args;
    va_start(args, format);
    size_t written = vsnprintf(&self->buffer[self->written], remaining, format, args);
    va_end(args);
    if (written < 0) {
        ERROR("Encoding error");
    } else if (written >= remaining) {
        ERROR("Not enough space");
    } else {
        self->written += written;
    }
}

static size_t StringBuffer_GetWritten(const struct StringBuffer *self)
{
    return self->written;
}

static void CardDeck_Init(struct CardDeck *self, const char *deck)
{
    char string[3];
    struct StringBuffer buffer;
    StringBuffer_Init(&buffer, string, sizeof(string) / sizeof(string[0]));
    size_t j = 0;
    for (size_t i = 0; i < strlen(deck) && j < sizeof(self->cards) / sizeof(self->cards[0]); i++) {
        if (deck[i] == ' ') {
            continue;
        }
        switch (StringBuffer_GetWritten(&buffer)) {
            case 0:
                StringBuffer_Write(&buffer, "%c", deck[i]);
                break;
            case 1:
                StringBuffer_Write(&buffer, "%c", deck[i]);
                Card_FromString(&self->cards[j], string);
                j += 1;
                StringBuffer_Init(&buffer, string, sizeof(string) / sizeof(string[0]));
                break;
            default:
                ERROR("Unhandled case '%c'", deck[i]);
                break;
        }
    }
}

static void CardDeck_Copy(struct CardDeck *self, const struct CardDeck *other)
{
    for (size_t i = 0; i < sizeof(self->cards) / sizeof(self->cards[0]); i++) {
        Card_Copy(&self->cards[i], &other->cards[i]);
    }
}

static int CardDeck_Compare(const struct CardDeck *self, const struct CardDeck *other, struct PokerHand *hand)
{
    struct PokerHand selfHand = CardDeck_GetHighestPokerHand(self);
    struct PokerHand otherHand = CardDeck_GetHighestPokerHand(other);
    while (selfHand.vtable->GetType(&selfHand) != NO_HAND || otherHand.vtable->GetType(&otherHand) != NO_HAND) {
        int sign = selfHand.vtable->Compare(&selfHand, &otherHand);
        if (sign > 0) {
            if (hand != NULL) {
                *hand = selfHand;
            }
            return sign;
        } else if (sign < 0) {
            if (hand != NULL) {
                *hand = otherHand;
            }
            return sign;
        }
        selfHand = CardDeck_GetHighestPokerHandLowerThan(self, &selfHand);
        otherHand = CardDeck_GetHighestPokerHandLowerThan(other, &otherHand);
    }
    return 0;
}

static struct PokerHand CardDeck_GetHighestPokerHand(const struct CardDeck *self)
{
    struct PokerHand limit;
    HighestHand_Default(&limit);
    return CardDeck_GetHighestPokerHandLowerThan(self, &limit);
}

static struct PokerHand CardDeck_GetHighestPokerHandLowerThan(const struct CardDeck *self, const struct PokerHand *limit)
{
    struct CardDeck copy;
    CardDeck_Copy(&copy, self);
    CardDeck_Sort(&copy);
    struct PokerHand hand;
    Flush_FromCardsLowerThan(&hand, copy.cards, limit);
    if (hand.vtable->GetType(&hand) != NO_HAND) {
        return hand;
    }
    Straight_FromCardsLowerThan(&hand, copy.cards, limit);
    if (hand.vtable->GetType(&hand) != NO_HAND) {
        return hand;
    }
    ThreeOfAKind_FromCardsLowerThan(&hand, copy.cards, limit);
    if (hand.vtable->GetType(&hand) != NO_HAND) {
        return hand;
    }
    TwoPairs_FromCardsLowerThan(&hand, copy.cards, limit);
    if (hand.vtable->GetType(&hand) != NO_HAND) {
        return hand;
    }
    Pair_FromCardsLowerThan(&hand, copy.cards, limit);
    if (hand.vtable->GetType(&hand) != NO_HAND) {
        return hand;
    }
    HighCard_FromCardsLowerThan(&hand, copy.cards, limit);
    if (hand.vtable->GetType(&hand) != NO_HAND) {
        return hand;
    }
    return hand;
}

static void CardDeck_Sort(struct CardDeck *self)
{
    size_t size = sizeof(self->cards) / sizeof(self->cards[0]);
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            struct Card *lhs = &self->cards[j];
            struct Card *rhs = &self->cards[j + 1];
            if (Card_Compare(lhs, rhs) < 0) {
                struct Card temp;
                Card_Copy(&temp, lhs);
                Card_Copy(lhs, rhs);
                Card_Copy(rhs, &temp);
            }
        }
    }
}

static void Card_Init(struct Card *self, enum Value value, enum Suit suit)
{
    self->value = value;
    self->suit = suit;
}

static void Card_Copy(struct Card *self, const struct Card *other)
{
    self->value = other->value;
    self->suit = other->suit;
}

static void Card_FromString(struct Card *self, const char *string)
{
    self->value = Value_FromString(&string[0]);
    self->suit = Suit_FromString(&string[1]);
}

static int Card_Compare(const struct Card *self, const struct Card *other)
{
    if (self->value == other->value) {
        return 0;
    }
    return self->value > other->value ? 1 : -1;
}

static bool Card_DoesFollow(const struct Card *self, const struct Card *other)
{
    return self->value - other->value == 1;
}

static bool Card_SuitEquals(const struct Card *self, const struct Card *other)
{
    return self->suit == other->suit;
}

static enum Value Card_GetValue(const struct Card *self)
{
    return self->value;
}

static enum Suit Card_GetSuit(const struct Card *self)
{
    return self->suit;
}

static int PokerHand_Compare(const struct PokerHand *self, const struct PokerHand *other)
{
    int sign = self->vtable->GetType(self) - other->vtable->GetType(other);
    if (sign == 0) {
        return sign;
    }
    return sign > 0 ? 1 : -1;
}

static void NoHand_Default(struct PokerHand *self)
{
    static const struct PokerHandMethods vtable = {
        .Compare = &NoHand_Compare,
        .GetType = &NoHand_GetType,
        .ToString = &NoHand_ToString,
    };
    self->vtable = &vtable;
}

static int NoHand_Compare(const struct PokerHand *self, const struct PokerHand *other)
{
    return PokerHand_Compare(self, other);
}

static enum PokerHandType NoHand_GetType(const struct PokerHand *self)
{
    return NO_HAND;
}

static void NoHand_ToString(const struct PokerHand *self, char *output)
{
    ERROR("Unimplemented method");
}

static void HighCard_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit)
{
    static const struct PokerHandMethods vtable = {
        .Compare = &HighCard_Compare,
        .GetType = &HighCard_GetType,
        .ToString = &HighCard_ToString,
    };
    self->vtable = &vtable;
    int sign = PokerHand_Compare(self, limit);
    if (sign > 0) {
        NoHand_Default(self);
        return;
    }
    const struct Card *card = NULL;
    for (size_t i = 0; i < NUMBER_OF_CARDS; i++) {
        if (sign == 0 && Card_Compare(&cards[i], &limit->value.HighCard.card) >= 0) {
            continue;
        }
        card = &cards[i];
        break;
    }
    if (card == NULL) {
        NoHand_Default(self);
        return;
    }
    Card_Copy(&self->value.HighCard.card, card);
}

static int HighCard_Compare(const struct PokerHand *self, const struct PokerHand *other)
{
    int sign = PokerHand_Compare(self, other);
    if (sign != 0) {
        return sign;
    }
    return Card_Compare(&self->value.HighCard.card, &other->value.HighCard.card);
}

static enum PokerHandType HighCard_GetType(const struct PokerHand *self)
{
    return HIGH_CARD;
}

static void HighCard_ToString(const struct PokerHand *self, char *output)
{
    char value[16];
    Value_ToString(Card_GetValue(&self->value.HighCard.card), value);
    sprintf(output, "high card: %s", value);
}

static void Pair_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit)
{
    static const struct PokerHandMethods vtable = {
        .Compare = &Pair_Compare,
        .GetType = &Pair_GetType,
        .ToString = &Pair_ToString,
    };
    self->vtable = &vtable;
    int sign = PokerHand_Compare(self, limit);
    if (sign > 0) {
        NoHand_Default(self);
        return;
    }
    const struct Card *card = NULL;
    if (sign == 0) {
        card = Pair_GetHighestPairLowerThan(cards, &limit->value.Pair.card);
    } else {
        card = Pair_GetHighestPair(cards);
    }
    if (card == NULL) {
        NoHand_Default(self);
        return;
    }
    Card_Copy(&self->value.Pair.card, card);
}

static const struct Card *Pair_GetHighestPair(const struct Card *cards)
{
    for (size_t i = 0; i < NUMBER_OF_CARDS - 1; i++) {
        if (Card_Compare(&cards[i], &cards[i + 1]) == 0) {
            return &cards[i];
        }
    }
    return NULL;
}

static const struct Card *Pair_GetHighestPairLowerThan(const struct Card *cards, const struct Card *limit)
{
    for (size_t i = 0; i < NUMBER_OF_CARDS - 1; i++) {
        if (Card_Compare(&cards[i], limit) >= 0) {
            continue;
        }
        if (Card_Compare(&cards[i], &cards[i + 1]) == 0) {
            return &cards[i];
        }
    }
    return NULL;
}

static int Pair_Compare(const struct PokerHand *self, const struct PokerHand *other)
{
    int sign = PokerHand_Compare(self, other);
    if (sign != 0) {
        return sign;
    }
    return Card_Compare(&self->value.Pair.card, &other->value.Pair.card);
}

static enum PokerHandType Pair_GetType(const struct PokerHand *self)
{
    return PAIR;
}

static void Pair_ToString(const struct PokerHand *self, char *output)
{
    char value[16];
    Value_ToString(Card_GetValue(&self->value.Pair.card), value);
    sprintf(output, "pair: %s", value);
}

static void TwoPairs_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit)
{
    static const struct PokerHandMethods vtable = {
        .Compare = &TwoPairs_Compare,
        .GetType = &TwoPairs_GetType,
        .ToString = &TwoPairs_ToString,
    };
    self->vtable = &vtable;
    int sign = PokerHand_Compare(self, limit);
    if (sign > 0) {
        NoHand_Default(self);
        return;
    }
    const struct Card *card = NULL;
    if (sign == 0) {
        card = Pair_GetHighestPairLowerThan(cards, &limit->value.TwoPairs.firstCard);
    } else {
        card = Pair_GetHighestPair(cards);
    }
    if (card == NULL) {
        NoHand_Default(self);
        return;
    }
    Card_Copy(&self->value.TwoPairs.firstCard, card);
    card = Pair_GetHighestPairLowerThan(cards, card);
    if (card == NULL) {
        NoHand_Default(self);
        return;
    }
    Card_Copy(&self->value.TwoPairs.secondCard, card);
}

static int TwoPairs_Compare(const struct PokerHand *self, const struct PokerHand *other)
{
    int sign = PokerHand_Compare(self, other);
    if (sign != 0) {
        return sign;
    }
    sign = Card_Compare(&self->value.TwoPairs.firstCard, &other->value.TwoPairs.firstCard);
    if (sign != 0) {
        return sign;
    }
    return Card_Compare(&self->value.TwoPairs.secondCard, &other->value.TwoPairs.secondCard);
}

static enum PokerHandType TwoPairs_GetType(const struct PokerHand *self)
{
    return TWO_PAIRS;
}

static void TwoPairs_ToString(const struct PokerHand *self, char *output)
{
    char firstValue[16];
    Value_ToString(Card_GetValue(&self->value.TwoPairs.firstCard), firstValue);
    char secondValue[16];
    Value_ToString(Card_GetValue(&self->value.TwoPairs.secondCard), secondValue);
    sprintf(output, "two pairs: %s over %s", firstValue, secondValue);
}

static void ThreeOfAKind_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit)
{
    static const struct PokerHandMethods vtable = {
        .Compare = &ThreeOfAKind_Compare,
        .GetType = &ThreeOfAKind_GetType,
        .ToString = &ThreeOfAKind_ToString,
    };
    self->vtable = &vtable;
    int sign = PokerHand_Compare(self, limit);
    if (sign > 0) {
        NoHand_Default(self);
        return;
    }
    const struct Card *card = NULL;
    if (sign == 0) {
        card = ThreeOfAKind_GetHighestThreeOfAKindLowerThan(cards, &limit->value.ThreeOfAKind.card);
    } else {
        card = ThreeOfAKind_GetHighestThreeOfAKind(cards);
    }
    if (card == NULL) {
        NoHand_Default(self);
        return;
    }
    Card_Copy(&self->value.ThreeOfAKind.card, card);
}

static const struct Card *ThreeOfAKind_GetHighestThreeOfAKind(const struct Card *cards)
{
    for (size_t i = 0; i < NUMBER_OF_CARDS - 2; i++) {
        if (Card_Compare(&cards[i], &cards[i + 1]) == 0 && Card_Compare(&cards[i + 1], &cards[i + 2]) == 0) {
            return &cards[i];
        }
    }
    return NULL;
}

static const struct Card *ThreeOfAKind_GetHighestThreeOfAKindLowerThan(const struct Card *cards, const struct Card *limit)
{
    for (size_t i = 0; i < NUMBER_OF_CARDS - 2; i++) {
        if (Card_Compare(&cards[i], limit) >= 0) {
            continue;
        }
        if (Card_Compare(&cards[i], &cards[i + 1]) == 0 && Card_Compare(&cards[i + 1], &cards[i + 2]) == 0) {
            return &cards[i];
        }
    }
    return NULL;
}

static int ThreeOfAKind_Compare(const struct PokerHand *self, const struct PokerHand *other)
{
    int sign = PokerHand_Compare(self, other);
    if (sign != 0) {
        return sign;
    }
    return Card_Compare(&self->value.ThreeOfAKind.card, &other->value.ThreeOfAKind.card);
}

static enum PokerHandType ThreeOfAKind_GetType(const struct PokerHand *self)
{
    return THREE_OF_A_KIND;
}

static void ThreeOfAKind_ToString(const struct PokerHand *self, char *output)
{
    char value[16];
    Value_ToString(Card_GetValue(&self->value.ThreeOfAKind.card), value);
    sprintf(output, "three of a kind: %s", value);
}

static void Straight_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit)
{
    static const struct PokerHandMethods vtable = {
        .Compare = &Straight_Compare,
        .GetType = &Straight_GetType,
        .ToString = &Straight_ToString,
    };
    self->vtable = &vtable;
    int sign = PokerHand_Compare(self, limit);
    if (sign > 0) {
        NoHand_Default(self);
        return;
    }
    const struct Card *card = Straight_GetStraight(cards);
    if (sign == 0 && Card_Compare(card, &limit->value.Straight.card) >= 0) {
        card = NULL;
    }
    if (card == NULL) {
        NoHand_Default(self);
        return;
    }
    Card_Copy(&self->value.Straight.card, card);
}

static const struct Card *Straight_GetStraight(const struct Card *cards)
{
    for (size_t i = 0; i < NUMBER_OF_CARDS - 1; i++) {
        if (!Card_DoesFollow(&cards[i], &cards[i + 1])) {
            return NULL;
        }
    }
    return &cards[0];
}

static int Straight_Compare(const struct PokerHand *self, const struct PokerHand *other)
{
    int sign = PokerHand_Compare(self, other);
    if (sign != 0) {
        return sign;
    }
    return Card_Compare(&self->value.Straight.card, &other->value.Straight.card);
}

static enum PokerHandType Straight_GetType(const struct PokerHand *self)
{
    return STRAIGHT;
}

static void Straight_ToString(const struct PokerHand *self, char *output)
{
    char value[16];
    Value_ToString(Card_GetValue(&self->value.Straight.card), value);
    sprintf(output, "straight: %s", value);
}

static void Flush_FromCardsLowerThan(struct PokerHand *self, const struct Card *cards, const struct PokerHand *limit)
{
    static const struct PokerHandMethods vtable = {
        .Compare = &Flush_Compare,
        .GetType = &Flush_GetType,
        .ToString = &Flush_ToString,
    };
    self->vtable = &vtable;
    int sign = PokerHand_Compare(self, limit);
    if (sign > 0) {
        NoHand_Default(self);
        return;
    }
    const struct Card *card = Flush_GetFlush(cards);
    if (sign == 0 && Card_Compare(card, &limit->value.Flush.card) >= 0) {
        card = NULL;
    }
    if (card == NULL) {
        NoHand_Default(self);
        return;
    }
    Card_Copy(&self->value.Flush.card, card);
}

static const struct Card *Flush_GetFlush(const struct Card *cards)
{
    for (size_t i = 0; i < NUMBER_OF_CARDS - 1; i++) {
        if (!Card_SuitEquals(&cards[i], &cards[i + 1])) {
            return NULL;
        }
    }
    return &cards[0];
}

static int Flush_Compare(const struct PokerHand *self, const struct PokerHand *other)
{
    int sign = PokerHand_Compare(self, other);
    if (sign != 0) {
        return sign;
    }
    return Card_Compare(&self->value.Flush.card, &other->value.Flush.card);
}

static enum PokerHandType Flush_GetType(const struct PokerHand *self)
{
    return FLUSH;
}

static void Flush_ToString(const struct PokerHand *self, char *output)
{
    char value[16];
    Value_ToString(Card_GetValue(&self->value.Flush.card), value);
    sprintf(output, "flush: %s", value);
}

static void HighestHand_Default(struct PokerHand *self)
{
    static const struct PokerHandMethods vtable = {
        .Compare = &HighestHand_Compare,
        .GetType = &HighestHand_GetType,
        .ToString = &HighestHand_ToString,
    };
    self->vtable = &vtable;
}

static int HighestHand_Compare(const struct PokerHand *self, const struct PokerHand *other)
{
    return PokerHand_Compare(self, other);
}

static enum PokerHandType HighestHand_GetType(const struct PokerHand *self)
{
    return HIGHEST_HAND;
}

static void HighestHand_ToString(const struct PokerHand *self, char *output)
{
    ERROR("Unimplemented method");
}

