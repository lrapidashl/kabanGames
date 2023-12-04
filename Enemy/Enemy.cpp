#include "Graphics.hpp"
#include <cmath>
#include <iostream>
#include "Enemy.h"

Enemy::Enemy(const std::string &spriteName, sf::Vector2f position)
: DrawableEntity(spriteName, position)
{
}

Enemy::Enemy(const Enemy& other)
: DrawableEntity(other)
{
}

float Enemy::getSpeed() const {
    return speed;
}

void Enemy::move(float elapsedTime, const Hero &hero)
{
    moveToHero(elapsedTime, hero);
    moveByHeroDirection(elapsedTime, hero);
}

float Enemy::getVectorLength(sf::Vector2f vector)
{
    return (float)std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

void Enemy::moveToHero(float elapsedTime, const Hero& hero)
{
    sf::Vector2f position = getPosition();
    const sf::Vector2f deltaPosition = hero.getPosition() - position;
    const auto deltaPositionLength = getVectorLength(deltaPosition);

    if (position.x > hero.getPosition().x)
    {
        setScale({ -1, 1 });
    }
    else if (position.x < hero.getPosition().x)
    {
        setScale({ 1, 1 });
    }

    sf::Vector2f direction = { 0, 0 };
    if (deltaPositionLength != 0)
    {
        direction = {deltaPosition.x / deltaPositionLength, deltaPosition.y / deltaPositionLength};
    }
    const sf::Vector2f positionOffset = direction * speed * elapsedTime;

    position += positionOffset;
    setPosition(position);
}

void Enemy::moveByHeroDirection(float elapsedTime, const Hero &hero)
{
    sf::Vector2f position = getPosition();
    if (isDirectionInVector(hero.getDirections(), Direction::UP))
    {
        position += elapsedTime * sf::Vector2f(0, hero.getSpeed());
    }
    if (isDirectionInVector(hero.getDirections(), Direction::DOWN))
    {
        position -= elapsedTime * sf::Vector2f(0, hero.getSpeed());
    }
    if (isDirectionInVector(hero.getDirections(), Direction::RIGHT))
    {
        position -= elapsedTime * sf::Vector2f(hero.getSpeed(), 0);
    }
    if (isDirectionInVector(hero.getDirections(), Direction::LEFT))
    {
        position += elapsedTime * sf::Vector2f(hero.getSpeed(), 0);
    }
    setPosition(position);
}
