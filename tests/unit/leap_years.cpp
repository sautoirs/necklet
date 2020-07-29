#include <catch2/catch.hpp>

#include <leap_years.c>

SCENARIO("All years divisible by 400 are leap years", "[leap_years]") {
    GIVEN("any positive year") {
        WHEN("the year is 0") {
            THEN("the function output is true") {
                REQUIRE(is_leap_years(0) == true);
	    }
	}

        WHEN("the year is 400") {
            THEN("the function output is true") {
                REQUIRE(is_leap_years(400) == true);
	    }
	}

        WHEN("the year is 800") {
            THEN("the function output is true") {
                REQUIRE(is_leap_years(800) == true);
	    }
	}

        WHEN("the year is 2000") {
            THEN("the function output is true") {
                REQUIRE(is_leap_years(2000) == true);
	    }
	}
    }
}

SCENARIO("All years divisble by 100 but not by 400 are not leap years", "[leap_years]") {
    GIVEN("any positive year") {
        WHEN("the year is 1700") {
            THEN("the function output is false") {
                REQUIRE(is_leap_years(1700) == false);
	    }
	}

        WHEN("the year is 1800") {
            THEN("the function output is false") {
                REQUIRE(is_leap_years(1800) == false);
	    }
	}

        WHEN("the year is 1900") {
            THEN("the function output is false") {
                REQUIRE(is_leap_years(1900) == false);
	    }
	}

        WHEN("the year is 2100") {
            THEN("the function output is false") {
                REQUIRE(is_leap_years(2100) == false);
	    }
	}
    }
}

SCENARIO("All years divisible by 4 but not by 100 are leap years", "[leap_years]") {
    GIVEN("any positive year") {
        WHEN("the year is 2008") {
            THEN("the function output is true") {
                REQUIRE(is_leap_years(2008) == true);
	    }
	}

        WHEN("the year is 2012") {
            THEN("the function output is true") {
                REQUIRE(is_leap_years(2012) == true);
	    }
	}

        WHEN("the year is 2016") {
            THEN("the function output is true") {
                REQUIRE(is_leap_years(2016) == true);
	    }
	}
    }
}

SCENARIO("All years not divisible by 4 are not leap years", "[leap_years]") {
    GIVEN("any positive year") {
        WHEN("the year is 2017") {
            THEN("the function output is false") {
                REQUIRE(is_leap_years(2017) == false);
	    }
	}

        WHEN("the year is 2018") {
            THEN("the function output is false") {
                REQUIRE(is_leap_years(2018) == false);
	    }
	}

        WHEN("the year is 2019") {
            THEN("the function output is false") {
                REQUIRE(is_leap_years(2019) == false);
	    }
	}
    }
}

