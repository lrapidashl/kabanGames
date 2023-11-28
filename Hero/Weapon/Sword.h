#ifndef KABAN_GAMES_SWORD_H
#define KABAN_GAMES_SWORD_H

#include "Weapon.h"
#include "Hero.h"

class Sword : public Weapon
{
public:
    Sword(const std::string& spriteName, sf::Vector2f position);

    explicit Sword(const std::string& spriteName): Sword(spriteName, { 100, 100 }) {};

    Sword(const Sword& sword);

    void move(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& scale) override;
};

#endif //KABAN_GAMES_SWORD_H
