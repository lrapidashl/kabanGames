#ifndef KABAN_GAMES_HERO_H
#define KABAN_GAMES_HERO_H

#include <memory>
#include "Graphics.hpp"
#include "GameConsts.h"
#include "DrawableEntity.h"
#include "Weapon.h"

class Hero : public DrawableEntity
{
private:
    std::vector<std::shared_ptr<Weapon>>    weapons {};
    float                                   speed = 80;
    std::vector<Direction>                  directions {};

public:
    Hero(const std::string& spriteName, sf::Vector2f position, const std::vector<std::shared_ptr<Weapon>>& weapons);

    Hero(const std::string& spriteName, sf::Vector2f position, const std::shared_ptr<Weapon>& weapon);

    std::vector<std::shared_ptr<Weapon>> getWeapons() const;

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

    void attack(float elapsedTime);
};

#endif //KABAN_GAMES_HERO_H
