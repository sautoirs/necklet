#include <catch2/catch.hpp>

#include <cstdlib>
#include <string>

#include <markov_chain.c>

SCENARIO("Build a markov chain from a given text", "[markov_chain]") {
    GIVEN("A text with repeated words") {
        WHEN("the input text is \"The way to get started is to quit talking and begin doing.\"") {
            THEN("the resulting model is valid") {
                std::string input = "The way to get started is to quit talking and begin doing.";
                struct mc *mc = mc_from_string(input.c_str(), input.size());
                REQUIRE(mc != NULL);
                REQUIRE(mc->nodes[0].word.size == 3);
                REQUIRE(mc->nodes[0].nexts[0].next->word.buffer == &input.c_str()[4]);
                REQUIRE(mc->nodes[2].word.size == 2);
                REQUIRE(mc->nodes[2].counter == 2);
                REQUIRE(mc->nodes[2].nexts[0].counter == 1);
                REQUIRE(mc->nodes[2].nexts[1].counter == 1);
                REQUIRE(mc->nodes[2].nexts[2].counter == 0);
                REQUIRE(mc->nodes[2].nexts[0].next->word.buffer == &input.c_str()[11]);
            }
        }
    }
}

SCENARIO("Generate a new text from a given one", "[markov_chain]") {
    GIVEN("A text with repeated words") {
        WHEN("the input text is \"The way to get started is to quit talking and begin doing.\"") {
            std::string output = std::string(128, 'a');
            THEN("the resulting text looks generated") {
                std::string input = "The way to get started is to quit talking and begin doing.";
                std::srand(0);
                struct mc *mc = mc_from_string(input.c_str(), input.size());
                size_t written = mc_generate(mc, &output[0], output.size(), "The");
                output.resize(written);
                REQUIRE(mc != NULL);
                REQUIRE(output == "The way to quit talking and begin doing.");

                std::srand(2);
                mc = mc_from_string(input.c_str(), input.size());
                written = mc_generate(mc, &output[0], output.size(), "The");
                output.resize(written);
                REQUIRE(mc != NULL);
                REQUIRE(output == "The way to get started is to get started");
            }
        }
    }
}

