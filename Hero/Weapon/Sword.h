#ifndef KABAN_GAMES_SWORD_H
#define KABAN_GAMES_SWORD_H

#include "Weapon.h"

class Sword : public Weapon
{
public:
    Sword(const std::string& spriteName, sf::Vector2f position);

    explicit Sword(const std::string& spriteName): Sword(spriteName, { 100, 100 }) {};

    Sword(const Sword& sword);

    void setDefaultPosition() override;

    void move(float elapsedTime, std::shared_ptr<HeroInterface> hero, const std::vector<sf::Vector2f>& enemiesPositions) override;
};

#endif //KABAN_GAMES_SWORD_H
