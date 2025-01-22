cmake_minimum_required(VERSION 3.15)

project(doomsound)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(SDL_STATIC ON)
FetchContent_Declare(
    sdl
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG SDL2
)
FetchContent_MakeAvailable(sdl)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
    sdlmixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG SDL2
)
FetchContent_MakeAvailable(sdlmixer)

add_library(doomsound
    ${CMAKE_CURRENT_SOURCE_DIR}/src/codec.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/doomsound.cpp
)

target_include_directories(doomsound PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(doomsound PUBLIC SDL2-static SDL2_mixer)

add_executable(wadsnd
    ${CMAKE_CURRENT_SOURCE_DIR}/wadsnd/main.cpp
)