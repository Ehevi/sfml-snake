cmake_minimum_required(VERSION 3.20)
project(snake)

set(SRCS
    src/game.cpp
    src/main.cpp
    src/snakesection.cpp
    src/input.cpp
    src/draw.cpp
    src/update.cpp
    src/food.cpp
    src/menu.cpp
    src/utils.cpp
    src/wall.cpp
    src/snake.cpp
)

add_executable("${PROJECT_NAME}" ${SRCS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic -Wextra -Werror -O0")

include_directories(headers /usr/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries("${PROJECT_NAME}" ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

file(COPY font DESTINATION ${CMAKE_BINARY_DIR})