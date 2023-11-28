#include "Enemies.h"
#include "Random.h"

Enemies::Enemies()
= default;

void Enemies::add(const std::string &spriteName, int enemiesCount, Side side) {
    for (int i = 0; i < enemiesCount; i++)
    {
        int sideNumber = (int)((i + getSideNumber(side)) % SIDES_COUNT);
        if (sideNumber == getSideNumber(Side::RIGHT))
        {
            enemies.push_back(Enemy(spriteName,{
                    Random::random((float)(-RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY), (float)(-RENDER_DISTANCE)),
                    Random::random((float)(-RENDER_DISTANCE), (float)(WINDOW_HEIGHT + RENDER_DISTANCE)) }));
        }
        if (sideNumber == getSideNumber(Side::TOP))
        {
            enemies.push_back(Enemy(spriteName,{
                    Random::random((float)(-RENDER_DISTANCE), (float)(WINDOW_WIDTH + RENDER_DISTANCE)),
                    Random::random((float)(-RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY), (float)(-RENDER_DISTANCE)) }));
        }
        if (sideNumber == getSideNumber(Side::LEFT))
        {
            enemies.push_back(Enemy(spriteName,{
                    Random::random((float)(WINDOW_WIDTH + RENDER_DISTANCE), (float)(WINDOW_WIDTH + RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY)),
                    Random::random((float)(-RENDER_DISTANCE), (float)(WINDOW_HEIGHT + RENDER_DISTANCE)) }));
        }
        if (sideNumber == getSideNumber(Side::BOTTOM))
        {
            enemies.push_back(Enemy(spriteName,{
                    Random::random((float)(-RENDER_DISTANCE), (float)(WINDOW_WIDTH + RENDER_DISTANCE)),
                    Random::random((float)(WINDOW_HEIGHT + RENDER_DISTANCE), (float)(WINDOW_HEIGHT + RENDER_DISTANCE * RENDER_SPREAD_MULTIPLY)) }));
        }
    }
}

std::vector<Enemy> Enemies::getEnemies()
{
    return enemies;
}

void Enemies::enemiesCollision(float elapsedTime) {
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = 0; j < enemies.size(); j++)
        {
            if (i != j)
            {
                float topDelta = std::abs(enemies[i].getPosition().y - enemies[j].getPosition().y - enemies[j].getSize().y);
                float bottomDelta = std::abs(enemies[i].getPosition().y - enemies[j].getPosition().y + enemies[i].getSize().y);
                float leftDelta = std::abs(enemies[i].getPosition().x - enemies[j].getPosition().x - enemies[j].getSize().x);
                float rightDelta = std::abs(enemies[i].getPosition().x - enemies[j].getPosition().x + enemies[i].getSize().x);
                bool horizontalCollision = (enemies[j].getPosition().x <= enemies[i].getPosition().x && enemies[i].getPosition().x <= enemies[j].getPosition().x + enemies[j].getSize().x) || (enemies[j].getPosition().x <= enemies[i].getPosition().x && enemies[i].getPosition().x + enemies[i].getSize().x <= enemies[j].getPosition().x + enemies[j].getSize().x);
                bool verticalCollision = (enemies[j].getPosition().y <= enemies[i].getPosition().y && enemies[i].getPosition().y <= enemies[j].getPosition().y + enemies[j].getSize().y) || (enemies[j].getPosition().y <= enemies[i].getPosition().y && enemies[i].getPosition().y + enemies[i].getSize().y <= enemies[j].getPosition().y + enemies[j].getSize().y);
                bool topCollision = enemies[i].getPosition().y >= enemies[j].getPosition().y && enemies[i].getPosition().y <= enemies[j].getPosition().y + enemies[j].getSize().y + 2;
                bool bottomCollision = enemies[i].getPosition().y + enemies[i].getSize().y >= enemies[j].getPosition().y - 2 && enemies[i].getPosition().y + enemies[i].getSize().y <= enemies[j].getPosition().y + enemies[j].getSize().y;
                bool leftCollision = enemies[i].getPosition().x >= enemies[j].getPosition().x  && enemies[i].getPosition().x <= enemies[j].getPosition().x + enemies[j].getSize().x + 2;
                bool rightCollision = enemies[i].getPosition().x + enemies[i].getSize().x >= enemies[j].getPosition().x - 2 && enemies[i].getPosition().x + enemies[i].getSize().x <= enemies[j].getPosition().x + enemies[j].getSize().x;
                if (i != j)
                {
                    if (horizontalCollision && topCollision)
                    {
                        enemies[i].setPosition({ enemies[i].getPosition().x, enemies[i].getPosition().y + enemies[i].getSpeed() * elapsedTime });
                        enemies[j].setPosition({ enemies[j].getPosition().x, enemies[j].getPosition().y - enemies[j].getSpeed() * elapsedTime });

                    }
                    if (horizontalCollision && bottomCollision)
                    {
                        enemies[i].setPosition({ enemies[i].getPosition().x, enemies[i].getPosition().y - enemies[i].getSpeed() * elapsedTime });
                        enemies[j].setPosition({ enemies[j].getPosition().x, enemies[j].getPosition().y + enemies[j].getSpeed() * elapsedTime });
                    }
                    if (verticalCollision && leftCollision)
                    {
                        enemies[i].setPosition({ enemies[i].getPosition().x + enemies[i].getSpeed() * elapsedTime, enemies[i].getPosition().y });
                        enemies[j].setPosition({ enemies[j].getPosition().x - enemies[j].getSpeed() * elapsedTime, enemies[j].getPosition().y });
                    }
                    if (verticalCollision && rightCollision)
                    {
                        enemies[i].setPosition({ enemies[i].getPosition().x - enemies[i].getSpeed() * elapsedTime, enemies[i].getPosition().y });
                        enemies[j].setPosition({ enemies[j].getPosition().x + enemies[j].getSpeed() * elapsedTime, enemies[j].getPosition().y });
                    }
                }
            }
        }
    }
}

void Enemies::move(float elapsedTime, const Hero& hero)
{
    for (Enemy& enemy : enemies)
    {
        enemy.move(elapsedTime, hero);
    }
}

void Enemies::update() {
    for (Enemy& enemy : enemies)
    {
        enemy.update();
    }
}