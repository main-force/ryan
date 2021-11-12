#include <ncurses.h>

#define WORLD_WIDTH 64
#define WORLD_HEIGHT 16
#define WORLD_INIT_ROW 2
#define WORLD_INIT_COLUMN 2


struct Wall {
    int init_col = WORLD_INIT_COLUMN;
    int end_col = WORLD_INIT_COLUMN + WORLD_WIDTH;
};

struct Floor {
    int init_row = WORLD_INIT_ROW;
    int end_row = WORLD_INIT_ROW + WORLD_HEIGHT;
};

void DrawWorld() {
    //Draw the wall;
    for(size_t curs = 0; curs < WORLD_HEIGHT; curs++) {
        mvprintw(WORLD_INIT_ROW + curs, Wall().init_col - 1, "|");
        mvprintw(WORLD_INIT_ROW + curs, Wall().end_col, "|");
    }

    // Draw the floor.
    for(size_t curs = 0; curs < WORLD_WIDTH; curs++) {
        mvprintw(Floor().init_row - 1, WORLD_INIT_COLUMN + curs, "-");
        mvprintw(Floor().end_row, WORLD_INIT_COLUMN + curs, "-");
    }
    refresh();
}

void Init() {
    initscr();
    noecho(); // 입력을 자동으로 화면에 출력하지 않도록 합니다.
    curs_set(FALSE); // cursor를 보이지 않게 합니다.
    DrawWorld();
}

int main() {
    Init();
    int row = 1, col = 1;
    keypad(stdscr, TRUE);
    while(1){
        int input = getch();

        DrawWorld();
        switch(input){
            case KEY_UP:
                mvprintw(--row, col, "A"); // real moving in your screen
                continue;
            case KEY_DOWN:
                mvprintw(++row, col, "A");
                continue;
            case KEY_LEFT:
                mvprintw(row, --col, "A");
                continue;
            case KEY_RIGHT:
                mvprintw(row, ++col, "A");
                continue;
        }
        if(input == 'q') break;
    }

    endwin();

    return 0;
}