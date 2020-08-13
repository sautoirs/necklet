#include <necklet/bowling.h>

#include <stdbool.h>
#include <string.h>

#define FRAMES_SIZE 12

// A frame contains multiple rolls (max 2). A game is a suite of 12 frame max.
struct frame {
    const char *rolls;
    size_t rolls_size;
};

// Build an empty frame
static void frame_default(struct frame *self);
// Build a frame from a given string and return a pointer to the next frame in that string
static const char *frame_from_string(struct frame *self, const char *string, size_t size);
// Return the number of points in a frame excluding the bonuses
static uint32_t frame_get_rolls_points(const struct frame *self);
// Return the number of points scored in the first roll
static uint32_t frame_get_first_roll_points(const struct frame *self);
// Return the number of bonus points if the previous frame was a spare
static uint32_t frame_get_spare_bonus_points(const struct frame *self);
// Return the number of bonus points if the previous frame was a strike
static uint32_t frame_get_strike_bonus_points(const struct frame *self, const struct frame *next);
// Return true if the frame is a spare
static bool frame_is_spare(const struct frame *self);
// Return true if the frame is a strike
static bool frame_is_strike(const struct frame *self);
// Fill an array of frame from a given string
static void frames_from_string(struct frame *array, size_t array_size, const char *string, size_t string_size);

uint32_t count_score(const char *input, size_t size)
{
    struct frame frames[FRAMES_SIZE];
    frames_from_string(&frames[0], FRAMES_SIZE, input, size);
    uint32_t points = 0;
    for (size_t i = 0; i < (FRAMES_SIZE - 2); i++) {
        struct frame *frame = &frames[i];
        points += frame_get_rolls_points(frame);
        if (frame_is_spare(frame)) {
            points += frame_get_spare_bonus_points(&frames[i + 1]);
        } else if (frame_is_strike(frame)) {
            points += frame_get_strike_bonus_points(&frames[i + 1], &frames[i + 2]);
        }
    }
    return points;
}

static void frame_default(struct frame *self)
{
    self->rolls = NULL;
    self->rolls_size = 0;
}

static const char *frame_from_string(struct frame *self, const char *string, size_t size)
{
    frame_default(self);
    self->rolls = string;
    const char *token = NULL;
    for (size_t i = 0; (i < size) && (token == NULL); i++) {
        if (string[i] != ' ') {
            self->rolls_size += 1;
        } else {
            token = &string[i + 1];
        }
    }
    return token;
}

static uint32_t frame_get_rolls_points(const struct frame *self)
{
    uint32_t points = 0;
    for (size_t i = 0; i < self->rolls_size; i++) {
        switch (self->rolls[i]) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                points += self->rolls[i] - '0';
                break;
            case '/':
            case 'X':
                points = 10;
                break;
            default:
                break;
        }
    }
    return points;
}

static uint32_t frame_get_first_roll_points(const struct frame *self)
{
    uint32_t points = 0;
    if (self->rolls_size > 0) {
        switch (self->rolls[0]) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                points = self->rolls[0] - '0';
                break;
            case 'X':
                points = 10;
                break;
            default:
                break;
        }
    }
    return points;
}

static uint32_t frame_get_spare_bonus_points(const struct frame *self)
{
    return frame_get_first_roll_points(self);
}

static uint32_t frame_get_strike_bonus_points(const struct frame *self, const struct frame *next)
{
    uint32_t points = 0;
    if (frame_is_strike(self)) {
        points = frame_get_rolls_points(self) + frame_get_first_roll_points(next);
    } else {
        points = frame_get_rolls_points(self);
    }
    return points;
}

static bool frame_is_spare(const struct frame *self)
{
    for (size_t i = 0; i < self->rolls_size; i++) {
        if (self->rolls[i] == '/') {
            return true;
        }
    }
    return false;
}

static bool frame_is_strike(const struct frame *self)
{
    for (size_t i = 0; i < self->rolls_size; i++) {
        if (self->rolls[i] == 'X') {
            return true;
        }
    }
    return false;
}

static void frames_from_string(struct frame *array, size_t array_size, const char *string, size_t string_size)
{
    const char *token = string;
    size_t remaining = string_size;
    for (size_t i = 0; i < array_size; i++) {
        if (token != NULL) {
            const char *next = frame_from_string(&array[i], token, remaining);
            remaining -= next - token;
            token = next;
        } else {
            frame_default(&array[i]);
        }
    }
}

