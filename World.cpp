#include "World.h"

World::World(size_t width, size_t height) {
    this->width = width;
    this->height = height;
    for (int i = 0; i < height; i++) {
        world_matrix.emplace_back(std::vector<Existence*>());
        for (int j = 0; j < width; j++) {
            Existence* none_object = new None();
            none_object->setPos(i, j);
            world_matrix[i].emplace_back(none_object);
        }
    }
    std::cout << "World init is succeed." << std::endl;
}

int World::RunOnce(){
    // Run world for one phase.

    std::vector<Existence*> existence_list = getExistenceList();
    for (auto existence : existence_list) {
        existence->RunOnce(world_matrix);
    }
    return 0;
}

std::vector<Existence*> World::getExistenceList() {
    std::vector<Existence*> existence_list;
    for(size_t i = 0; i < getHeight(); i++) {
        for(size_t j = 0; j < getWidth(); j++) {
            if(world_matrix[i][j]->getType() == ACT) {
                existence_list.emplace_back(world_matrix[i][j]);
            }
        }
    }
    return existence_list;
}

std::string World::getWorldMatrixString() {
    std::string result;
    for(auto & y : world_matrix) {
        for (auto & exist : y) {
            result.append(std::to_string(exist->getType()));
        }
    }
    return result;
}

int World::addExistence(Existence& existence) {
    Position target_pos = existence.getPos();
    if (world_matrix[target_pos.x][target_pos.y]->getType() == NONE) {
        Existence* none_object = world_matrix[target_pos.x][target_pos.y];
        world_matrix[target_pos.x][target_pos.y] = &existence;
        delete none_object;
        return 0;
    }
    else {
        // Can't add this position
        delete &existence;
        return -1;
    }
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

size_t World::getWidth() const {
    return this->width;
}

size_t World::getHeight() const {
    return this->height;
}