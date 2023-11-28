#include "Sword.h"

Sword::Sword(const std::string& spriteName, sf::Vector2f position)
: Weapon(spriteName, position)
{
}

Sword::Sword(const Sword &other)
: Weapon(other)
{
}

void Sword::setDefaultPosition()
{

}

void Sword::move(float elapsedTime, std::shared_ptr<HeroInterface> hero, const std::vector<sf::Vector2f>& enemiesPositions)
{
    setOrigin({ 0, 0 });
    if (hero->getScale().x < 0)
    {
        setPosition({ hero->getPosition().x - hero->getSize().x / 2, hero->getPosition().y - getSize().y / 2 });
        setScale({ -1, 1 });
    }
    else if (hero->getSize().x > 0)
    {
        setPosition({ hero->getPosition().x + hero->getSize().x / 2, hero->getPosition().y - getSize().y / 2 });
        setScale({ 1, 1 });
    }
}