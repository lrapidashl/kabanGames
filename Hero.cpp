#include "Hero.h"

Hero::Hero(const std::string& spriteName)
{
    texture.loadFromFile(spriteName);
    sprite.setTexture(texture);

    size = { (float)texture.getSize().x, (float)texture.getSize().y };
    sprite.setOrigin(size.x / 2, size.y / 2);
}

sf::Vector2f Hero::getPosition() const
{
    return position;
}

void Hero::setPosition(sf::Vector2f position)
{
    this->position = position;
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

void Hero::update(float elapsedTime)
{
    sprite.setPosition(position);
}

void Hero::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
