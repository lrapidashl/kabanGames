#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(const std::string& spriteName, sf::Vector2f position)
: position(position)
{
    texture.loadFromFile(spriteName);
    sprite.setTexture(texture);

    size = { (float)texture.getSize().x, (float)texture.getSize().y };
    scale = { 1, 1 };
    origin = { size.x / 2, size.y / 2 };
}

DrawableEntity::DrawableEntity(const DrawableEntity& other)
: position(other.position), texture(other.texture), sprite(other.sprite), size(other.size), scale(other.scale), origin(other.origin)
{
    sprite.setTexture(texture);
}

void DrawableEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

sf::Vector2f DrawableEntity::getPosition() const
{
    return position;
}

void DrawableEntity::setPosition(sf::Vector2f position)
{
    this->position = position;
}

sf::Vector2f DrawableEntity::getSize() const
{
    return size;
}

sf::Vector2f DrawableEntity::getScale() const
{
    return scale;
}

void DrawableEntity::setScale(sf::Vector2f scale)
{
    this->scale = scale;
}

sf::Vector2f DrawableEntity::getOrigin() const
{
    return origin;
}

void DrawableEntity::setOrigin(sf::Vector2f origin)
{
    this->origin = origin;
}

void DrawableEntity::update()
{
    sprite.setPosition(position);
    sprite.setScale(scale);
    sprite.setOrigin(origin);
}