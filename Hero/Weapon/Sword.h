#ifndef KABAN_GAMES_SWORD_H
#define KABAN_GAMES_SWORD_H

#include "Weapon.h"

class Sword : public Weapon
{
private:
    void enemyCollision(DrawableEntity& bullet) override;
public:
    Sword(const std::string& spriteName, const std::string& ammoSpriteName, sf::Vector2f position);

    explicit Sword(const std::string& spriteName, const std::string& ammoSpriteName): Sword(spriteName, ammoSpriteName, { 100, 100 }) {};

    Sword(const Sword& sword);

    void setDefaultPosition(const std::shared_ptr<EnemiesInterface>& enemies) override;

    void move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero) override;
};

#endif //KABAN_GAMES_SWORD_H
