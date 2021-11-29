#ifndef RYAN_WORLD_H
#define RYAN_WORLD_H

#include <cstddef>
#include <vector>
#include "Existence.h"

class World {
public:
    World(size_t width, size_t height);
    int addExistence(Existence& existence);
    int setExistence(Position pos, Existence& existence);

private:
    size_t width{};
    size_t height{};
    std::vector<std::vector<Existence*>> world_matrix;
};

#endif //RYAN_WORLD_H
