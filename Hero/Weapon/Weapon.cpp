#include <iostream>
#include "Weapon.h"

Weapon::Weapon(const std::string& spriteName, sf::Vector2f position)
: DrawableEntity(spriteName, position)
{}

Weapon::Weapon(const Weapon &other)
: DrawableEntity(other)
{}

bool Weapon::isAttack() const
{
    if (time >= delay)
    {
        return true;
    }
    return false;
}

void Weapon::attack(float elapsedTime)
{
    time += elapsedTime;
    if (time >= delay + duration)
    {
        time -= delay + duration;
    }
}
