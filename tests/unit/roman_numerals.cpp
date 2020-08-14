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

    GIVEN("A roman number which has a basic roman representation") {
        WHEN("the input is \"I\"") {
            THEN("the function output is 1") {
                std::string input = "I";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 1);
            }
        }

        WHEN("the input is \"V\"") {
            THEN("the function output is 5") {
                std::string input = "V";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 5);
            }
        }

        WHEN("the input is \"X\"") {
            THEN("the function output is 10") {
                std::string input = "X";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 10);
            }
        }

        WHEN("the input is \"L\"") {
            THEN("the function output is 50") {
                std::string input = "L";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 50);
            }
        }

        WHEN("the input is \"C\"") {
            THEN("the function output is 100") {
                std::string input = "C";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 100);
            }
        }

        WHEN("the input is \"D\"") {
            THEN("the function output is 500") {
                std::string input = "D";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 500);
            }
        }

        WHEN("the input is \"M\"") {
            THEN("the function output is 1000") {
                std::string input = "M";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 1000);
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

        WHEN("the input is 448") {
            THEN("the function output is \"CDXLVIII\"") {
                size_t written = to_roman(&output[0], output.size(), 448);
                output.resize(written);
                REQUIRE(output == "CDXLVIII");
            }
        }
    }

    GIVEN("A roman number which is slightly bigger than a basic") {
        WHEN("the input is \"II\"") {
            THEN("the function output is 2") {
                std::string input = "II";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 2);
            }
        }

        WHEN("the input is \"III\"") {
            THEN("the function output is 3") {
                std::string input = "III";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 3);
            }
        }

        WHEN("the input is \"VI\"") {
            THEN("the function output is 6") {
                std::string input = "VI";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 6);
            }
        }

        WHEN("the input is \"VII\"") {
            THEN("the function output is 7") {
                std::string input = "VII";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 7);
            }
        }

        WHEN("the input is \"VIII\"") {
            THEN("the function output is 8") {
                std::string input = "VIII";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 8);
            }
        }

        WHEN("the input is \"XVIII\"") {
            THEN("the function output is 18") {
                std::string input = "XVIII";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 18);
            }
        }

        WHEN("the input is \"CDXLVIII\"") {
            THEN("the function output is 448") {
                std::string input = "CDXLVIII";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 448);
            }
        }
    }
}

SCENARIO("A numbers slightly smaller than a basic number is completed with a smaller basic number prepended to the first one", "[roman_numerals]") {
    GIVEN("An arabic number which is slightly smaller than a basic number") {
        std::string output = std::string(128, 'a');
        WHEN("the input is 4") {
            THEN("the function output is \"IV\"") {
                size_t written = to_roman(&output[0], output.size(), 4);
                output.resize(written);
                REQUIRE(output == "IV");
            }
        }

        WHEN("the input is 9") {
            THEN("the function output is \"IX\"") {
                size_t written = to_roman(&output[0], output.size(), 9);
                output.resize(written);
                REQUIRE(output == "IX");
            }
        }

        WHEN("the input is 19") {
            THEN("the function output is \"XIX\"") {
                size_t written = to_roman(&output[0], output.size(), 19);
                output.resize(written);
                REQUIRE(output == "XIX");
            }
        }

        WHEN("the input is 24") {
            THEN("the function output is \"XXIV\"") {
                size_t written = to_roman(&output[0], output.size(), 24);
                output.resize(written);
                REQUIRE(output == "XXIV");
            }
        }

        WHEN("the input is 1998") {
            THEN("the function output is \"MCMXCVIII\"") {
                size_t written = to_roman(&output[0], output.size(), 1998);
                output.resize(written);
                REQUIRE(output == "MCMXCVIII");
            }
        }
    }

    GIVEN("A roman number which is slightly smaller than a basic") {
        WHEN("the input is \"IV\"") {
            THEN("the function output is 4") {
                std::string input = "IV";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 4);
            }
        }

        WHEN("the input is \"IX\"") {
            THEN("the function output is 9") {
                std::string input = "IX";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 9);
            }
        }

        WHEN("the input is \"MCMXCVIII\"") {
            THEN("the function output is 1998") {
                std::string input = "MCMXCVIII";
                uint32_t arabic = to_arabic(input.c_str(), input.size());
                REQUIRE(arabic == 1998);
            }
        }
    }
}

