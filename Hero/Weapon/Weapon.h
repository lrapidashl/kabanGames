#ifndef KABAN_GAMES_WEAPON_H
#define KABAN_GAMES_WEAPON_H

#include <memory>
#include "DrawableEntity.h"
#include "HeroInterface.h"

class Weapon: public DrawableEntity
{
protected:
    float damage = 60;
    float size{};
    float duration = 2;
    float delay = 5;
    float speed = 200;
    float count = 1;
    float time = 0;

public:
    Weapon(const std::string& spriteName, sf::Vector2f position);

    explicit Weapon(const std::string& spriteName): Weapon(spriteName, {100, 100}){};

    Weapon(const Weapon &other);

    bool isAttack() const;

    void attack(float elapsedTime);

    virtual void setDefaultPosition() = 0;

    virtual void move(float elapsedTime, std::shared_ptr<HeroInterface> hero, const std::vector<sf::Vector2f>& enemiesPositions) = 0;
};

#endif //KABAN_GAMES_WEAPON_H
