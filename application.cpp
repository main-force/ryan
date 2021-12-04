#include <ncurses.h>
#include <iostream>
#include <vector>
#include "DataIO.h"
#include "Draw.h"

void InitNcurses() {
    initscr();
    noecho(); // 입력을 자동으로 화면에 출력하지 않도록 합니다.
    curs_set(FALSE); // cursor를 보이지 않게 합니다.
}

void InitWorldConfigure(Client::DataIO& data_io, WorldConfig& world_config) {
    // Send Request world configure. ex) width, height etc...
    if(data_io.SendData("WorldConfigure") == -1) exit(0);
    if(data_io.ReceiveData() == -1) exit(0);
    if(data_io.get_result_code() == "WC") {
        std::string world_configure_string = data_io.get_result_message();
        world_config.setWorldConfig(world_configure_string);
        Draw::DrawWorldConfigure(world_config);
    }
    else {
        std::cout << "Received bad result code in InitWorldConfigure: " << data_io.get_result_code() << std::endl;
        exit(0);
    }
}

int DrawForever(Client::DataIO& data_io, WorldConfig& world_config) {
    while(true) {
        if(data_io.SendData("World") == -1) return -1;
        if(data_io.ReceiveData() == -1) return -1;
        if(data_io.get_result_code() == "W") {
            std::string world_string = data_io.get_result_message();
            Draw::DrawWorld(world_config, world_string);
        }
        else {
            return 1;
        }
    }
}

int main() {
    Client::DataIO data_io;
    WorldConfig world_config;

    InitNcurses();
    InitWorldConfigure(data_io, world_config);

    switch(DrawForever(data_io, world_config)){
        case 1:
            endwin();
            std::cout << "Bad result code received in DrawForever: " << data_io.get_result_code() << std::endl;
            break;
        case -1:
            endwin();
            std::cout << "Connection failed." << std::endl;
            break;
    }

    return 0;
}