project(pet_game)
cmake_minimum_required(VERSION 3.18.1)

set(HEADERS
    include/gameEnviroment.h
)

set(SOURCES
    src/gameEnviroment.cpp
    src/Source.cpp
)

add_executable(demo ${SOURCES} ${HEADERS})
target_include_directories(demo PUBLIC include)