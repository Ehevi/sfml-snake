cmake_minimum_required(VERSION 3.20)
project(snake)

set(CMAKE_CXX_STANDARD 20)

add_executable(snake src/main.cpp src/game.cpp headers/game.hpp src/snakesection.cpp headers/snakesection.hpp)

include_directories(headers /usr/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(snake ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

