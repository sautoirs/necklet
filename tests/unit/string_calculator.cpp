#include <catch2/catch.hpp>

#include <string>

#include <string_calculator.c>

SCENARIO("Allow the add method to handle an unknow number of arguments", "[string_calculator]") {
    char output[] = "aaaaaaaaaaaaaaa";
    GIVEN("an input with multiple numbers separated by comma") {
        WHEN("the input is \"\"") {
            THEN("the function output is \"0\"") {
		std::string input = "";
		add(input.c_str(), input.size(), output, sizeof(output) * sizeof(output[0])); 
                REQUIRE(std::string(output) == "0");
	    }
	}

        WHEN("the input is \"1\"") {
            THEN("the function output is \"1\"") {
		std::string input = "1";
		add(input.c_str(), input.size(), output, sizeof(output) * sizeof(output[0])); 
                REQUIRE(std::string(output) == "1");
	    }
	}

        WHEN("the input is \"1.1,2.2\"") {
            THEN("the function output is \"3.3\"") {
		std::string input = "1.1,2.2";
		add(input.c_str(), input.size(), output, sizeof(output) * sizeof(output[0])); 
                REQUIRE(std::string(output) == "3.3");
	    }
	}
    }
}

SCENARIO("Allow the add method to handle newlines as separators", "[string_calculator]") {
    char output[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    GIVEN("an input with multiple numbers separated by comma") {
        WHEN("the input is \"1\\n2,3\"") {
            THEN("the function output is \"6\"") {
		std::string input = "1\n2,3";
		add(input.c_str(), input.size(), output, sizeof(output) * sizeof(output[0])); 
                REQUIRE(std::string(output) == "6");
	    }
	}

        WHEN("the input is \"175.2,\\n35\"") {
            THEN("the function output is \"Number expected but '\\n' found at position 6.\"") {
		std::string input = "175.2,\n35";
		add(input.c_str(), input.size(), output, sizeof(output) * sizeof(output[0])); 
                REQUIRE(std::string(output) == "Number expected but '\n' found at position 6.");
	    }
	}
    }
}

