#ifndef KABAN_GAMES_BOW_H
#define KABAN_GAMES_BOW_H

#include "Weapon.h"
#include "Enemies.h"

class Bow : public Weapon
{
private:
    void moveByHeroDirection(float elapsedTime, const std::shared_ptr<HeroInterface>& hero);

    static float getVectorLength(sf::Vector2f vector);

    std::vector<sf::Vector2f> getNearestEnemiesPositions(const sf::Vector2f& position, const std::vector<sf::Vector2f>& enemiesPositions);
public:
    Bow(const std::string& spriteName, sf::Vector2f position);

    explicit Bow(const std::string& spriteName): Bow(spriteName, { 100, 100 }) {};

    Bow(const Bow& sword);

    void setDefaultPosition() override;

    void move(float elapsedTime,std::shared_ptr<HeroInterface> hero, const std::vector<sf::Vector2f>& enemiesPositions) override;
};

#endif //KABAN_GAMES_BOW_H
