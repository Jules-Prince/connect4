cmake_minimum_required(VERSION 3.5)
project(connect4 CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied example games

# Disable OpenGL deprecation warnings on macOS
if(APPLE)
    add_compile_definitions(GL_SILENCE_DEPRECATION)
endif()

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

# Make dependencies available
FetchContent_MakeAvailable(raylib plog)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

# Declaring our executable
add_executable(${PROJECT_NAME})
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

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} 
    PUBLIC 
        ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
) 
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets")