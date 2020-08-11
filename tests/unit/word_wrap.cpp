#include <catch2/catch.hpp>

#include <string>

#include <word_wrap.c>

SCENARIO("Split the paragraph into lines of less or equal than `col` characters", "[word_wrap]") {
    std::string output = std::string(128, 'a');
    GIVEN("A paragraph written on a single line and a number of column matching spaces") {
        WHEN("the input is (\"aa bb cc dd\", 3)") {
            THEN("the function output is \"aa \\nbb \\ncc \\ndd \"") {
		std::string input = "aa bb cc dd";
		size_t written = word_wrap(input.c_str(), input.size(), &output[0], output.size(), 3); 
		output.resize(written);
                REQUIRE(output == "aa \nbb \ncc \ndd");
	    }
	}

        WHEN("the input is (\"\", 1)") {
            THEN("the function output is \"\"") {
		std::string input = "";
		size_t written = word_wrap(input.c_str(), input.size(), &output[0], output.size(), 1); 
		output.resize(written);
                REQUIRE(output == "");
	    }
	}
	
        WHEN("the input is (\"aa\", 3)") {
            THEN("the function output is \"aa\"") {
		std::string input = "aa";
		size_t written = word_wrap(input.c_str(), input.size(), &output[0], output.size(), 3); 
		output.resize(written);
                REQUIRE(output == "aa");
	    }
	}
    }
}

