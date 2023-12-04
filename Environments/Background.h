#ifndef KABAN_GAMES_BACKGROUND_H
#define KABAN_GAMES_BACKGROUND_H

#include "DrawableEntity.h"
#include "HeroInterface.h"

class Background : public sf::Drawable
{
private:
    std::vector<DrawableEntity> tiles;

    static void moveByHeroDirection(float elapsedTime, DrawableEntity& tile, const std::shared_ptr<HeroInterface>& hero);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    explicit Background(const std::string& spriteName);

    void move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero);

    void update();
};

#endif //KABAN_GAMES_BACKGROUND_H
