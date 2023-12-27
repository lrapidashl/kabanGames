#ifndef KABAN_GAMES_EXPERIENCE_H
#define KABAN_GAMES_EXPERIENCE_H

#include <memory>
#include "DrawableEntity.h"
#include "HeroInterface.h"

class Experience : public sf::Drawable
{
private:
    std::vector<DrawableEntity> gems {};
    std::string                 spriteName;
    float                       speed = 200;

    static float getVectorLength(sf::Vector2f vector);

    static void moveByHeroDirection(float elapsedTime, DrawableEntity& tile, const std::shared_ptr<HeroInterface>& hero);

    void moveToHero(float elapsedTime, DrawableEntity& tile, const std::shared_ptr<HeroInterface>& hero) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
public:
    explicit Experience(std::string spriteName);

    Experience(const Experience& other);

    std::vector<DrawableEntity> getGems() const;

    void setGems(const std::vector<DrawableEntity>& gems);

    void spawn(const sf::Vector2f& position);

    void move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero);
};

#endif //KABAN_GAMES_EXPERIENCE_H
