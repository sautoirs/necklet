#include <necklet/poker_hands.h>

#include <stdarg.h>
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
            const struct Card *card;
        } HighCard;
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
static int CardDeck_Compare(const struct CardDeck *self, const struct CardDeck *other, struct PokerHand *hand);
static struct PokerHand CardDeck_GetHighestPokerHand(const struct CardDeck *self);
static struct PokerHand CardDeck_GetHighestPokerHandLowerThan(const struct CardDeck *self, const struct PokerHand *limit);
static void Card_Init(struct Card *self, enum Value value, enum Suit suit);
static void Card_FromString(struct Card *self, const char *string);
static int Card_Compare(const struct Card *self, const struct Card *other);
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
    fprintf(stderr, "' inside %s() in %s:%lu\n", function, file, line);
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
    struct PokerHand hand;
    HighCard_FromCardsLowerThan(&hand, self->cards, limit);
    if (hand.vtable->GetType(&hand) != NO_HAND && hand.vtable->Compare(&hand, limit) < 0) {
        return hand;
    }
    return hand;
}

static void Card_Init(struct Card *self, enum Value value, enum Suit suit)
{
    self->value = value;
    self->suit = suit;
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
        if (sign < 0 || Card_Compare(&cards[i], limit->value.HighCard.card) < 0) {
            if (card == NULL || Card_Compare(&cards[i], card) > 0) {
                card = &cards[i];
            }
        }
    }
    if (card == NULL) {
        NoHand_Default(self);
        return;
    }
    self->value.HighCard.card = card;
}

static int HighCard_Compare(const struct PokerHand *self, const struct PokerHand *other)
{
    int sign = PokerHand_Compare(self, other);
    if (sign != 0) {
        return sign;
    }
    return Card_Compare(self->value.HighCard.card, other->value.HighCard.card);
}

static enum PokerHandType HighCard_GetType(const struct PokerHand *self)
{
    return HIGH_CARD;
}

static void HighCard_ToString(const struct PokerHand *self, char *output)
{
    char value[16];
    Value_ToString(Card_GetValue(self->value.HighCard.card), value);
    sprintf(output, "high card: %s", value);
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

