cmake_minimum_required(VERSION 3.13)

project(Necklet)

add_library(Necklet
    src/fizzbuzz.c
    src/leap_years.c
    src/string_calculator.c
    src/word_wrap.c
    src/bowling.c
    src/roman_numerals.c
    src/markov_chain.c
    src/poker_hands.c
)

target_include_directories(Necklet
    PUBLIC
        include
    PRIVATE
        src
)

add_library(Necklet::Necklet ALIAS Necklet)

if((CMAKE_PROJECT_NAME STREQUAL Necklet OR NECKLET_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests/unit)
    target_compile_options(Necklet 
        PUBLIC
            $<$<STREQUAL:${CMAKE_C_COMPILER_ID},GNU>:--coverage>
    )
    target_link_options(Necklet 
        PUBLIC
            $<$<STREQUAL:${CMAKE_C_COMPILER_ID},GNU>:--coverage>
    )
endif()

