#include <iostream>
#include <unordered_map>
#include "Hero.h"

Hero::Hero(const std::string &spriteName, sf::Vector2f position, const std::vector<std::shared_ptr<Weapon>>& weapons)
: HeroInterface(spriteName, position)
{
    for (const std::shared_ptr<Weapon>& weapon : weapons)
    {
        this->weapons.push_back(weapon);
    }
    setWeaponIconsPositions();
}

Hero::Hero(const std::string &spriteName, sf::Vector2f position, const std::shared_ptr<Weapon>& weapon)
: HeroInterface(spriteName, position)
{
    weapons.push_back(weapon);
    setWeaponIconsPositions();
}

Hero::Hero(Hero *other)
: HeroInterface(*other), speed(other->speed), directions(other->directions), weapons(other->weapons)
{}

std::vector<std::shared_ptr<Weapon>> Hero::getWeapons() const
{
    return weapons;
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

void Hero::attack(float elapsedTime, const std::shared_ptr<EnemiesInterface>& enemies)
{
    for (std::shared_ptr<Weapon>& weapon : weapons)
    {
        weapon->attack(elapsedTime);
        if (weapon->isAttack())
        {
            weapon->move(elapsedTime, std::make_shared<Hero>(this));
        }
        else
        {
            weapon->setDefaultPosition(enemies);
        }
        weapon->update();
    }
}

void Hero::setWeaponIconsPositions()
{
    for (int i = 0; i < weapons.size(); i++)
    {
        weapons[i]->setPosition({ 40 * (float)i, 10 });
    }
}