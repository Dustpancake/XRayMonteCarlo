cmake_minimum_required(VERSION 2.8)
project(XRayMonteCarlo)


# --- find ROOT lib
if(EXISTS $ENV{ROOTSYS}/cmake/ROOTConfig.cmake)
    list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
    message("Found ROOTConfig.cmake :: ROOT in prefix path...")

elseif(EXISTS $ENV{ROOTSYS}/etc/cmake)
    list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
    message("Did not find ROOTConfig.cmake :: attempting to find ROOT in module path...")

elseif(EXISTS /usr/share/root/cmake)
    message("adding /usr/share/root/cmake to path...")
    list(APPEND CMAKE_MODULE_PATH /usr/share/root/cmake)
    set(IS_LINAPP 1)
endif()


find_package(ROOT REQUIRED COMPONENTS RIO Net)

# --- if found ROOT
if(ROOT)
    message(FATAL_ERROR "Could not find ROOT")
else()
    message("+ Found ROOT")
endif()

# --- include ROOT
if(${IS_LINAPP})
    include_directories(${ROOT_INCLUDE_DIRS})
    message("+ On linapp server")

    set(MY_FLAGS "-std=c++0x")
else()
    set(CMAKE_MACOSX_RPATH 1)
    include(${ROOT_USE_FILE})
    message("+ On personal computer")

    set(MY_FLAGS "-O2")

    set(CMAKE_CXX_STANDARD 11)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_FLAGS}")

# --- find source files
file(GLOB SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/pipeline/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/plottools/*.cpp"
    )

# --- include Boost libraries
find_package(Boost REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message("+ Found Boost")
else()
    message(FATAL_ERROR "Could not find Boost.")
endif ()

# --- include dir lib include
include_directories(include)

# --- construct and add custom lib with boost wrapper
file(GLOB SUPPORT_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/supportlib/*.cpp")
add_library(SupportLib SHARED ${SUPPORT_LIBS})


# --- set compiler flag for supportlib library to optimize for speed
if (NOT ${IS_LINAPP})
    set_target_properties(SupportLib PROPERTIES COMPILE_FLAGS "-O2")
endif()
# set_target_properties(SupportLib PROPERTIES PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/include/SupportLib.h")

# --- link ROOT with customs
target_link_libraries(SupportLib ${ROOT_LIBRARIES})

add_executable(run src/main.cpp ${SOURCE})
add_executable(test src/tests.cpp ${SOURCE})


# --- link with customs
target_link_libraries(run SupportLib)
target_link_libraries(test SupportLib)

# ---- link with ROOT
target_link_libraries(run ${ROOT_LIBRARIES})
target_link_libraries(test ${ROOT_LIBRARIES})