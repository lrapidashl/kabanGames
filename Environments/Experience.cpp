#include "Experience.h"
#include "cmath"
#include <utility>
#include <iostream>

Experience::Experience(std::string spriteName)
: spriteName(std::move(spriteName))
{
}

Experience::Experience(const Experience &other)
: spriteName(other.spriteName), speed(other.speed)
{
    gems.clear();
    for (const auto & gem : other.gems)
    {
        gems.emplace_back(other.spriteName, gem.getPosition());
    }
}

std::vector<DrawableEntity> Experience::getGems() const
{
    return gems;
}

void Experience::setGems(const std::vector<DrawableEntity>& gems)
{
    this->gems.clear();
    for (const auto &gem : gems)
    {
        this->gems.emplace_back(gem);
    }
}

void Experience::spawn(const sf::Vector2f& position)
{
    DrawableEntity newGem(spriteName, position);
    gems.push_back(newGem);
}

void Experience::move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero)
{
    for (DrawableEntity& gem : gems)
    {
        moveToHero(elapsedTime, gem, hero);
        moveByHeroDirection(elapsedTime, gem, hero);
        gem.update();
    }
}

void Experience::moveByHeroDirection(float elapsedTime, DrawableEntity& gem, const std::shared_ptr<HeroInterface>& hero)
{
    sf::Vector2f position = gem.getPosition();
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
    gem.setPosition(position);
}

void Experience::moveToHero(float elapsedTime, DrawableEntity &gem, const std::shared_ptr<HeroInterface> &hero) const
{
    sf::Vector2f position = gem.getPosition();
    const sf::Vector2f deltaPosition = hero->getPosition() - position;
    const auto deltaPositionLength = getVectorLength(deltaPosition);

    sf::Vector2f direction = { 0, 0 };
    if (deltaPositionLength != 0)
    {
        direction = {deltaPosition.x / deltaPositionLength, deltaPosition.y / deltaPositionLength};
    }
    if (deltaPositionLength <= hero->getExpRadius())
    {
        const sf::Vector2f positionOffset = direction * speed * elapsedTime;
        position += positionOffset;
        gem.setPosition(position);
    }
}

float Experience::getVectorLength(sf::Vector2f vector)
{
    return (float)std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

void Experience::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const DrawableEntity& gem : gems)
    {
        target.draw(gem, states);
    }
}
