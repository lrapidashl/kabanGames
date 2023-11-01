#ifndef KABAN_GAMES_ENEMY_H
#define KABAN_GAMES_ENEMY_H
#include <Graphics.hpp>
#include "Hero.h"

class Enemy : public sf::Drawable
{
private:
    sf::Texture  texture;
    sf::Sprite   sprite;
    sf::Vector2f position;
    sf::Vector2f size = { 55, 30 };
    float speed = 50;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    static float getVectorLength(sf::Vector2f vector);

public:
    Enemy(const std::string& spriteName, sf::Vector2f position);

    explicit Enemy(const std::string& spriteName): Enemy(spriteName, { -100, -100 }) {};

    Enemy(const Enemy& other);

    sf::Vector2f getPosition() const;

    void setPosition(sf::Vector2f position);

    sf::Vector2f getSize() const;

    void moveToHero(float elapsedTime, const Hero& hero);

    float getSpeed() const;

    void update();
};

#endif //KABAN_GAMES_ENEMY_H
