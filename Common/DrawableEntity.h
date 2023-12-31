#ifndef KABAN_GAMES_DRAWABLEENTITY_H
#define KABAN_GAMES_DRAWABLEENTITY_H
#include "Graphics.hpp"

class DrawableEntity: public sf::Drawable {
private:
    sf::Texture  texture;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f scale;
    sf::Vector2f origin;
    float        rotation = 0;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    sf::Sprite   sprite;

public:
    DrawableEntity(const std::string& spriteName, sf::Vector2f position);

    DrawableEntity(const DrawableEntity& other);

    sf::Vector2f getPosition() const;

    void setPosition(sf::Vector2f position);

    float getRotation() const;

    void setRotation(float rotation);

    sf::Vector2f getSize() const;

    void setSize(sf::Vector2f size);

    sf::Vector2f getScale() const;

    void setScale(sf::Vector2f scale);

    sf::Vector2f getOrigin() const;

    void setOrigin(sf::Vector2f origin);

    void update();
};

#endif //KABAN_GAMES_DRAWABLEENTITY_H
