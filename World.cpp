#include "World.h"

World::World(size_t width, size_t height) {
    width = width;
    height = height;
    for (size_t i = 0; i < height; i++) {
        world_matrix.emplace_back(std::vector<Existence*>(width, new None()));
    }
    std::cout << "World init is succeed." << std::endl;
}

int World::addExistence(Existence& existence) {
    Position origin_pos = existence.getPos();
    auto none_existence = world_matrix[origin_pos.x][origin_pos.y];
    world_matrix[origin_pos.x][origin_pos.y] = &existence;
    delete none_existence;
    return 0;
}

int World::setExistence(Position pos, Existence& existence) {
    Position origin_pos = existence.getPos();
    // 항상 그 칸에 있는 None 메모리는 메모리 해제 or existence의 위치로 이동.
    // 여기서는 existence가 항상 이동 가능하다고 가정.
    // 이동가능한 곳은 None인 곳.
    Existence* none_existence = world_matrix[pos.x][pos.y];
    world_matrix[pos.x][pos.y] = &existence;
    world_matrix[origin_pos.x][origin_pos.y] = none_existence;
    return 0;
}
