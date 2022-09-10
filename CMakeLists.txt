cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # For clang-tidy.
set(BUILD_SHARED_LIBS OFF)              # We expect external libraries to be linked statically.
set(CMAKE_CXX_STANDARD 17)              # Compile as C++17.
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Require C++14 support.

project(LeetCodeJounery
        LANGUAGES C CXX
        )

# People keep running CMake in the wrong folder, completely nuking their project or creating weird bugs.
# This checks if you're running CMake from a folder that already has CMakeLists.txt.
# Importantly, this catches the common case of running it from the root directory.
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" PATH_TO_CMAKELISTS_TXT)
if (EXISTS "${PATH_TO_CMAKELISTS_TXT}")
    message(FATAL_ERROR "Run CMake from a build subdirectory! \"mkdir build ; cd build ; cmake ..\" \
    Some junk files were created in this folder (CMakeCache.txt, CMakeFiles); you should delete those.")
endif ()

# Expected directory structure.
set(LEETCODEJONERY_BUILD_SUPPORT_DIR "${CMAKE_SOURCE_DIR}/build_support")
set(LEETCODEJONERY_CLANG_SEARCH_PATH "/usr/local/bin" "/usr/bin" "/usr/local/opt/llvm/bin" "/usr/local/opt/llvm@11/bin"
        "/usr/local/Cellar/llvm/11.0.1/bin" "/opt/homebrew/opt/llvm@11/bin/")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL "^11.")
        message(STATUS "You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
    else ()
        message(WARNING "!! We recommend that you use clang-12 for developing LeetCodeJounery. You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}, a different version.")
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    message(STATUS "You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
else ()
    message(WARNING "!! We recommend that you use clang-12 for developing LeetCodeJounery. You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}, which is not clang.")
endif ()

######################################################################################################################
# DEPENDENCIES
######################################################################################################################

# clang-format

# attempt to find the binary if user did not specify
find_program(CLANG_FORMAT_BIN
        NAMES clang-format clang-format-11
        HINTS ${LEETCODEJONERY_CLANG_SEARCH_PATH})

if ("${CLANG_FORMAT_BIN}" STREQUAL "CLANG_FORMAT_BIN-NOTFOUND")
    message(WARNING "LeetCodeJounery/main couldn't find clang-format.")
else ()
    message(STATUS "LeetCodeJounery/main found clang-format at ${CLANG_FORMAT_BIN}")
endif ()

# attempt to find the binary if user did not specify
find_program(CLANG_TIDY_BIN
        NAMES clang-tidy clang-tidy-11
        HINTS ${LEETCODEJONERY_CLANG_SEARCH_PATH})

find_program(CLANG_APPLY_REPLACEMENTS_BIN
        NAMES clang-apply-replacements clang-apply-replacements-11
        HINTS ${LEETCODEJONERY_CLANG_SEARCH_PATH})

if ("${CLANG_APPLY_REPLACEMENTS_BIN}" STREQUAL "CLANG_APPLY_REPLACEMENTS_BIN-NOTFOUND")
    message(WARNING "LeetCodeJounery/main couldn't find clang-apply-replacements.")
else ()
    # Output compile_commands.json
    set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
    message(STATUS "LeetCodeJounery/main found clang-apply-replacements at ${CLANG_APPLY_REPLACEMENTS_BIN}")
endif ()

######################################################################################################################
# COMPILER SETUP
######################################################################################################################

if (NOT LEETCODEJONERY_SANITIZER)
    set(LEETCODEJONERY_SANITIZER address)
endif ()

message("Build mode: ${CMAKE_BUILD_TYPE}")
message("${LEETCODEJONERY_SANITIZER} sanitizer enabled in debug mode.")

# Compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter -Wno-attributes") #TODO: remove
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -fsanitize=${LEETCODEJONERY_SANITIZER} -fno-omit-frame-pointer -fno-optimize-sibling-calls")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "CMAKE_SHARED_LINKER_FLAGS: ${CMAKE_SHARED_LINKER_FLAGS}")

# Output directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Includes.
set(LEETCODEJONERY_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

include_directories(${LEETCODEJONERY_SRC_INCLUDE_DIR})

function(disable_target_warnings NAME)
    target_compile_options(${NAME} PRIVATE "-w")
endfunction()

######################################################################################################################
# Other CMake modules
# MUST BE ADDED AFTER CONFIGURING COMPILER PARAMETERS
######################################################################################################################

######################################################################################################################
# MAKE TARGETS
######################################################################################################################
file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*/*.cpp)
foreach( sourcefile ${APP_SOURCES} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${sourcefile})

    string( REGEX REPLACE ".+/(.+)\\..*" "\\1" file ${filename} )
    
    add_executable( ${file} ${sourcefile} )
endforeach( sourcefile ${APP_SOURCES} )

##########################################
# "make format"
# "make check-format"
##########################################

string(CONCAT LEETCODEJONERY_FORMAT_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/src,"
        )

# Runs clang format and updates files in place.
add_custom_target(format ${LEETCODEJONERY_BUILD_SUPPORT_DIR}/run_clang_format.py
        ${CLANG_FORMAT_BIN}
        ${LEETCODEJONERY_BUILD_SUPPORT_DIR}/clang_format_exclusions.txt
        --source_dirs
        ${LEETCODEJONERY_FORMAT_DIRS}
        --fix
        --quiet
        )

# Runs clang format and exits with a non-zero exit code if any files need to be reformatted
add_custom_target(check-format ${LEETCODEJONERY_BUILD_SUPPORT_DIR}/run_clang_format.py
        ${CLANG_FORMAT_BIN}
        ${LEETCODEJONERY_BUILD_SUPPORT_DIR}/clang_format_exclusions.txt
        --source_dirs
        ${LEETCODEJONERY_FORMAT_DIRS}
        --quiet
        )
