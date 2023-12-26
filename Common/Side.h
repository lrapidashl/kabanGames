#ifndef KABAN_GAMES_SIDE_H
#define KABAN_GAMES_SIDE_H

const unsigned SIDES_COUNT = 4;

enum struct Side
{
    RIGHT,
    TOP,
    LEFT,
    BOTTOM,
};

int getSideNumber(Side side);

Side getRandomSide();

#endif //KABAN_GAMES_SIDE_H
