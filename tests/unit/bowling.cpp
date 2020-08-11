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

SCENARIO("If in two tries he knocks them all down, his score for the frame is ten plus the number of pins knocked down on his next throw", "[bowling]") {
    GIVEN("A bownling line with a spare") {
        WHEN("the input is \"5/ 11\"") {
            THEN("the function output is 13") {
		std::string input = "5/ 11";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 13);
	    }
	}

        WHEN("the input is \"-/ 11\"") {
            THEN("the function output is 13") {
		std::string input = "-/ 11";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 13);
	    }
	}

        WHEN("the input is \"-/ --\"") {
            THEN("the function output is 11") {
		std::string input = "-/ -1";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 11);
	    }
	}
    }
}

SCENARIO("If on his first try in the frame he knocks down all the pins, his turn is over and his score for the frame is ten plus the simple total of the pins knocked down in his next two rolls", "[bowling]") {
    GIVEN("A bownling line with a strike") {
        WHEN("the input is \"X 11 11\"") {
            THEN("the function output is 16") {
		std::string input = "X 11 11";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 16);
	    }
	}
	
        WHEN("the input is \"X -- 11\"") {
            THEN("the function output is 12") {
		std::string input = "X -- 11";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 12);
	    }
	}
    }
}

