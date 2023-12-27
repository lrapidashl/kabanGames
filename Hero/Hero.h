#ifndef KABAN_GAMES_HERO_H
#define KABAN_GAMES_HERO_H

#include <memory>
#include "Graphics.hpp"
#include "GameConsts.h"
#include "HeroInterface.h"
#include "EnemiesInterface.h"
#include "Weapon.h"

class Hero : public HeroInterface
{
private:
    const float HP_BAR_HEIGHT = 5;
    const float EXP_BAR_HEIGHT = 10;

    std::vector<std::shared_ptr<Weapon>> weapons {};
    float                                speed = 100;
    std::vector<Direction>               directions {};
    float                                maxHp = 100;
    float                                hp = 100;
    float                                maxExp = 10;
    float                                exp = 0;
    sf::RectangleShape                   hpBar;
    sf::RectangleShape                   expBar;
    float                                expRadius = 50;

    void setWeaponIconsPositions();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    Hero(const std::string& spriteName, sf::Vector2f position, const std::vector<std::shared_ptr<Weapon>>& weapons);

    Hero(const std::string& spriteName, sf::Vector2f position, const std::shared_ptr<Weapon>& weapon):
    Hero(spriteName, position, std::vector<std::shared_ptr<Weapon>> {weapon}) {};

    explicit Hero(Hero *other);

    std::vector<std::shared_ptr<Weapon>> getWeapons() const;

    float getSpeed() const override;

    std::vector<Direction> getDirections() const override;

    float getExpRadius() const override;

    void moveUp();

    void moveDown();

    void moveRight();

    void moveLeft();

    void stopUp();

    void stopDown();

    void stopRight();

    void stopLeft();

    void move();

    void attack(float elapsedTime, const std::shared_ptr<EnemiesInterface>& enemies, Experience& experience);

    void enemiesCollision(const std::shared_ptr<EnemiesInterface>& enemies);

    void experienceCollision(Experience& experience);

    bool isDeath() const;
};

#endif //KABAN_GAMES_HERO_H
