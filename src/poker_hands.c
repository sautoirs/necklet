#include <necklet/poker_hands.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALUE_SIZE 6
#define NUMBER_OF_CARDS 5
#define NUMBER_OF_CARD_HANDS 2

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

struct PokerHand {
    const char *name;
    struct CardDeck deck;
};

struct StringBuffer {
    char *buffer;
    size_t size;
    size_t written;
};

static void error(const char *file, const char *function, size_t line, const char *format, ...);
static enum Value Value_FromString(const char *string);
static void Value_ToString(enum Value self, char *output);
static enum Suit Suit_FromString(const char *string);
static void StringBuffer_Init(struct StringBuffer *self, char *buffer, size_t size);
static void StringBuffer_Write(struct StringBuffer *self, const char *format, ...);
static size_t StringBuffer_GetWritten(const struct StringBuffer *self);
static void CardDeck_Init(struct CardDeck *self, const char *deck);
static int CardDeck_Compare(const struct CardDeck *self, const struct CardDeck *other);
static const struct Card *CardDeck_GetHighestCard(const struct CardDeck *self);
static void Card_Init(struct Card *self, enum Value value, enum Suit suit);
static void Card_FromString(struct Card *self, const char *string);
static int Card_Compare(const struct Card *self, const struct Card *other);
static enum Value Card_GetValue(const struct Card *self);
static enum Suit Card_GetSuit(const struct Card *self);

static struct PokerHand g_pokerHands[NUMBER_OF_CARD_HANDS];

struct PokerHand *PokerHand_Init(enum Player player, const char *name, const char *deck)
{
    size_t i = (size_t)player;
    if (i >= NUMBER_OF_CARD_HANDS) {
        return NULL;
    }
    struct PokerHand *self = &g_pokerHands[i];
    self->name = name;
    CardDeck_Init(&self->deck, deck);
    return self;
}

size_t PokerHand_PrettyCompare(const struct PokerHand *self, const struct PokerHand *other, char *output, size_t size)
{
    size_t written = 0;
    struct StringBuffer buffer;
    StringBuffer_Init(&buffer, output, size);
    int sign = CardDeck_Compare(&self->deck, &other->deck);
    if (sign == 0) {
        StringBuffer_Write(&buffer, "Tie.");
        return StringBuffer_GetWritten(&buffer);
    }
    const struct PokerHand *winner = sign > 0 ? self : other;
    StringBuffer_Write(&buffer, "%s wins.", winner->name);
    const struct Card *highest = CardDeck_GetHighestCard(&winner->deck);
    char value[VALUE_SIZE];
    Value_ToString(Card_GetValue(highest), value);
    StringBuffer_Write(&buffer, " - with high card: %s", value);
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

static int CardDeck_Compare(const struct CardDeck *self, const struct CardDeck *other)
{
    return Card_Compare(CardDeck_GetHighestCard(self), CardDeck_GetHighestCard(other));
}

static const struct Card *CardDeck_GetHighestCard(const struct CardDeck *self)
{
    const struct Card *highest = &self->cards[0];
    for (size_t i = 1; i < sizeof(self->cards) / sizeof(self->cards[0]); i++) {
        if (Card_Compare(&self->cards[i], &self->cards[i - 1])) {
            highest = &self->cards[i];
        }
    }
    return highest;
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

