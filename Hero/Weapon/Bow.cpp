#include <unordered_map>
#include <cmath>
#include <iostream>
#include "Bow.h"
#include "GameConsts.h"

Bow::Bow(const std::string& spriteName, const std::string& ammoSpriteName, sf::Vector2f position)
: Weapon(spriteName, ammoSpriteName, position, 20, 5, 1, 200, 1)
{
}

Bow::Bow(const Bow &other)
: Weapon(other)
{
}

void Bow::setDefaultPosition(const std::shared_ptr<EnemiesInterface>& enemies)
{
    for (int i = 0; i < (int)count; i++)
    {
        ammo[i].setPosition(WINDOW_CENTER);
    }
    getNearestEnemiesPositions(WINDOW_CENTER, enemies);
}

void Bow::move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero)
{
    for (int i = 0; i < (int)count; i++)
    {
        if (time >= delay + ammoDelay * (float)i
        && time <= delay + ammoDelay * (float)i + duration)
        {
            const sf::Vector2f deltaPosition = nearestEnemies[i]->getPosition() - hero->getPosition();
            const auto deltaPositionLength = getVectorLength(deltaPosition);

            sf::Vector2f direction = {0, 0};
            if (deltaPositionLength != 0)
            {
                direction = {deltaPosition.x / deltaPositionLength, deltaPosition.y / deltaPositionLength};
            }
            const sf::Vector2f positionOffset = direction * speed * elapsedTime;

            ammo[i].setPosition(ammo[i].getPosition() + positionOffset);
            rotate(ammo[i], direction);
            moveByHeroDirection(elapsedTime, ammo[i], hero);
        }
    }
}

void Bow::moveByHeroDirection(float elapsedTime, DrawableEntity& entity, const std::shared_ptr<HeroInterface>& hero)
{
    sf::Vector2f position = entity.getPosition();
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
    entity.setPosition(position);
}

float Bow::getVectorLength(sf::Vector2f vector)
{
    return (float)std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

float Bow::toDegrees(double radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void Bow::rotate(DrawableEntity& entity, sf::Vector2f direction)
{
    const double angle = atan2(double(direction.y), double(direction.x));
    float newRotation = toDegrees(angle);
    entity.setRotation(newRotation);
}

void Bow::getNearestEnemiesPositions(const sf::Vector2f& position, const std::shared_ptr<EnemiesInterface>& enemies)
{
    std::unordered_map<float, std::shared_ptr<Enemy>> enemiesDistToPosMap;
    std::vector<float> enemiesDistances;
    for (const Enemy& enemy : enemies->getEnemies())
    {
        const sf::Vector2f deltaPosition = position - enemy.getPosition();
        const auto deltaPositionLength = getVectorLength(deltaPosition);
        enemiesDistances.push_back(deltaPositionLength);
        enemiesDistToPosMap[deltaPositionLength] = std::make_shared<Enemy>(enemy);
    }
    std::sort(enemiesDistances.begin(), enemiesDistances.end());
    nearestEnemies.clear();
    int nearestCount = (int)MAX_AMMO_COUNT >= (int)enemies->getEnemies().size() ? (int)MAX_AMMO_COUNT : (int)enemies->getEnemies().size();
    nearestEnemies.reserve(nearestCount);
    for (int i = 0; i < nearestCount; i++)
    {
        nearestEnemies.push_back(enemiesDistToPosMap[enemiesDistances[i]]);
    }
}

void Bow::enemyCollision(DrawableEntity& bullet)
{
    bullet.setPosition({-1000000, -1000000});
}
