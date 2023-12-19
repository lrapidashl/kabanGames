#ifndef KABAN_GAMES_HERO_H
#define KABAN_GAMES_HERO_H

#include <memory>
#include "Graphics.hpp"
#include "GameConsts.h"
#include "HeroInterface.h"
#include "EnemiesInterface.h"
#include "Weapon.h"

class Hero : public HeroInterface
{
private:
    std::vector<std::shared_ptr<Weapon>> weapons {};
    float                                speed = 100;
    std::vector<Direction>               directions {};

    void setWeaponIconsPositions();

public:
    Hero(const std::string& spriteName, sf::Vector2f position, const std::vector<std::shared_ptr<Weapon>>& weapons);

    Hero(const std::string& spriteName, sf::Vector2f position, const std::shared_ptr<Weapon>& weapon);

    explicit Hero(Hero *other);

    std::vector<std::shared_ptr<Weapon>> getWeapons() const;

    float getSpeed() const override;

    std::vector<Direction> getDirections() const override;

    void moveUp();

    void moveDown();

    void moveRight();

    void moveLeft();

    void stopUp();

    void stopDown();

    void stopRight();

    void stopLeft();

    void move();

    void attack(float elapsedTime, const std::shared_ptr<EnemiesInterface>& enemies);
};

#endif //KABAN_GAMES_HERO_H
