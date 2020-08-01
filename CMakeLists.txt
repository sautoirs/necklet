cmake_minimum_required(VERSION 3.13)

project(Necklet)

add_library(Necklet
    src/fizzbuzz.c
    src/leap_years.c
    src/string_calculator.c
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
endif()

