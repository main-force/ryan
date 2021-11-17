#include <iostream>
#include <vector>
#include "World.h"
#include "Actant.h"
#include "Object.h"
#include "DataIO.h"
//--------------------------------------

int main() {
    Server::DataIO data_io;
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
