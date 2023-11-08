#include "Hero.h"

Hero::Hero(const std::string &spriteName, sf::Vector2f position)
: DrawableEntity(spriteName, position)
{
}

float Hero::getSpeed() const
{
    return speed;
}

std::vector<Direction> Hero::getDirections() const
{
    return directions;
}

void Hero::moveUp()
{
    directions.push_back(Direction::UP);
}

void Hero::moveDown()
{
    directions.push_back(Direction::DOWN);
}

void Hero::moveRight()
{
    directions.push_back(Direction::RIGHT);
}

void Hero::moveLeft()
{
    directions.push_back(Direction::LEFT);
}

void Hero::stopUp()
{
    directions.erase(std::remove(
            directions.begin(), directions.end(), Direction::UP), directions.end());
}

void Hero::stopDown()
{
    directions.erase(std::remove(
            directions.begin(), directions.end(), Direction::DOWN), directions.end());
}

void Hero::stopRight()
{
    directions.erase(std::remove(
            directions.begin(), directions.end(), Direction::RIGHT), directions.end());
}

void Hero::stopLeft()
{
    directions.erase(std::remove(
            directions.begin(), directions.end(), Direction::LEFT), directions.end());
}

void Hero::move()
{
    if (isDirectionInVector(directions, Direction::RIGHT))
    {
        setScale({ 1, 1 });
    }
    else if (isDirectionInVector(directions, Direction::LEFT))
    {
        setScale({ -1, 1 });
    }
}