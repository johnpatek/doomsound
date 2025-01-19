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

FetchContent_Declare(
    sndfile
    GIT_REPOSITORY https://github.com/libsndfile/libsndfile.git
    GIT_TAG master
)
FetchContent_MakeAvailable(sndfile)

add_subdirectory(example)