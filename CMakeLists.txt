cmake_minimum_required(VERSION 3.2)
project(XRayMonteCarlo)

# --- omitted -Werror since ROOT is bad
set(MY_FLAGS "-g -O -Wall -Weffc++ -pedantic  \
    -pedantic-errors -Wextra -Waggregate-return -Wcast-align \
    -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion \
    -Wdisabled-optimization \
    -Wfloat-equal  -Wformat  -Wformat=2 \
    -Wformat-nonliteral -Wformat-security  \
    -Wformat-y2k \
    -Wimplicit  -Wimport  -Winit-self  -Winline \
    -Winvalid-pch   \
    -Wunavailable-declarations  -Wlong-long -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute   \
    -Wmissing-include-dirs -Wmissing-noreturn \
    -Wpacked  -Wpadded -Wparentheses  -Wpointer-arith \
    -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
    -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
    -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused \
    -Wunused-function  -Wunused-label  -Wunused-parameter \
    -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings -Wno-error=padded")


# --- find ROOT lib
if(EXISTS $ENV{ROOTSYS}/cmake/ROOTConfig.cmake)
    list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
    message("Found ROOTConfig.cmake :: ROOT in prefix path...")
else()
    list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
    message("Did not find ROOTConfig.cmake :: attempting to find ROOT in module path...")
endif()


find_package(ROOT REQUIRED COMPONENTS RIO Net)

# --- if found ROOT
if(ROOT)
    message(FATAL_ERROR "Could not find ROOT")
else()
    message("ROOT found!")
endif()

# --- include ROOT
include(${ROOT_USE_FILE})

# --- find source files
file(GLOB SOURCE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_FLAGS}")

# --- include dir lib include
include_directories(include)

# --- construct and add pseudo-random-number-generator lib
add_library(pRNG STATIC prng/PRNG.cpp)
# set_target_properties(pRNG PROPERTIES PUBLIC_HEADER include/xorshift.h)

add_executable(run ${SOURCE})

# --- link with customs
target_link_libraries(run pRNG)

# ---- link with ROOT
target_link_libraries(run ${ROOT_LIBRARIES})