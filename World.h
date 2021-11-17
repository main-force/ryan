#include <cstddef>

#ifndef RYAN_WORLD_H
#define RYAN_WORLD_H

struct WidthPosition {
    int init_x;
    int end_x;
};

struct HeightPosition {
    int init_y;
    int end_y;
};

class World {
public:
    World();
private:
    size_t width{};
    size_t height{};
    WidthPosition width_pos{};
    HeightPosition height_pos{};
};

#endif //RYAN_WORLD_H
