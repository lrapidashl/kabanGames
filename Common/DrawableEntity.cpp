#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(const std::string& spriteName, sf::Vector2f position)
: position(position)
{
    texture.loadFromFile(spriteName);
    sprite.setTexture(texture);

    size = { (float)texture.getSize().x, (float)texture.getSize().y };
    scale = { 1, 1 };
    sprite.setOrigin(size.x / 2, size.y / 2);
}

DrawableEntity::DrawableEntity(const DrawableEntity& other)
: position(other.position), texture(other.texture), sprite(other.sprite), size(other.size), scale(other.scale)
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

void DrawableEntity::setScale(sf::Vector2f scale)
{
    this->scale = scale;
}

void DrawableEntity::update()
{
    sprite.setPosition(position);
    sprite.setScale(scale);
}