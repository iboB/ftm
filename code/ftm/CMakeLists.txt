if(FTM_HEADER_ONLY_LIB)
    add_library(ftm INTERFACE)
elseif(FTM_STATIC_LIB)
    add_library(ftm STATIC ftm_impl.cpp)
    target_compile_definitions(ftm
        PRIVATE -DFTM_IMPLEMENT=1
    )
elseif(FTM_SHARED_LIB)
    add_library(ftm SHARED ftm_impl.cpp)

    if(UNIX)
        target_compile_options(ftm PRIVATE -fvisibility=hidden)
    endif()
    target_compile_definitions(ftm
        PUBLIC -DFTM_SHARED=1
        PRIVATE -DFTM_IMPLEMENT=1
    )
else()
    message(FATAL_ERROR "ftm: unsupported lib config")
endif()

target_include_directories(ftm INTERFACE ..)
