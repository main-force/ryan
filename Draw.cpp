#include "Draw.h"

WorldConfig::WorldConfig() {
    width = 0;
    height = 0;
    wall = {};
    floor = {};
}

int WorldConfig::setWorldConfig(std::string& world_config_string) {
    std::vector<std::string> config_vec = ParseConfigure(world_config_string);
    std::stringstream ss;

    // Set width and height of world.
    ss << config_vec[0] << ' ' << config_vec[1];
    ss >> this->width;
    ss >> this->height;

    // Set wall and floor of world.
    wall = Wall{
            .init_col = WORLD_INIT_COLUMN,
            .end_col = WORLD_INIT_COLUMN + int(width) - 1,
    };
    floor = Floor{
            .init_row = WORLD_INIT_ROW,
            .end_row = WORLD_INIT_ROW + int(height) - 1,
    };
    return 0;
}

size_t WorldConfig::getWidth() {
    return this->width;
}

size_t WorldConfig::getHeight() {
    return this->height;
}

Wall WorldConfig::getWall() {
    return wall;
}

Floor WorldConfig::getFloor() {
    return floor;
}

std::vector<std::string> WorldConfig::ParseConfigure(std::string& world_configure_string) {
    std::vector<std::string> config_vector;
    size_t pos = 0;
    std::string config_element;
    while((pos = world_configure_string.find(DELIMETER)) != std::string::npos) {
        config_element = world_configure_string.substr(0, pos);
        config_vector.push_back(config_element);
        world_configure_string.erase(0, pos + 1);
    }
    config_vector.push_back(world_configure_string);
    return config_vector;
}

void Draw::DrawWorld(WorldConfig& world_config, std::string world_string) {
    Floor floor = world_config.getFloor();
    Wall wall = world_config.getWall();
    for(int row = 0; row < world_config.getHeight(); row++) {
        for(int col = 0; col < world_config.getWidth(); col++) {
            size_t target_world_element = row * world_config.getWidth() + col;
            std::string element = world_string.substr(0, 1);
            world_string.erase(0, 1);
            mvprintw(floor.init_row + row, wall.init_col + col, element.c_str());
        }
    }
    refresh();
}

void Draw::DrawWorldConfigure(WorldConfig& world_config) {
    //Draw the walls.;
    for(size_t curs = 0; curs < world_config.getHeight(); curs++) {
        mvprintw(world_config.getFloor().init_row + int(curs), world_config.getWall().init_col - 1, "|");
        mvprintw(world_config.getFloor().init_row + int(curs), world_config.getWall().end_col + 1, "|");
    }

    //Draw the edges.
    mvprintw(world_config.getFloor().init_row - 1, world_config.getWall().init_col - 1, "+");
    mvprintw(world_config.getFloor().init_row - 1, world_config.getWall().end_col + 1, "+");
    mvprintw(world_config.getFloor().end_row + 1, world_config.getWall().end_col + 1, "+");
    mvprintw(world_config.getFloor().end_row + 1, world_config.getWall().init_col - 1, "+");

    //Draw the floor.
    for(size_t curs = 0; curs < world_config.getWidth(); curs++) {
        mvprintw(world_config.getFloor().init_row - 1, world_config.getWall().init_col + int(curs), "-");
        mvprintw(world_config.getFloor().end_row + 1, world_config.getWall().init_col + int(curs), "-");
    }

    //Draw element on the window.
    refresh();
}

void Draw::DrawActant() {
    //Socket 통신을 통해 Actant의 init위치 데이터 가져오기
}