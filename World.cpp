#include "World.h"

//==========Configure==========
#define WORLD_WIDTH 64
#define WORLD_HEIGHT 16

//WORLD_INIT_ROW and COLUMN must > 0
#define WORLD_INIT_Y 2
#define WORLD_INIT_X 2
//==========Configure==========

World::World() {
    width = WORLD_WIDTH;
    height = WORLD_HEIGHT;
    width_pos = WidthPosition {
            .init_x = WORLD_INIT_X,
            .end_x = WORLD_INIT_X + WORLD_WIDTH - 1
    };
    height_pos = HeightPosition {
            .init_y = WORLD_INIT_Y,
            .end_y = WORLD_INIT_Y + WORLD_HEIGHT - 1
    };
}