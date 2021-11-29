#include "Draw.h"

//WORLD_INIT_ROW and COLUMN must > 0
#define WORLD_INIT_Y 2
#define WORLD_INIT_X 2

struct Wall {
    int init_col = WORLD_INIT_COLUMN;
    int end_col = WORLD_INIT_COLUMN + WORLD_WIDTH - 1;
};

struct Floor {
    int init_row = WORLD_INIT_ROW;
    int end_row = WORLD_INIT_ROW + WORLD_HEIGHT - 1;
};


void Draw::DrawWorld(&World world) {
    //Draw the walls.;
    for(size_t curs = 0; curs < WORLD_HEIGHT; curs++) {
        mvprintw(Floor().init_row + curs, Wall().init_col - 1, "|");
        mvprintw(Floor().init_row + curs, Wall().end_col + 1, "|");
    }

    //Draw the edges.
    mvprintw(Floor().init_row - 1, Wall().init_col - 1, "+");
    mvprintw(Floor().init_row - 1, Wall().end_col + 1, "+");
    mvprintw(Floor().end_row + 1, Wall().end_col + 1, "+");
    mvprintw(Floor().end_row + 1, Wall().init_col - 1, "+");

    //Draw the floor.
    for(size_t curs = 0; curs < WORLD_WIDTH; curs++) {
        mvprintw(Floor().init_row - 1, Wall().init_col + curs, "-");
        mvprintw(Floor().end_row + 1, Wall().init_col + curs, "-");
    }

    //Draw element on the window.
    refresh();
}
