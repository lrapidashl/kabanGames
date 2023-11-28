#ifndef KABAN_GAMES_ENEMIES_H
#define KABAN_GAMES_ENEMIES_H
#include <vector>
#include "Enemy.h"
#include "Side.h"

class Enemies
{
private:
    std::vector<Enemy> enemies;
public:
    Enemies();

    void add(const std::string& spriteName, int enemiesCount, Side side = Side::RIGHT);

    std::vector<Enemy> getEnemies();

    std::vector<sf::Vector2f> getEnemiesPositions();

    void enemiesCollision(float elapsedTime);

    void move(float elapsedTime, const Hero& hero);

    void update();
};

#endif //KABAN_GAMES_ENEMIES_H