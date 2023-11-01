#include "Hero.h"

Hero::Hero(const std::string& spriteName)
{
    texture.loadFromFile(spriteName);
    sprite.setTexture(texture);

    size = { (float)texture.getSize().x, (float)texture.getSize().y };
    sprite.setOrigin(size.x / 2, size.y / 2);
}

sf::Vector2f Hero::getPosition() const
{
    return position;
}

void Hero::setPosition(sf::Vector2f position)
{
    this->position = position;
}

void Hero::move()
{

}

void Hero::update(float elapsedTime)
{
    sprite.setPosition(position);
}

void Hero::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
