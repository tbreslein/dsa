cmake_minimum_required(VERSION 3.20)

project(
    c_dsa
    VERSION 0.1
    LANGUAGES C
    )

set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE INTERNAL "Write compile_commands.json; needed for LSPs")
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES
        ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(main main.c linkedlist.h doublelinkedlist.h)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(main INTERFACE
        ${DEFAULT_COMPILE_OPTIONS}
        -fdiagnostics-color=always
        -Wall
        -Wextra
        )
elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(main INTERFACE
        ${DEFAULT_COMPILE_OPTIONS}
        -Wall
        -Wextra
        )
endif()

# soft link for compile_commands
file(CREATE_LINK ${CMAKE_BINARY_DIR}/compile_commands.json
     ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json SYMBOLIC)
