#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <future>
#include <chrono>
#include "World.h"
#include "Actant.h"
#include "Object.h"
#include "DataIO.h"

//--------------------------------------



void Init(std::promise<Server::DataIO> &&promised_data_io) {
    Server::DataIO data_io;
    //auto* data_io = new Server::DataIO;
    data_io.ListenConnectionRequest();
    while(true) {
        data_io.ReceiveData();
        if(data_io.get_data() == "Start") {
            std::string message = Server::DataIO::MakeMessage("C", "Complete");
            data_io.SendData(message);
            promised_data_io.set_value(data_io);
            break;
        }
        else {
            std::string message = Server::DataIO::MakeMessage("F", "Please send 'Start' first.");
            data_io.SendData(message);
        }
    }
}

int main() {
    Server::DataIO data_io;
    std::promise<Server::DataIO> promised_data_io;
    auto future_data_io = promised_data_io.get_future();
    std::thread listen_client(&Init, std::move(promised_data_io));

    while(true) {
        if (future_data_io.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "Not Connected" << std::endl;
        }
        else {
            //End Init.
            std::cout << "Connected" << std::endl;
            //Send the world data to client.
            data_io = future_data_io.get();
            listen_client.join();
            while(true) {
                data_io.ReceiveData();
                if(data_io.get_data() == "Hello") {
                    std::cout << "Receive Hello" << std::endl;
                    data_io.SendData(Server::DataIO::MakeMessage("E", "Exit."));
                    break;
                }
                else {
                    std::cout << data_io.get_data() << std::endl;
                    data_io.SendData(Server::DataIO::MakeMessage("C", "Server:Complete receive the message."));
                }
            }
            break;
        }
    }



    /*while(true) {
        if(data_io.ReceiveData() == -1) break;
        std::cout << "Received: " << data_io.get_data() << std::endl;
    }
    World world;
    Actant actant1;
    */

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
