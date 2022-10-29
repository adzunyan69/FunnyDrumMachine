cmake_minimum_required(VERSION 3.0)

project(SDL2Test)

set(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/SDL2/cmake")
set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/SDL2/include")

# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x64/SDL2main.lib")
else ()
  set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x86/SDL2main.lib")
endif ()

string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCES 
  src/main.cpp
  src/GameModule/mainwindow.h
  src/GameModule/mainwindow.cpp)

add_executable(SDL2Test src/main.cpp ${SOURCES})
target_link_libraries(SDL2Test ${SDL2_LIBRARIES})