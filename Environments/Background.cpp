#include <memory>
#include "Background.h"
#include "GameConsts.h"

Background::Background(const std::string& spriteName)
{
    for(int i = -2; i < 3; i++)
    {
        for (int j = -2; j < 3; j++)
        {
            DrawableEntity tile(spriteName, { 0, 0 });
            tile.setPosition({ (float)WINDOW_WIDTH / 2 + tile.getSize().x * (float)i, (float)WINDOW_HEIGHT / 2 + tile.getSize().y * (float)j });
            tiles.push_back(tile);
        }
    }
}

void Background::move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero)
{
    for (DrawableEntity& tile : tiles)
    {
        moveByHeroDirection(elapsedTime, tile, hero);
        tile.update();
    }
}

void Background::update()
{
    for (auto & tile : tiles)
    {
        if (3 * tile.getSize().x - std::abs(tile.getPosition().x) <= 0)
        {
            tile.setPosition({
                -(tile.getPosition().x) + (tile.getSize().x + std::abs(3 * tile.getSize().x - std::abs(tile.getPosition().x))) * (float)((tile.getPosition().x < 0) ? -1 : 1),
                tile.getPosition().y
            });
        }
        if (3 * tile.getSize().y - std::abs(tile.getPosition().y) <= 0)
        {
            tile.setPosition({
                tile.getPosition().x,
                -(tile.getPosition().y) + (tile.getSize().y + std::abs(3 * tile.getSize().y - std::abs(tile.getPosition().y))) * (float)((tile.getPosition().y < 0) ? -1 : 1)
            });
        }
    }
}

void Background::moveByHeroDirection(float elapsedTime, DrawableEntity& tile, const std::shared_ptr<HeroInterface>& hero)
{
    sf::Vector2f position = tile.getPosition();
    if (isDirectionInVector(hero->getDirections(), Direction::UP))
    {
        position += elapsedTime * sf::Vector2f(0, hero->getSpeed());
    }
    if (isDirectionInVector(hero->getDirections(), Direction::DOWN))
    {
        position -= elapsedTime * sf::Vector2f(0, hero->getSpeed());
    }
    if (isDirectionInVector(hero->getDirections(), Direction::RIGHT))
    {
        position -= elapsedTime * sf::Vector2f(hero->getSpeed(), 0);
    }
    if (isDirectionInVector(hero->getDirections(), Direction::LEFT))
    {
        position += elapsedTime * sf::Vector2f(hero->getSpeed(), 0);
    }
    tile.setPosition(position);
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const DrawableEntity& tile : tiles)
    {
        target.draw(tile, states);
    }
}