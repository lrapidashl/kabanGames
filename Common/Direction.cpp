#include <algorithm>
#include "Direction.h"

bool isDirectionInVector(std::vector<Direction> directions, Direction direction)
{
    return std::find(directions.begin(), directions.end(), direction) != directions.end();
}