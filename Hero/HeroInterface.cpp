#include "HeroInterface.h"

HeroInterface::HeroInterface(const std::string &spriteName, sf::Vector2f position)
: DrawableEntity(spriteName, position)
{}

HeroInterface::HeroInterface(const HeroInterface &other)
: DrawableEntity(other)
{}