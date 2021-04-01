set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(icm_warning_flags "-D_CRT_SECURE_NO_WARNINGS /wd4251 /wd4275 /w34100 /Zc:__cplusplus")
else()
    set(icm_warning_flags "-Wall -Wextra")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
