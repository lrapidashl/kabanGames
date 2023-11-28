#ifndef KABAN_GAMES_WEAPON_H
#define KABAN_GAMES_WEAPON_H

#include "DrawableEntity.h"
#include "Direction.h"

class Weapon: public DrawableEntity
{
private:
    float damage = 60;
    float size{};
    float duration = 2;
    float delay = 5;
    float speed = 0;
    float count = 1;
    float time = 0;

public:
    Weapon(const std::string& spriteName, sf::Vector2f position);

    explicit Weapon(const std::string& spriteName): Weapon(spriteName, {100, 100}){};

    Weapon(const Weapon &other);

    bool isAttack() const;

    void attack(float elapsedTime);

    virtual void move(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& scale) = 0;
};

#endif //KABAN_GAMES_WEAPON_H
