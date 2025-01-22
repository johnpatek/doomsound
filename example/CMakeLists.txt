FetchContent_Declare(
    wadtek
    GIT_REPOSITORY https://github.com/maxtek6/wadtek.git
    GIT_TAG master
)
FetchContent_MakeAvailable(wadtek)

FetchContent_Declare(
    sigfn
    GIT_REPOSITORY https://github.com/maxtek6/sigfn.git
    GIT_TAG master
)
FetchContent_MakeAvailable(sigfn)

FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG master
)
FetchContent_MakeAvailable(argparse)

add_executable(soundctl main.cpp)
target_link_libraries(soundctl PRIVATE wadtek doomsound sigfn_a)