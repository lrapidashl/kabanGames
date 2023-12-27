#ifndef KABAN_GAMES_GAMECONSTS_H
#define KABAN_GAMES_GAMECONSTS_H

#include <string>
#include "Graphics.hpp"

constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned WINDOW_WIDTH = 1600;
constexpr unsigned WINDOW_HEIGHT = 900;
const sf::Vector2f WINDOW_CENTER = { (float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2 };
constexpr unsigned MAX_FPS = 60;
const int RENDER_DISTANCE = 100;
const int RENDER_SPREAD_MULTIPLY = 5;
const std::string KNIGHT_PATH = "../images/heroes/knight.png";
const std::string BOAR_PATH = "../images/enemies/boar.png";
const std::string SWORD_PATH = "../images/weapons/sword.png";
const std::string SWORD_AMMO_PATH = "../images/weapons/sword_ammo.png";
const std::string BOW_PATH = "../images/weapons/bow.png";
const std::string BOW_AMMO_PATH = "../images/weapons/bow_ammo.png";
const std::string BACKGROUND_PATH = "../images/environments/background.png";
const std::string EXPERIENCE_PATH = "../images/environments/experience.png";

#endif //KABAN_GAMES_GAMECONSTS_H
