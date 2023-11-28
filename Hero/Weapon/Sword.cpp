#include <iostream>
#include "Sword.h"

Sword::Sword(const std::string& spriteName, sf::Vector2f position)
: Weapon(spriteName, position)
{
}

Sword::Sword(const Sword &other)
: Weapon(other)
{
}

void Sword::move(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& scale)
{
    setOrigin({ 0, 0 });
    if (scale.x < 0)
    {
        setPosition({ position.x - size.x / 2, position.y - getSize().y / 2 });
        setScale({ -1, 1 });
    }
    else if (scale.x > 0)
    {
        setPosition({ position.x + size.x / 2, position.y - getSize().y / 2 });
        setScale({ 1, 1 });
    }
}