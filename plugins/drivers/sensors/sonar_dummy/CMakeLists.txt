cmake_minimum_required(VERSION 3.12)
project(ping-cpp LANGUAGES CXX)

# Use standard C++ version and remove extensions to allow better compatibility
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Include modules

set(PING_SRC_DIR  "$ENV{HOME}/Documents/Sonar/ping-cppcstred")
add_subdirectory(${PING_SRC_DIR} ${CMAKE_CURRENT_BINARY_DIR}/_deps/ping-cppstred-build)

add_executable(pingDummyDriver)
target_sources(
    pingDummyDriver
PRIVATE
main.cpp
)
target_link_libraries(
    pingDummyDriver
PRIVATE
    DEVICE
    HAL
    PING_MESSAGES
    BOOSTLESS
)
