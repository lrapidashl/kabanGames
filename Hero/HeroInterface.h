#ifndef KABAN_GAMES_HEROINTERFACE_H
#define KABAN_GAMES_HEROINTERFACE_H

#include "Direction.h"
#include "DrawableEntity.h"

class HeroInterface : public DrawableEntity
{
public:
    HeroInterface(const std::string& spriteName, sf::Vector2f position);

    HeroInterface(const HeroInterface &other);

    virtual float getSpeed() const = 0;

    virtual std::vector<Direction> getDirections() const = 0;

    virtual float getExpRadius() const = 0;
};

#endif //KABAN_GAMES_HEROINTERFACE_H
