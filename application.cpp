//여기에다가 데이터 받는 클라이언트용 소켓을 넣어야 함.
//Socket으로 데이터 받아서 Draw하기.
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <sstream>
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
    WorldConfig() {
        width = 0;
        height = 0;
        wall = {};
        floor = {};
    }
    int setWorldConfig(std::string& world_config_string) {
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
    size_t getWidth() {
        return this->width;
    }
    size_t getHeight() {
        return this->height;
    }

    Wall getWall() {
        return wall;
    }

    Floor getFloor() {
        return floor;
    }
private:
    size_t width;
    size_t height;
    Wall wall{};
    Floor floor{};

    static std::vector<std::string> ParseConfigure(std::string& world_configure_string) {
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

};

void DrawWorldConfigure(WorldConfig& world_config) {
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

void DrawWorld(WorldConfig& world_config, std::string world_string) {
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

void DrawActant() {
    //Socket 통신을 통해 Actant의 init위치 데이터 가져오기
}

int main() {
    // Init
    Client::DataIO data_io;
    WorldConfig world_config;
    initscr();
    noecho(); // 입력을 자동으로 화면에 출력하지 않도록 합니다.
    curs_set(FALSE); // cursor를 보이지 않게 합니다.

    // Send Request world configure. ex) width, height etc...
    if(data_io.SendData("WorldConfigure") == -1) exit(0);
    if(data_io.ReceiveData() == -1) exit(0);
    if(data_io.get_result_code() == "WC") {
        std::string world_configure_string = data_io.get_result_message();
        world_config.setWorldConfig(world_configure_string);
        DrawWorldConfigure(world_config);
    }

    while(true) {
        if(data_io.SendData("World") == -1) break;
        if(data_io.ReceiveData() == -1) break;
        if(data_io.get_result_code() == "W") {
            std::string world_string = data_io.get_result_message();
            DrawWorld(world_config, world_string);
        }
        else {
            break;
        }
    }

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