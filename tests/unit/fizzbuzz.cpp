#include <catch2/catch.hpp>

#include <fizzbuzz.c>

SCENARIO("getting fizz, buzz or fizzbuz", "[fizzbuzz]") {
    GIVEN("any positive number") {
	char buffer[32];
        WHEN("the number is 1") {
            THEN("the function output is 1") {
		fizzbuzz(1, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "1");
	    }
	}

        WHEN("the number is 2") {
            THEN("the function output is 2") {
		fizzbuzz(2, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "2");
	    }
	}

        WHEN("the number is 3") {
            THEN("the function output is Fizz") {
		fizzbuzz(3, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "Fizz");
	    }
	}

        WHEN("the number is 4") {
            THEN("the function output is 4") {
		fizzbuzz(4, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "4");
	    }
	}

        WHEN("the number is 5") {
            THEN("the function output is Buzz") {
		fizzbuzz(5, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "Buzz");
	    }
	}

        WHEN("the number is 15") {
            THEN("the function output is FizzBuzz") {
		fizzbuzz(15, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "FizzBuzz");
	    }
	}
    }

    GIVEN("a number with 3 in it") {
	char buffer[32];
	WHEN("the number is 3") {
	    THEN("the function output is Fizz") {
		fizzbuzz(3, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "Fizz");
	    }
	}

	WHEN("the number is 13") {
	    THEN("the function output is Fizz") {
		fizzbuzz(13, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "Fizz");
	    }
	}
    }

    GIVEN("a number with 5 in it") {
	char buffer[32];
	WHEN("the number is 5") {
	    THEN("the function output is Buzz") {
		fizzbuzz(5, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "Buzz");
	    }
	}

	WHEN("the number is 25") {
	    THEN("the function output is Buzz") {
		fizzbuzz(25, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "Buzz");
	    }
	}
    }

    GIVEN("a number with both 3 and 5 in it") {
	char buffer[32];
	WHEN("the number is 35") {
	    THEN("the function output is FizzBuzz") {
		fizzbuzz(35, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "FizzBuzz");
	    }
	}

	WHEN("the number is 5531") {
	    THEN("the function output is FizzBuzz") {
		fizzbuzz(5531, buffer, sizeof(buffer) * sizeof(buffer[0]));
                REQUIRE(std::string(buffer) == "FizzBuzz");
	    }
	}
    }
}

