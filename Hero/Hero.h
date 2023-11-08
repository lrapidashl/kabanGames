#ifndef KABAN_GAMES_HERO_H
#define KABAN_GAMES_HERO_H
#include "Graphics.hpp"
#include "../Common/GameConsts.h"
#include "../Common/Direction.h"
#include "../Common/DrawableEntity.h"

class Hero : public DrawableEntity
{
private:
    float                  speed = 80;
    std::vector<Direction> directions {};

public:
    Hero(const std::string& spriteName, sf::Vector2f position);

    explicit Hero(const std::string& spriteName): Hero(spriteName, { WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f}) {};

    float getSpeed() const;

    std::vector<Direction> getDirections() const;

    void moveUp();

    void moveDown();

    void moveRight();

    void moveLeft();

    void stopUp();

    void stopDown();

    void stopRight();

    void stopLeft();

    void move();
};

#endif //KABAN_GAMES_HERO_H
