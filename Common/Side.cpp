#include "Side.h"
#include "Random.h"

int getSideNumber(Side side)
{
    switch (side)
    {
        case Side::RIGHT:
            return 0;
        case Side::TOP:
            return 1;
        case Side::LEFT:
            return 2;
        case Side::BOTTOM:
            return 3;
    }
}

Side getRandomSide()
{
    switch ((int)std::floor(Random::random(0, SIDES_COUNT)))
    {
        case 0:
            return Side::RIGHT;
        case 1:
            return Side::TOP;
        case 2:
            return Side::LEFT;
        case 3:
            return Side::BOTTOM;
    }
}