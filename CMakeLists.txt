cmake_minimum_required(VERSION 3.10)

project(ftm)


if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(dev_mode ON)
else()
    set(dev_mode OFF)
endif()

if(dev_mode)
    include(./dev.cmake)
endif()

option(FTM_BUILD_TESTS "ftm: build tests" ${dev_mode})
option(FTM_BUILD_EXAMPLES "ftm: build examples" ${dev_mode})
option(FTM_BUILD_SCRATCH "ftm: build scratch project for testing and experiments" ${dev_mode})

mark_as_advanced(FTM_BUILD_TESTS FTM_BUILD_EXAMPLES FTM_BUILD_SCRATCH)

option(FTM_HEADER_ONLY_LIB "ftm: treat as a header-only library" OFF)
option(FTM_STATIC_LIB "ftm: build a static library" OFF)
option(FTM_SHARED_LIB "ftm: build a shared library" ON)

add_subdirectory(code/ftm)

if(FTM_BUILD_SCRATCH)
    add_subdirectory(scratch)
endif()

if(FTM_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()

if(FTM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
