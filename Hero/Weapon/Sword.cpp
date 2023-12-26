#include "Sword.h"
#include "cmath"

Sword::Sword(const std::string& spriteName, const std::string& ammoSpriteName, sf::Vector2f position)
: Weapon(spriteName, ammoSpriteName, position, 60, 0.2, 3, 0, 1)
{
}

Sword::Sword(const Sword &other)
: Weapon(other)
{
}

void Sword::setDefaultPosition(const std::shared_ptr<EnemiesInterface>& enemies)
{

}

void Sword::move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero)
{
    for (int i = 0; i < (int)count; i++)
    {
        if (hero->getScale().x < 0)
        {
            ammo[i].setPosition({hero->getPosition().x - (float)std::pow(-1, i) * (hero->getSize().x / 2 + getSize().x / 2),  -((float)i * getSize().y / 4) + hero->getPosition().y});
            ammo[i].setScale({-(float)std::pow(-1, i), 1});
        }
        else if (hero->getSize().x > 0)
        {
            ammo[i].setPosition({hero->getPosition().x + (float)std::pow(-1, i) * (hero->getSize().x / 2 + getSize().x / 2), -((float)i * getSize().y / 4) + hero->getPosition().y});
            ammo[i].setScale({(float)std::pow(-1, i), 1});
        }
    }
}

void Sword::enemyCollision(DrawableEntity& bullet)
{

}