#include <unordered_map>
#include <cmath>
#include "Bow.h"

Bow::Bow(const std::string& spriteName, sf::Vector2f position)
: Weapon(spriteName, position)
{
}

Bow::Bow(const Bow &other)
: Weapon(other)
{
}

void Bow::setDefaultPosition()
{
    setPosition({ (float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2 });
}

void Bow::move(float elapsedTime, std::shared_ptr<HeroInterface> hero, const std::vector<sf::Vector2f>& enemiesPositions)
{
    std::vector<sf::Vector2f> nearestEnemiesPositions = getNearestEnemiesPositions(hero->getPosition(), enemiesPositions);
    for (const sf::Vector2f& enemyPosition : nearestEnemiesPositions)
    {
        const sf::Vector2f deltaPosition = enemyPosition - getPosition();
        const auto deltaPositionLength = getVectorLength(deltaPosition);

        sf::Vector2f direction = { 0, 0 };
        if (deltaPositionLength != 0)
        {
            direction = {deltaPosition.x / deltaPositionLength, deltaPosition.y / deltaPositionLength};
        }
        const sf::Vector2f positionOffset = direction * speed * elapsedTime;

        setPosition(getPosition() + positionOffset);
    }
    moveByHeroDirection(elapsedTime, hero);
}

void Bow::moveByHeroDirection(float elapsedTime, const std::shared_ptr<HeroInterface>& hero)
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

float Bow::getVectorLength(sf::Vector2f vector)
{
    return (float)std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

std::vector<sf::Vector2f> Bow::getNearestEnemiesPositions(const sf::Vector2f& position, const std::vector<sf::Vector2f>& enemiesPositions) {
    std::unordered_map<float, sf::Vector2f> enemiesDistToPosMap;
    std::vector<float> enemiesDistances;
    for (const sf::Vector2f& enemyPosition : enemiesPositions)
    {
        const sf::Vector2f deltaPosition = position - enemyPosition;
        const auto deltaPositionLength = getVectorLength(deltaPosition);
        enemiesDistances.push_back(deltaPositionLength);
        enemiesDistToPosMap[deltaPositionLength] = enemyPosition;
    }
    std::sort(enemiesDistances.begin(), enemiesDistances.end());
    std::vector<sf::Vector2f> nearestEnemiesPositions;
    nearestEnemiesPositions.reserve((int)count);
    for (int i = 0; i < (int)count; i++)
    {
        nearestEnemiesPositions.push_back(enemiesDistToPosMap[enemiesDistances[i]]);
    }
    return nearestEnemiesPositions;
}
