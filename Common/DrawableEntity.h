#ifndef KABAN_GAMES_DRAWABLEENTITY_H
#define KABAN_GAMES_DRAWABLEENTITY_H
#include "Graphics.hpp"

class DrawableEntity: public sf::Drawable {
private:
    sf::Texture  texture;
    sf::Sprite   sprite;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f scale;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    DrawableEntity(const std::string& spriteName, sf::Vector2f position);

    DrawableEntity(const DrawableEntity& other);

    sf::Vector2f getPosition() const;

    void setPosition(sf::Vector2f position);

    sf::Vector2f getSize() const;

    void setScale(sf::Vector2f scale);

    void update();
};

#endif //KABAN_GAMES_DRAWABLEENTITY_H
