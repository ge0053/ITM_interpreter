
cmake_minimum_required(VERSION 3.10)
project(ITM_interpret C)






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

add_executable(ITM_interpret ${C_SRC})

target_compile_options(ITM_interpret PRIVATE -Wall -Wextra -g -pedantic)

install(TARGETS ITM_interpret RUNTIME DESTINATION bin)

set(CMAKE_BUILD_TYPE Release)
