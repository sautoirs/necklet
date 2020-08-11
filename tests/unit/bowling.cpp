#include <catch2/catch.hpp>

#include <string>

#include <bowling.c>

SCENARIO("Return the sum of the frames if in none of them the player knocked all the pins down", "[bowling]") {
    GIVEN("A bownling line with no spare nor strike") {
        WHEN("the input is \"\"") {
            THEN("the function output is 0") {
		std::string input = "";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 0);
	    }
	}

        WHEN("the input is \"12 34\"") {
            THEN("the function output is 10") {
		std::string input = "12 34";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 10);
	    }
	}
	
        WHEN("the input is \"1- -4\"") {
            THEN("the function output is 5") {
		std::string input = "1- -4";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 5);
	    }
	}
    }
}

