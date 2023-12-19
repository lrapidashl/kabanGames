#ifndef KABAN_GAMES_ENEMY_H
#define KABAN_GAMES_ENEMY_H

#include <memory>
#include "Graphics.hpp"
#include "HeroInterface.h"
#include "DrawableEntity.h"

class Enemy : public DrawableEntity
{
private:
    float speed = 50;

    static float getVectorLength(sf::Vector2f vector);

    void moveByHeroDirection(float elapsedTime, const std::shared_ptr<HeroInterface>& hero);

    void moveToHero(float elapsedTime, const std::shared_ptr<HeroInterface>& hero);
public:
    Enemy(const std::string& spriteName, sf::Vector2f position);

    explicit Enemy(const std::string& spriteName): Enemy(spriteName, { -100, -100 }) {};

    Enemy(const Enemy& other);

    float getSpeed() const;

    void move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero);
};

#endif //KABAN_GAMES_ENEMY_H
