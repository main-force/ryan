//여기에다가 데이터 받는 클라이언트용 소켓을 넣어야 함.
//Socket으로 데이터 받아서 Draw하기.
#include <ncurses.h>
#include <iostream>
#include "DataIO.h"

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

Client::DataIO Init() {
    Client::DataIO data_io;
    while(true) {
        char buff[BUFSIZE];
        std::cout << "Input the message: ";
        std::cin >> buff;
        data_io.SendData(buff);
        data_io.ReceiveData();
        if(data_io.get_result_code() == "E") {
            std::cout << "[Server]:" << data_io.get_result_message() << std::endl;
            break;
        }
        else if(data_io.get_result_code() == "S") {
            std::cout << "[Server]:" << data_io.get_result_message() << std::endl;
            //break;
        }

        else if(data_io.get_result_code() == "C") {
            //Exit
            std::cout << "[Server]:" << data_io.get_result_message() << std::endl;
            break;
        }
    }

    /*
    initscr();
    noecho(); // 입력을 자동으로 화면에 출력하지 않도록 합니다.
    curs_set(FALSE); // cursor를 보이지 않게 합니다.
    DrawWorld();
    */
    return data_io;
}

int main() {
    Client::DataIO data_io = Init();
    /*int row = 1, col = 1;
    keypad(stdscr, TRUE);
    while(1){
        int input = getch();

        //DrawWorld();
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
    */
    return 0;
}