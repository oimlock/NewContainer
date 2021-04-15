project(NewContainer)
cmake_minimum_required(VERSION 3.18.1)

set(HEADERS
    include/IContainer.h
    include/ListContainer.h
	include/VectorContainer.h
	include/VectorList.h	
)

set(SOURCES
    src/ListContainer.cpp
    src/Source.cpp
    src/VectorContainer.cpp
	src/VectorList.cpp
)

add_executable(demo ${SOURCES} ${HEADERS})
target_include_directories(demo PUBLIC include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
