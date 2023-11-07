#include <Graphics.hpp>
#include <cmath>
#include <iostream>
#include "Enemy.h"
#include "Hero.h"

Enemy::Enemy(const std::string& spriteName, sf::Vector2f position)
: position(position)
{
    texture.loadFromFile(spriteName);
    sprite.setTexture(texture);

    size = { (float)texture.getSize().x, (float)texture.getSize().y };
    sprite.setOrigin(size.x / 2, size.y / 2);
}

Enemy::Enemy(const Enemy& other)
: position(other.position), texture(other.texture), sprite(other.sprite), size(other.size), speed(other.speed)
{
    sprite.setTexture(texture);
}

sf::Vector2f Enemy::getPosition() const
{
    return position;
}

void Enemy::setPosition(sf::Vector2f position)
{
    this->position = position;
}

sf::Vector2f Enemy::getSize() const {
    return size;
}

float Enemy::getSpeed() const {
    return speed;
}

void Enemy::move(float elapsedTime, const Hero &hero)
{
    moveToHero(elapsedTime, hero);
    moveByHeroDirection(elapsedTime, hero);
}

void Enemy::update()
{
    sprite.setPosition(position);
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

bool Enemy::isDirectionInVector(std::vector<Direction> directions, Direction direction)
{
    return std::find(directions.begin(), directions.end(), direction) != directions.end();
}

float Enemy::getVectorLength(sf::Vector2f vector)
{
    return (float)std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

void Enemy::moveToHero(float elapsedTime, const Hero& hero)
{
    const sf::Vector2f deltaPosition = hero.getPosition() - position;
    const auto deltaPositionLength = getVectorLength(deltaPosition);

    if (position.x > hero.getPosition().x)
    {
        sprite.setScale(-1, 1);
    }
    else if (position.x < hero.getPosition().x)
    {
        sprite.setScale(1, 1);
    }

    sf::Vector2f direction = { 0, 0 };
    if (deltaPositionLength != 0)
    {
        direction = {deltaPosition.x / deltaPositionLength, deltaPosition.y / deltaPositionLength};
    }
    const sf::Vector2f positionOffset = direction * speed * elapsedTime;

    position += positionOffset;
}

void Enemy::moveByHeroDirection(float elapsedTime, const Hero &hero)
{
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
}
