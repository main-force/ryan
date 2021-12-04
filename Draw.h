#ifndef RYAN_DRAW_H
#define RYAN_DRAW_H

#include <string>
#include <vector>
#include <sstream>
#include <ncurses.h>
#include "World.h"
#include "DataIO.h"

//WORLD_INIT_ROW and COLUMN must > 0
#define WORLD_INIT_ROW 2
#define WORLD_INIT_COLUMN 2

struct Wall {
    int init_col;
    int end_col;
};

struct Floor {
    int init_row;
    int end_row;
};

class WorldConfig {
public:
    WorldConfig();
    int setWorldConfig(std::string& world_config_string);
    size_t getWidth();
    size_t getHeight();
    Wall getWall();
    Floor getFloor();

private:
    size_t width;
    size_t height;
    Wall wall{};
    Floor floor{};
    static std::vector<std::string> ParseConfigure(std::string& world_configure_string);
};

class Draw {
public:
    static void DrawWorld(WorldConfig& world_config, std::string world_string);
    static void DrawWorldConfigure(WorldConfig& world_config);
    void DrawActant();
};

#endif //RYAN_DRAW_H
