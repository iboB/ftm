add_library(ftm STATIC
    ftm_impl.cpp
 "test_time.hpp")

target_include_directories(ftm INTERFACE ..)
