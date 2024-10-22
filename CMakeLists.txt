cmake_minimum_required(VERSION 3.5)
project(connect4 CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add coverage flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Ensure debug information is included
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set(CMAKE_BUILD_TYPE Debug)

# Enable testing
enable_testing()

# Adding dependencies
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

# Adding plog
FetchContent_Declare(
    plog
    GIT_REPOSITORY "https://github.com/SergiusTheBest/plog.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

# Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make dependencies available
FetchContent_MakeAvailable(raylib plog googletest)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/src/*.h"
)
# Remove main.cpp from sources
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Get all test files
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_LIST_DIR}/tests/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/tests/*.h"
)

set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

# Main executable
add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_INCLUDE}
    ${plog_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    raylib
)

# Test executable
add_executable(${PROJECT_NAME}_test)
target_sources(${PROJECT_NAME}_test
    PRIVATE
    ${PROJECT_SOURCES}
    ${TEST_SOURCES}
)
target_include_directories(${PROJECT_NAME}_test
    PRIVATE
    ${PROJECT_INCLUDE}
    ${plog_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}_test
    PRIVATE
    raylib
    gtest_main
    gtest
)

# Register tests
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)
