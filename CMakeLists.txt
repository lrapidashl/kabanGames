cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(kaban-games)

include_directories(headers included/SFML)
include_directories(headers Common)
include_directories(headers Enemy)
include_directories(headers Hero)
include_directories(headers Hero/Weapon)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

add_executable(kabanGames main.cpp
        Hero/Hero.cpp
        Hero/Hero.h
        Enemy/Enemy.cpp
        Enemy/Enemy.h
        Common/Direction.h
        Hero/Weapon/Weapon.cpp
        Hero/Weapon/Weapon.h
        Common/Direction.cpp
        Enemy/Enemies.cpp
        Enemy/Enemies.h
        Common/Random.h
        Common/Random.cpp
        Common/GameConsts.h
        Common/Side.h
        Common/Side.cpp
        Common/DrawableEntity.cpp
        Common/DrawableEntity.h
        Hero/Weapon/Sword.cpp
        Hero/Weapon/Sword.h
        Hero/Weapon/Bow.cpp
        Hero/Weapon/Bow.h
        Hero/HeroInterface.cpp
        Hero/HeroInterface.h
        Environments/Background.cpp
        Environments/Background.h
        Enemy/EnemiesInterface.cpp
        Enemy/EnemiesInterface.h)

target_include_directories(kabanGames PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(kabanGames PUBLIC cxx_std_17)
target_compile_definitions(kabanGames PRIVATE SFML_STATIC)

target_link_libraries(kabanGames ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})