cmake_minimum_required(VERSION 3.16)

project(Runner LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/catch2.git
  GIT_TAG        v2.13.0
)
FetchContent_MakeAvailable(catch2)

add_executable(Runner
    fizzbuzz.cpp
    leap_years.cpp
    string_calculator.cpp
    word_wrap.cpp
    bowling.cpp
    roman_numerals.cpp
    markov_chain.cpp
    poker_hands.cpp
    main.cpp
)
target_include_directories(Runner
    PRIVATE
        ../../src
)

target_link_libraries(Runner
    PRIVATE
        Necklet::Necklet
        Catch2::Catch2
)

