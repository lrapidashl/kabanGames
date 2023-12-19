#include <iostream>
#include "Weapon.h"

Weapon::Weapon(const std::string& spriteName, const std::string& ammoSpriteName, sf::Vector2f position, float damage, float duration, float delay, float speed, float count)
: DrawableEntity(spriteName, position), damage(damage), duration(duration), delay(delay), speed(speed), count(count)
{
    for (int i = 0; i < (int)count; i++)
    {
        ammo.emplace_back(ammoSpriteName, position);
    }
}

Weapon::Weapon(const Weapon &other)
: DrawableEntity(other), damage(other.damage), duration(other.duration), delay(other.delay), ammoDelay(other.ammoDelay), speed(other.speed), sizeScale(other.sizeScale), count(other.count), time(other.time), ammo(other.ammo)
{}

bool Weapon::isAttack() const
{
    if (time >= delay)
    {
        return true;
    }
    return false;
}

void Weapon::attack(float elapsedTime)
{
    time += elapsedTime;
    if (time >= delay + ammoDelay * (count - 1) + duration)
    {
        time -= delay + ammoDelay * (count - 1) + duration;
    }
    for (int i = 0; i < (int)count; i++)
    {
        ammo[i].update();
    }
}

void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    if (isAttack())
    {
        for (int i = 0; i < (int)count; i++)
        {
            if (time >= delay + ammoDelay * (float)i
                && time <= delay + ammoDelay * (float)i + duration)
            {
                target.draw(ammo[i], states);
            }
        }
    }
}
