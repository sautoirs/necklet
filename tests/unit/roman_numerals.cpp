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

SCENARIO("A numbers slightly bigger than a basic number is completed with a smaller basic number appended to the first one", "[roman_numerals]") {
    GIVEN("An arabic number which is slightly bigger than a basic number") {
        std::string output = std::string(128, 'a');
        WHEN("the input is 2") {
            THEN("the function output is \"II\"") {
                size_t written = to_roman(&output[0], output.size(), 2);
                output.resize(written);
                REQUIRE(output == "II");
            }
        }

        WHEN("the input is 6") {
            THEN("the function output is \"VI\"") {
                size_t written = to_roman(&output[0], output.size(), 6);
                output.resize(written);
                REQUIRE(output == "VI");
            }
        }

        WHEN("the input is 7") {
            THEN("the function output is \"VII\"") {
                size_t written = to_roman(&output[0], output.size(), 7);
                output.resize(written);
                REQUIRE(output == "VII");
            }
        }

        WHEN("the input is 8") {
            THEN("the function output is \"VIII\"") {
                size_t written = to_roman(&output[0], output.size(), 8);
                output.resize(written);
                REQUIRE(output == "VIII");
            }
        }

        WHEN("the input is 16") {
            THEN("the function output is \"XVI\"") {
                size_t written = to_roman(&output[0], output.size(), 16);
                output.resize(written);
                REQUIRE(output == "XVI");
            }
        }

        WHEN("the input is 26") {
            THEN("the function output is \"XXVI\"") {
                size_t written = to_roman(&output[0], output.size(), 26);
                output.resize(written);
                REQUIRE(output == "XXVI");
            }
        }
    }
}
