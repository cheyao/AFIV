cmake_minimum_required(VERSION 3.5)
project(Viewer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are:
        Debug Release"
      FORCE)
endif()


if(CMAKE_BUILD_TYPE STREQUAL Debug)
    message("Debug enabled")
    add_definitions(-D_DEBUG)
else()
    add_definitions(-DNDEBUG)
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
# find_package(SDL2_image REQUIRED)
# include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# tinyfiledialogs
include_directories(extern/tinyfiledialogs)

# src
include_directories(include)
add_executable(Viewer
src/main.cpp
src/ui/window.cpp
src/ui/app.cpp
src/util/log.cpp
src/formats/image.cpp
src/formats/bmp.cpp
extern/tinyfiledialogs/tinyfiledialogs.cpp
)

target_link_libraries(Viewer ${SDL2_LIBRARIES})

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE
        NAMES "clang-tidy"
        DOC "Path to clang-tidy executable")
    if(NOT CLANG_TIDY_EXE)
        message(STATUS "clang-tidy not found.")
    else()
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif()

    if(CLANG_TIDY_EXE)
        set_target_properties(aseprite PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
    endif()
endif()

# do appify for app
