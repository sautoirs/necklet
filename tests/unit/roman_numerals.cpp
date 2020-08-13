#include <catch2/catch.hpp>

#include <string>

#include <roman_numerals.c>

SCENARIO("Basic numbers are represented with a single letter", "[roman_numerals]") {
    GIVEN("An arabic number which has a basic roman representation") {
        std::string output = std::string(128, 'a');
        WHEN("the input is 1") {
            THEN("the function output is \"I\"") {
                size_t written = to_roman(&output[0], output.size(), 1);
                output.resize(written);
                REQUIRE(output == "I");
            }
        }

        WHEN("the input is 5") {
            THEN("the function output is \"V\"") {
                size_t written = to_roman(&output[0], output.size(), 5);
                output.resize(written);
                REQUIRE(output == "V");
            }
        }

        WHEN("the input is 10") {
            THEN("the function output is \"X\"") {
                size_t written = to_roman(&output[0], output.size(), 10);
                output.resize(written);
                REQUIRE(output == "X");
            }
        }

        WHEN("the input is 50") {
            THEN("the function output is \"L\"") {
                size_t written = to_roman(&output[0], output.size(), 50);
                output.resize(written);
                REQUIRE(output == "L");
            }
        }

        WHEN("the input is 100") {
            THEN("the function output is \"C\"") {
                size_t written = to_roman(&output[0], output.size(), 100);
                output.resize(written);
                REQUIRE(output == "C");
            }
        }

        WHEN("the input is 500") {
            THEN("the function output is \"D\"") {
                size_t written = to_roman(&output[0], output.size(), 500);
                output.resize(written);
                REQUIRE(output == "D");
            }
        }

        WHEN("the input is 1000") {
            THEN("the function output is \"M\"") {
                size_t written = to_roman(&output[0], output.size(), 1000);
                output.resize(written);
                REQUIRE(output == "M");
            }
        }
    }
}
