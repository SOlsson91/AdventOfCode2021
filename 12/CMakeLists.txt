cmake_minimum_required(VERSION 3.2)
project(aoc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic  -Wnull-dereference -Wdouble-promotion -Wformat=2 ")

include_directories("./src/" "../util/")

file(GLOB_RECURSE SOURCE 
	"./src/*.cpp"
	"./src/*.h"
	"../util/*.cpp"
	"../util/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(
	${PROJECT_NAME}
)
