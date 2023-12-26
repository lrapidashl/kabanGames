#include <iostream>
#include "Weapon.h"

Weapon::Weapon(const std::string& spriteName, const std::string& ammoSpriteName, sf::Vector2f position, float damage, float duration, float delay, float speed, float count)
: DrawableEntity(spriteName, position), damage(damage), duration(duration), delay(delay), speed(speed), count(count)
{
    for (int i = 0; i < (int)count; i++)
    {
        ammo.emplace_back(ammoSpriteName, position);
    }
}

Weapon::Weapon(const Weapon &other)
: DrawableEntity(other), damage(other.damage), duration(other.duration), delay(other.delay), ammoDelay(other.ammoDelay), speed(other.speed), sizeScale(other.sizeScale), count(other.count), time(other.time), ammo(other.ammo)
{}

bool Weapon::isAttack() const
{
    if (time >= delay)
    {
        return true;
    }
    return false;
}

void Weapon::attack(float elapsedTime)
{
    time += elapsedTime;
    if (time >= delay + ammoDelay * (count - 1) + duration)
    {
        time -= delay + ammoDelay * (count - 1) + duration;
    }
    for (int i = 0; i < (int)count; i++)
    {
        ammo[i].update();
    }
}

void Weapon::enemiesCollision(const std::shared_ptr<EnemiesInterface>& enemies)
{
    std::vector<Enemy> newEnemies = enemies->getEnemies();
    for (auto & tile : ammo)
    {
        sf::Vector2f weaponPosition = tile.getPosition();
        sf::Vector2f weaponSize = tile.getSize();
        for (auto & enemy : newEnemies)
        {
            sf::Vector2f enemyPosition = enemy.getPosition();
            sf::Vector2f enemySize = enemy.getSize();
            bool topCollision = weaponPosition.y - weaponSize.y / 2 <= enemyPosition.y + enemySize.y / 2;
            bool rightCollision = weaponPosition.x + weaponSize.x / 2 >= enemyPosition.x - enemySize.x / 2;
            bool bottomCollision = weaponPosition.y + weaponSize.y / 2 >= enemyPosition.y - enemySize.y / 2;
            bool leftCollision = weaponPosition.x - weaponSize.x / 2 <= enemyPosition.x + enemySize.x / 2;
            if (topCollision && rightCollision && bottomCollision && leftCollision && !enemy.getIsHit()) {
                enemy.setHp(enemy.getHp() - damage);
                enemy.setIsHit(true);
                enemyCollision(tile);
            }
            if (enemy.getHp() <= 0) {
                enemy.setHp(enemy.getMaxHp());
                enemy.respawn(getRandomSide());
            }
        }
    }
    enemies->setEnemies(newEnemies);
}

void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    if (isAttack())
    {
        for (int i = 0; i < (int)count; i++)
        {
            if (time >= delay + ammoDelay * (float)i
                && time <= delay + ammoDelay * (float)i + duration)
            {
                target.draw(ammo[i], states);
            }
        }
    }
}
