#include "Graphics.hpp"
#include <cmath>
#include <iostream>
#include "Enemy.h"
#include "GameConsts.h"
#include "Random.h"

Enemy::Enemy(const std::string &spriteName, sf::Vector2f position)
: DrawableEntity(spriteName, position)
{
}

Enemy::Enemy(const Enemy& other)
: DrawableEntity(other), hp(other.hp), maxHp(other.maxHp), speed(other.speed), isHit(other.isHit), damage(other.damage)
{
}

float Enemy::getSpeed() const
{
    return speed;
}

float Enemy::getMaxHp() const
{
    return maxHp;
}

float Enemy::getHp() const
{
    return hp;
}

void Enemy::setHp(float hp)
{
    this->hp = hp;
}

bool Enemy::getIsHit() const
{
    return isHit;
}

void Enemy::setIsHit(bool isHit)
{
    this->isHit = isHit;
}

void Enemy::respawn(Side side)
{
    int sideNumber = (int)(getSideNumber(side) % SIDES_COUNT);
    if (sideNumber == getSideNumber(Side::RIGHT))
    {
        setPosition({
                Random::random((float)(-RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY), (float)(-RENDER_DISTANCE)),
                Random::random((float)(-RENDER_DISTANCE), (float)(WINDOW_HEIGHT + RENDER_DISTANCE)) });
    }
    if (sideNumber == getSideNumber(Side::TOP))
    {
        setPosition({
                Random::random((float)(-RENDER_DISTANCE), (float)(WINDOW_WIDTH + RENDER_DISTANCE)),
                Random::random((float)(-RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY), (float)(-RENDER_DISTANCE)) });
    }
    if (sideNumber == getSideNumber(Side::LEFT))
    {
        setPosition({
                Random::random((float)(WINDOW_WIDTH + RENDER_DISTANCE), (float)(WINDOW_WIDTH + RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY)),
                Random::random((float)(-RENDER_DISTANCE), (float)(WINDOW_HEIGHT + RENDER_DISTANCE)) });
    }
    if (sideNumber == getSideNumber(Side::BOTTOM))
    {
        setPosition({
                Random::random((float)(-RENDER_DISTANCE), (float)(WINDOW_WIDTH + RENDER_DISTANCE)),
                Random::random((float)(WINDOW_HEIGHT + RENDER_DISTANCE), (float)(WINDOW_HEIGHT + RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY)) });
    }
}

void Enemy::move(float elapsedTime, const std::shared_ptr<HeroInterface> &hero)
{
    moveToHero(elapsedTime, hero);
    moveByHeroDirection(elapsedTime, hero);
}

float Enemy::getVectorLength(sf::Vector2f vector)
{
    return (float)std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

void Enemy::moveToHero(float elapsedTime, const std::shared_ptr<HeroInterface>& hero)
{
    sf::Vector2f position = getPosition();
    const sf::Vector2f deltaPosition = hero->getPosition() - position;
    const auto deltaPositionLength = getVectorLength(deltaPosition);

    if (position.x > hero->getPosition().x)
    {
        setScale({ -1, 1 });
    }
    else if (position.x < hero->getPosition().x)
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

void Enemy::moveByHeroDirection(float elapsedTime, const std::shared_ptr<HeroInterface> &hero)
{
    sf::Vector2f position = getPosition();
    if (isDirectionInVector(hero->getDirections(), Direction::UP))
    {
        position += elapsedTime * sf::Vector2f(0, hero->getSpeed());
    }
    if (isDirectionInVector(hero->getDirections(), Direction::DOWN))
    {
        position -= elapsedTime * sf::Vector2f(0, hero->getSpeed());
    }
    if (isDirectionInVector(hero->getDirections(), Direction::RIGHT))
    {
        position -= elapsedTime * sf::Vector2f(hero->getSpeed(), 0);
    }
    if (isDirectionInVector(hero->getDirections(), Direction::LEFT))
    {
        position += elapsedTime * sf::Vector2f(hero->getSpeed(), 0);
    }
    setPosition(position);
}
