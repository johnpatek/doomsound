FetchContent_Declare(
    wadtek
    GIT_REPOSITORY https://github.com/maxtek6/wadtek.git
    GIT_TAG master
)
FetchContent_MakeAvailable(wadtek)

add_executable(soundctl main.cpp)
target_link_libraries(soundctl PRIVATE wadtek)