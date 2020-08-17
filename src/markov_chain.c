#include <necklet/markov_chain.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#ifndef MC_MAX_WORDS
#    define MC_MAX_WORDS (4096)
#endif

struct string {
    const char *buffer;
    size_t size;
};

struct link {
    struct node *next;
    uint32_t counter;
};

struct node {
    struct string word;
    struct link nexts[MC_MAX_WORDS];
    uint32_t counter;
};

struct mc {
    struct node nodes[MC_MAX_WORDS];
};

static void mc_default(struct mc *self);
static struct node *mc_get_or_insert(struct mc *self, const struct string *word);
static const struct node *mc_get_node_with(const struct mc *self, const struct string *word);
static const struct node *mc_get_empty_node(const struct mc *self);
static void node_default(struct node *self);
static void node_init(struct node *self, const struct string *word);
static void node_link_to(struct node *self, struct node *other);
static bool node_has_word(const struct node *self, const struct string *word);
static const struct string *node_get_word(const struct node *self);
static struct link *node_get_or_insert(struct node *self, struct node *next);
static struct node *node_randomly_get_next(const struct node *self);
static void link_default(struct link *self);
static void link_init(struct link *self, struct node *next);
static bool link_leads_to(const struct link *self, const struct node *next);
static void link_increment(struct link *self);
static struct node *link_get_next(const struct link *self);
static uint32_t link_get_counter(const struct link *self);
static void string_default(struct string *self);
static void string_init(struct string *self, const char *buffer, size_t size);
static void string_copy(struct string *self, const struct string *other);
static const char *string_get_buffer(const struct string *self);
static size_t string_get_size(const struct string *self);
static bool string_equals(const struct string *self, const struct string *other);
static size_t get_next_word(const char **next, const char *buffer, size_t size);

struct mc g_mc;

struct mc *mc_from_string(const char *input, size_t input_size)
{
    struct mc *self = &g_mc;
    // Revert back the model to the default value.
    mc_default(self);
    // Fill the model with encounter words.
    const char *token = input;
    size_t remaining = input_size;
    const char *next = NULL;
    size_t size = get_next_word(&next, token, remaining);
    struct string string;
    string_init(&string, token, size);
    struct node *node = mc_get_or_insert(self, &string);
    remaining = remaining > next - token ? remaining - (next - token) : 0;
    token = next;
    while (remaining > 0) {
        size = get_next_word(&next, token, remaining);
        if (size > 0) {
            string_init(&string, token, size);
            struct node *other = mc_get_or_insert(self, &string);
            node_link_to(node, other);
            node = other;
        }
        remaining = remaining > next - token ? remaining - (next - token) : 0;
        token = next;
    }
    return self;
}

size_t mc_generate(const struct mc *self, char *output, size_t output_size, const char *first_word)
{
    size_t written = 0;
    struct string string;
    string_init(&string, first_word, strlen(first_word));
    const struct node *node = mc_get_node_with(self, &string);
    while (node != NULL) {
        if (written != 0) {
            if (1 > output_size - written) {
                break;
            }
            memcpy(&output[written], " ", 1);
            written += 1;
        }
        const struct string *word = node_get_word(node);
        if (string_get_size(word) > output_size - written) {
            break;
        }
        memcpy(&output[written], string_get_buffer(word), string_get_size(word));
        written += string_get_size(word);
        node = node_randomly_get_next(node);
    }
    return written;
}

static void mc_default(struct mc *self)
{
    for (size_t i = 0; i < sizeof(self->nodes) / sizeof(self->nodes[0]); i++) {
        node_default(&self->nodes[i]);
    }
}

static struct node *mc_get_or_insert(struct mc *self, const struct string *word)
{
    struct node *node = (struct node *)mc_get_node_with(self, word);
    if (node != NULL) {
        return node;
    }
    node = (struct node *)mc_get_empty_node(self);
    if (node != NULL) {
        node_init(node, word);
        return node;
    }
    return NULL;
}

