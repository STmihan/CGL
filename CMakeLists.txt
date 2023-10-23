cmake_minimum_required(VERSION 3.26)
set(PROJECT_NAME cgl)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        main.cpp
)

add_subdirectory(external/sime)
target_link_libraries(${PROJECT_NAME} PUBLIC SIME)
