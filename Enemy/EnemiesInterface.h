#ifndef KABAN_GAMES_ENEMIESINTERFACE_H
#define KABAN_GAMES_ENEMIESINTERFACE_H

#include "Enemy.h"

class EnemiesInterface
{
public:
    EnemiesInterface();

    EnemiesInterface(const EnemiesInterface& other);

    virtual std::vector<Enemy> getEnemies() const = 0;
};


#endif //KABAN_GAMES_ENEMIESINTERFACE_H
