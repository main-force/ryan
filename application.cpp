//여기에다가 데이터 받는 클라이언트용 소켓을 넣어야 함.

#include <ncurses.h>

#define WORLD_WIDTH 64
#define WORLD_HEIGHT 16
//WORLD_INIT_ROW and COLUMN must > 0
#define WORLD_INIT_ROW 2
#define WORLD_INIT_COLUMN 2

struct Wall {
    int init_col = WORLD_INIT_COLUMN;
    int end_col = WORLD_INIT_COLUMN + WORLD_WIDTH - 1;
};

struct Floor {
    int init_row = WORLD_INIT_ROW;
    int end_row = WORLD_INIT_ROW + WORLD_HEIGHT - 1;
};

void DrawWorld() {
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

void DrawActant() {
    //Socket 통신을 통해 Actant의 init위치 데이터 가져오기
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