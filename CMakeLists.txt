cmake_minimum_required(VERSION 3.26)
set(PROJECT_NAME cgl)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/state.h
        src/game.h
        src/game.cpp
        src/size_utils.h
        src/size_utils.cpp
)

add_subdirectory(external/sime)
target_link_libraries(${PROJECT_NAME} PUBLIC SIME)
