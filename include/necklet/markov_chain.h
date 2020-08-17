#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <stddef.h>

/// A markov chain model
struct mc;

/// Build a markov chain from a given text
///
/// The markov chain is filled with words and the probability for a given word to be followed by another one.
struct mc *mc_from_string(const char *input, size_t input_size);

/// Generate a text from a markov chain
///
/// The generated output string start with the first_word.
size_t mc_generate(const struct mc *self, char *output, size_t output_size, const char *first_word);

#endif

