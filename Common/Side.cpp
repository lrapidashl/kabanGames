#include "Side.h"

int getSideNumber(Side side)
{
    switch (side) {
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