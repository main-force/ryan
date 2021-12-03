#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <future>
#include <chrono>
#include "World.h"
#include "DataIO.h"
#include "Existence.h"
//==========Configure==========
#define WORLD_WIDTH 64
#define WORLD_HEIGHT 16
//==========Configure==========

int main() {
    // Listen client connection request the other thread.
    // have to fix this future data io.
    Server::DataIO data_io;
    std::future<Server::DataIO> future_data_io;
    bool is_running_thread = false;

    // Init World.
    World world(WORLD_WIDTH, WORLD_HEIGHT);
    Actant actant(8, 32);
    world.addExistence(actant);

    // Delete later.
    size_t cnt = 0;

    while(true) {
        if(!is_running_thread) {
            std::promise<Server::DataIO> promised_data_io;
            future_data_io = promised_data_io.get_future();
            std::thread listen_client(&Server::ClientConnectionWait, std::move(promised_data_io));
            listen_client.detach();
            is_running_thread = true;
        }

        auto connection_status = future_data_io.wait_for(std::chrono::milliseconds(0));
        if (Server::IsConnectedToClient(connection_status)) {
            data_io = future_data_io.get();
            is_running_thread = false;
            //클라이언트한테 월드 요청 리퀘스트 대기 후 World 데이터 전송.
            //Send the world data to client.
            data_io.SendWorldConfigure(world);
            int num = 33;
            while(true) {
                //RunOnce()은 Actant의 Event(상호작용) 한번이 루프 한번.
                //RunOnce();
                if (data_io.SendWorld(world) == -1) {
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            }
           // Restart listening client connection request.
        }
        else {
            cnt++;
            if(cnt == 500) { break; }
            //RunOnce();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "[Server]:Not Connected" << std::endl;
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
