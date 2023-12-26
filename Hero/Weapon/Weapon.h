#ifndef KABAN_GAMES_WEAPON_H
#define KABAN_GAMES_WEAPON_H

#include <memory>
#include "DrawableEntity.h"
#include "HeroInterface.h"
#include "EnemiesInterface.h"

class Weapon : public DrawableEntity
{
protected:
    std::vector<DrawableEntity> ammo;
    float                       damage;
    float                       sizeScale = 1;
    float                       duration;
    float                       delay;
    float                       ammoDelay = 0.1;
    float                       speed;
    float                       count = 1;
    float                       time = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    virtual void enemyCollision(DrawableEntity& bullet) = 0;

public:
    Weapon(const std::string& spriteName, const std::string& ammoSpriteName, sf::Vector2f position, float damage, float duration, float delay, float speed, float count);

    Weapon(const Weapon &other);

    bool isAttack() const;

    void attack(float elapsedTime);

    void enemiesCollision(const std::shared_ptr<EnemiesInterface>& enemies);

    virtual void setDefaultPosition(const std::shared_ptr<EnemiesInterface>& enemies) = 0;

    virtual void move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero) = 0;
};

#endif //KABAN_GAMES_WEAPON_H
