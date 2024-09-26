cmake_minimum_required(VERSION 3.10)
project(cute_cat)

set(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Specify the path to SFML using CMAKE_PREFIX_PATH
set(CMAKE_PREFIX_PATH "D:/vcpkg/installed/x64-windows")

find_package(SFML COMPONENTS graphics window system REQUIRED)

# Add include directories
include_directories(include)

# Add source files
file(GLOB SOURCES "source/*.cpp")

# Add executable target
add_executable(cute_cat ${SOURCES})

# Link SFML to the executable target
target_link_libraries(cute_cat PRIVATE sfml-graphics sfml-window sfml-system)

# Copy resources to build directory
file(COPY resource DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/resource/font DESTINATION ${CMAKE_BINARY_DIR}/resource)