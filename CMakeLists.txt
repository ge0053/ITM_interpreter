
cmake_minimum_required(VERSION 3.10)
project(stream_inotify C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
file(GLOB_RECURSE C_SRC CONFIGURE_DEPENDS
${CMAKE_SOURCE_DIR}/src/main.c
${CMAKE_SOURCE_DIR}/inc/expand_address.c
${CMAKE_SOURCE_DIR}/inc/print_msg.c

)

include_directories( 
${CMAKE_SOURCE_DIR}/inc/
)

# Add executable
add_executable(stream_inotify ${C_SRC})

# Extra warnings for safety
target_compile_options(stream_inotify PRIVATE -Wall -Wextra -g -pedantic)

# If you want to enable optimization in Release mode
set(CMAKE_BUILD_TYPE Release)
