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

    hpBar.setFillColor(sf::Color::Red);
    expBar.setFillColor(sf::Color::Blue);

    hpBar.setSize({getSize().x, HP_BAR_HEIGHT});
    expBar.setSize({0, EXP_BAR_HEIGHT});

    hpBar.setPosition({getPosition().x - getSize().x / 2, getPosition().y + getSize().y / 2});
    expBar.setPosition({0, 0});

    setWeaponIconsPositions();
}

Hero::Hero(Hero *other)
: HeroInterface(*other), speed(other->speed), directions(other->directions), weapons(other->weapons), hp(other->hp),
maxHp(other->maxHp), exp(other->exp), maxExp(other->maxExp), hpBar(other->hpBar), expBar(other->expBar)
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

float Hero::getExpRadius() const
{
    return expRadius;
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

void Hero::attack(float elapsedTime, const std::shared_ptr<EnemiesInterface>& enemies, Experience& experience)
{
    for (std::shared_ptr<Weapon>& weapon : weapons)
    {
        weapon->attack(elapsedTime);
        if (weapon->isAttack())
        {
            weapon->move(elapsedTime, std::make_shared<Hero>(this));
            weapon->enemiesCollision(enemies, experience);
        }
        else
        {
            weapon->setDefaultPosition(enemies);
            std::vector<Enemy> newEnemies = enemies->getEnemies();
            enemies->setEnemies(newEnemies);
        }
        weapon->update();
    }
}

void Hero::enemiesCollision(const std::shared_ptr<EnemiesInterface>& enemies)
{
    std::vector<Enemy> newEnemies = enemies->getEnemies();
    sf::Vector2f heroPosition = getPosition();
    sf::Vector2f heroSize = getSize();
    for (auto & enemy : newEnemies)
    {
        sf::Vector2f enemyPosition = enemy.getPosition();
        sf::Vector2f enemySize = enemy.getSize();
        bool topCollision = heroPosition.y - heroSize.y / 2 <= enemyPosition.y + enemySize.y / 2;
        bool rightCollision = heroPosition.x + heroSize.x / 2 >= enemyPosition.x - enemySize.x / 2;
        bool bottomCollision = heroPosition.y + heroSize.y / 2 >= enemyPosition.y - enemySize.y / 2;
        bool leftCollision = heroPosition.x - heroSize.x / 2 <= enemyPosition.x + enemySize.x / 2;
        if (topCollision && rightCollision && bottomCollision && leftCollision)
        {
            hp -= enemy.getDamage();
            hpBar.setSize({getSize().x / maxHp * hp, HP_BAR_HEIGHT});
        }
    }
}

void Hero::experienceCollision(Experience &experience)
{
    std::vector<DrawableEntity> newExperience = experience.getGems();
    sf::Vector2f heroPosition = getPosition();
    sf::Vector2f heroSize = getSize();
    for (int i = 0; i < newExperience.size(); i++)
    {
        sf::Vector2f enemyPosition = newExperience[i].getPosition();
        sf::Vector2f enemySize = newExperience[i].getSize();
        bool topCollision = heroPosition.y - heroSize.y / 2 <= enemyPosition.y + enemySize.y / 2;
        bool rightCollision = heroPosition.x + heroSize.x / 2 >= enemyPosition.x - enemySize.x / 2;
        bool bottomCollision = heroPosition.y + heroSize.y / 2 >= enemyPosition.y - enemySize.y / 2;
        bool leftCollision = heroPosition.x - heroSize.x / 2 <= enemyPosition.x + enemySize.x / 2;
        if (topCollision && rightCollision && bottomCollision && leftCollision)
        {
            newExperience.erase(newExperience.begin() + i);
            exp++;
            expBar.setSize({WINDOW_WIDTH / maxExp * exp, EXP_BAR_HEIGHT});
            if (exp >= maxExp)
            {
                exp = 0;
                maxExp *= 1.1;
                expBar.setSize({WINDOW_WIDTH / maxExp * exp, EXP_BAR_HEIGHT});
            }
            break;
        }
    }
    experience.setGems(newExperience);
}

bool Hero::isDeath() const
{
    return hp <= 0;
}

void Hero::setWeaponIconsPositions()
{
    for (int i = 0; i < weapons.size(); i++)
    {
        weapons[i]->setOrigin({0, 0});
        weapons[i]->setPosition({ 50 * (float)i, 10 });
    }
}

void Hero::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    target.draw(hpBar, states);
    target.draw(expBar, states);
}