cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(kaban-games)

include_directories(headers included/SFML)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

add_executable(kabanGames main.cpp
        Hero.cpp
        Hero.h
        Enemy.cpp
        Enemy.h
        Direction.h)

target_include_directories(kabanGames PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(kabanGames PUBLIC cxx_std_17)
target_compile_definitions(kabanGames PRIVATE SFML_STATIC)

target_link_libraries(kabanGames ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})