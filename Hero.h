#ifndef KABAN_GAMES_HERO_H
#define KABAN_GAMES_HERO_H
#include <Graphics.hpp>
#include "Direction.h"

class Hero : public sf::Drawable
{
private:

    sf::Texture            texture;
    sf::Sprite             sprite;
    sf::Vector2f           position = { -100, -100 };
    sf::Vector2f           size = { 40, 60 };
    float                  speed = 80;
    std::vector<Direction> directions {};

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    explicit Hero(const std::string& spriteName);

    sf::Vector2f getPosition() const;

    void setPosition(sf::Vector2f position);

    float getSpeed() const;

    std::vector<Direction> getDirections() const;

    void moveUp();

    void moveDown();

    void moveRight();

    void moveLeft();

    void stopUp();

    void stopDown();

    void stopRight();

    void stopLeft();

    void update(float elapsedTime);
};


#endif //KABAN_GAMES_HERO_H
