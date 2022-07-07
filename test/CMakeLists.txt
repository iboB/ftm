cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include(./get_cpm.cmake)

CPMAddPackage(gh:iboB/icm@1.3.3)
CPMAddPackage(gh:iboB/doctest-lib@2.4.8a)

include(${icm_SOURCE_DIR}/icm_testing.cmake)

macro(add_ftm_test test)
    icm_add_doctest_lib_test(${test} ftm ${ARGN})
endmacro()

add_ftm_test(test_time t-test_time.cpp)
add_ftm_test(year_month_day t-year_month_day.cpp)
