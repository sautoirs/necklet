#include <catch2/catch.hpp>

#include <string>

#include <bowling.c>

SCENARIO("Return the sum of the frames if in none of them the player knocked all the pins down", "[bowling]") {
    GIVEN("A bowling line with no spare nor strike") {
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
    GIVEN("A bowling line with a spare") {
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
    GIVEN("A bowling line with a strike") {
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

SCENARIO("If he gets a spare or strike in the last frame, the bowler gets to throw one or two more bonus balls. These bonus throws are taken as part of the same turn. If the bonus throws knock down all the pins, the process does not repeat: the bonus throws are only used to calculate the score of the final frame", "[bowling]") {
    GIVEN("A bowling line with a strike or a spare in the last frame") {
        WHEN("the input is \"-- -- -- -- -- -- -- -- X X X X\"") {
            THEN("the function output is 60") {
		std::string input = "-- -- -- -- -- -- -- -- X X X X";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 60);
	    }
	}
	
        WHEN("the input is \"-- -- -- -- -- -- -- -- -/ 1/ X\"") {
            THEN("the function output is 31") {
		std::string input = "-- -- -- -- -- -- -- -- -/ 1/ X";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 31);
	    }
	}

        WHEN("the input is \"-- -- -- -- -- -- -- -- X X X 2\"") {
            THEN("the function output is 52") {
		std::string input = "-- -- -- -- -- -- -- -- X X X 2";
		uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 52);
	    }
	}

        WHEN("the input is \"X X X X X X X X X X X X\"") {
            THEN("the function output is 52") {
                std::string input = "X X X X X X X X X X X X";
                uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 300);
            }
        }

        WHEN("the input is \"9- 9- 9- 9- 9- 9- 9- 9- 9- 9-\"") {
            THEN("the function output is 52") {
                std::string input = "9- 9- 9- 9- 9- 9- 9- 9- 9- 9-";
                uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 90);
            }
        }

        WHEN("the input is \"5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/5\"") {
            THEN("the function output is 52") {
                std::string input = "5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/ 5/5";
                uint32_t score = count_score(input.c_str(), input.size());
                REQUIRE(score == 150);
            }
        }
    }
}

