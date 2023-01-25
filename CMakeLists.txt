cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SDL2Test)


if (WIN32)
    set(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/SDL2/cmake")
    set(SDL2_ttf_DIR "${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/cmake")
    set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/SDL2/include;${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/include")
    set(SDL2_ttf_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/include")
    # Support both 32 and 64 bit builds
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
      set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x64/SDL2main.lib")
      set(SDL2_ttf_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/lib/x64/SDL2_ttf.lib")
    else ()
      set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/SDL2/lib/x86/SDL2main.lib")
      set(SDL2_ttf_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/SDL2_ttf/lib/x86/SDL2_ttf.lib")
    endif ()

    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
endif ()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_ttf_INCLUDE_DIRS})

set(SOURCES 
  src/main.cpp
  src/GameModule/mainwindow.h
  src/GameModule/mainwindow.cpp
  src/Stuff/textureloader.h
  src/Stuff/texture.h
  src/Stuff/texture.cpp
  src/Stuff/timer.h
  src/Stuff/timer.cpp
  src/Stuff/uniformrandom.h
  src/Stuff/uniformrandom.cpp
  src/GameModule/button.h
  src/GameModule/button.cpp
  src/GameModule/drum.h
  src/GameModule/drum.cpp
  src/GameModule/cell.h
  src/GameModule/cell.cpp
  src/GameModule/fpscounter.h
  src/GameModule/fpscounter.cpp)

add_executable(SDL2Test src/main.cpp ${SOURCES})
target_link_libraries(SDL2Test ${SDL2_LIBRARIES} ${SDL2_ttf_LIBRARIES})
