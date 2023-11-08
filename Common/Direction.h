#include <vector>

enum struct Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

bool isDirectionInVector(std::vector<Direction> directions, Direction direction);