static const struct node *mc_get_node_with(const struct mc *self, const struct string *word)
{
    for (size_t i = 0; i < sizeof(self->nodes) / sizeof(self->nodes[0]); i++) {
        const struct node *node = &self->nodes[i];
        if (node_has_word(node, word)) {
            return node;
        }
    }
    return NULL;
}

static const struct node *mc_get_empty_node(const struct mc *self)
{
    struct string empty;
    string_default(&empty);
    for (size_t i = 0; i < sizeof(self->nodes) / sizeof(self->nodes[0]); i++) {
        const struct node *node = &self->nodes[i];
        if (node_has_word(node, &empty)) {
            return node;
        }
    }
    return NULL;
}

static void node_default(struct node *self)
{
    string_default(&self->word);
    for (size_t i = 0; i < sizeof(self->nexts) / sizeof(self->nexts[0]); i++) {
        link_default(&self->nexts[i]);
    }
    self->counter = 0;
}

static void node_init(struct node *self, const struct string *word)
{
    string_copy(&self->word, word);
    for (size_t i = 0; i < sizeof(self->nexts) / sizeof(self->nexts[0]); i++) {
        link_default(&self->nexts[i]);
    }
    self->counter = 0;
}

static void node_link_to(struct node *self, struct node *other)
{
    struct link *link = node_get_or_insert(self, other);
    link_increment(link);
    self->counter += 1;
}

static bool node_has_word(const struct node *self, const struct string *word)
{
    return string_equals(&self->word, word);
}

static const struct string *node_get_word(const struct node *self)
{
    return &self->word;
}

static struct link *node_get_or_insert(struct node *self, struct node *next)
{
    for (size_t i = 0; i < sizeof(self->nexts) / sizeof(self->nexts[0]); i++) {
        struct link *link = &self->nexts[i];
        if (link_leads_to(link, next)) {
            return link;
        }
    }
    for (size_t i = 0; i < sizeof(self->nexts) / sizeof(self->nexts[0]); i++) {
        struct link *link = &self->nexts[i];
        if (link_leads_to(link, NULL)) {
            link_init(link, next);
            return link;
        }
    }
    return NULL;
}

static struct node *node_randomly_get_next(const struct node *self)
{
    if (self->counter == 0) {
        return NULL;
    }
    uint32_t rand_ = rand();
    uint32_t choice = rand_ % self->counter;
    uint32_t sum = 0;
    for (size_t i = 0; i < sizeof(self->nexts) / sizeof(self->nexts[0]); i++) {
        const struct link *link = &self->nexts[i];
        sum += link_get_counter(link);
        if (sum > choice) {
            return link_get_next(link);
        }
    }
    return NULL;
}

static void link_default(struct link *self)
{
    self->next = NULL;
    self->counter = 0;
}

static void link_init(struct link *self, struct node *next)
{
    self->next = next;
    self->counter = 0;
}

static bool link_leads_to(const struct link *self, const struct node *next)
{
    return self->next == next;
}

static void link_increment(struct link *self)
{
    self->counter += 1;
}

static struct node *link_get_next(const struct link *self)
{
    return self->next;
}

static uint32_t link_get_counter(const struct link *self)
{
    return self->counter;
}

static void string_default(struct string *self)
{
    self->buffer = NULL;
    self->size = 0;
}

static void string_init(struct string *self, const char *buffer, size_t size)
{
    self->buffer = buffer;
    self->size = size;
}

static void string_copy(struct string *self, const struct string *other)
{
    self->buffer = other->buffer;
    self->size = other->size;
}

static const char *string_get_buffer(const struct string *self)
{
    return self->buffer;
}

static size_t string_get_size(const struct string *self)
{
    return self->size;
}

static bool string_equals(const struct string *self, const struct string *other)
{
    if (string_get_size(self) != string_get_size(other)) {
        return false;
    }
    return memcmp(self->buffer, other->buffer, self->size) == 0;
}

static size_t get_next_word(const char **next, const char *buffer, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        if (buffer[i] == ' ') {
            *next = &buffer[i + 1];
            return i;
        }
    }
    *next = &buffer[size + 1];
    return size;
}

