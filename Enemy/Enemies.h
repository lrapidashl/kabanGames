#ifndef KABAN_GAMES_ENEMIES_H
#define KABAN_GAMES_ENEMIES_H
#include <vector>
#include "Enemy.h"
#include "EnemiesInterface.h"

class Enemies : public EnemiesInterface
{
private:
    std::vector<Enemy> enemies;
public:
    Enemies();

    explicit Enemies(Enemies* other);

    void add(const std::string& spriteName, int enemiesCount, Side side = Side::RIGHT);

    std::vector<Enemy> getEnemies() const override;

    void setEnemies(const std::vector<Enemy>& enemies) override;

    void enemiesCollision(float elapsedTime);

    void move(float elapsedTime, const std::shared_ptr<HeroInterface>& hero);

    void update();
};

#endif //KABAN_GAMES_ENEMIES_H