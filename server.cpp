#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "World.h"
#include "Actant.h"
#include "Object.h"
#include "DataIO.h"
//--------------------------------------



Server::DataIO Init() {
    Server::DataIO data_io;
    while(true) {
        data_io.ReceiveData();
        if(data_io.get_data() == "Start") {
            std::string message = Server::DataIO::MakeMessage("C", "Complete");
            data_io.SendData(message);
            return data_io;
        }
        else {
            std::string message = Server::DataIO::MakeMessage("F", "Please send 'Start' first.");
            data_io.SendData(message);
        }
    }
}

int main() {
    Server::DataIO data_io = Init();

    while(true) {
        if(data_io.ReceiveData() == -1) break;
        std::cout << "Received: " << data_io.get_data() << std::endl;
    }
    World world;
    Actant actant1;

    /*
    while(true) {
        if (actant1.isSafe()) {
            //추가적인 일을 하면 됨...
        }
        else  { //안전하지 못한 상태일 때
            UniqueCharacter target_character = actant1.FindSolverCharacter();
            //actant1.Solve(target_character);
        }
        break;
    }
     */
    return 0;
}
