#ifndef KABAN_GAMES_BOW_H
#define KABAN_GAMES_BOW_H

#include "Weapon.h"
#include "Enemies.h"

class Bow : public Weapon
{
private:
    const float MAX_AMMO_COUNT = 10;

    std::vector<std::shared_ptr<Enemy>> nearestEnemies;

    static void moveByHeroDirection(float elapsedTime, DrawableEntity& entity, const std::shared_ptr<HeroInterface>& hero);

    static float getVectorLength(sf::Vector2f vector);

    static float toDegrees(double radians);

    static void rotate(DrawableEntity& entity, sf::Vector2f direction) ;

    void getNearestEnemiesPositions(const sf::Vector2f& position, const std::shared_ptr<EnemiesInterface>& enemies);

public:
    Bow(const std::string& spriteName, const std::string& ammoSpriteName, sf::Vector2f position);

    explicit Bow(const std::string& spriteName, const std::string& ammoSpriteName): Bow(spriteName, ammoSpriteName, { 100, 100 }) {};

    Bow(const Bow& sword);

    void setDefaultPosition(const std::shared_ptr<EnemiesInterface>& enemies) override;

    void move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero) override;
};

#endif //KABAN_GAMES_BOW_H
