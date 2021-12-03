#ifndef RYAN_DATAIO_H
#define RYAN_DATAIO_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <future>
#include <unordered_map>
#include <functional>
#include <vector>

#include "World.h"

#define BUFSIZE 4096
#define PORT 9999
#define SERVERIP "127.0.0.1" //Default is local. Change this with your server ip.
#define DELIMETER '$'

namespace Server{
    class DataIO {
    public:
        DataIO();

        int ListenConnectionRequest();
        int ClientInfo();
        int ReceiveData();
        int SendData(const std::string& send_data);
        int SendWorldConfigure(World& world);
        int SendWorld(World& world);
        int ProcessReceivedData();
        std::string get_data();
        bool IsConnected();
        int CloseSocket();

    private:
        bool is_connected = false;
        struct sockaddr_in caddr{};
        socklen_t caddrSize{};
        int socketServer{};
        int socketClient{};
        std::string data;
        std::unordered_map<std::string, std::function<int(Server::DataIO&)>> req_res_map;
        int ClientStart();
        int ClientExit();
        int BadRequest();
    };

    void ClientConnectionWait(std::promise<Server::DataIO> &&promised_data_io);
    bool IsConnectedToClient(std::future_status connection_status);
    std::string MakeMessage(const char* code, const char* message);
}

//Until here. World 요구사항을 Server로부터 당겨오기.
namespace Client{
    class DataIO {
    public:
        DataIO();
        ~DataIO();
        int ReceiveData();
        int SendData(const std::string& send_data) const;
        std::string get_result_code();
        std::string get_result_message();
        DataIO Init();
    private:
        int socketServer{};
        std::string data;
        int RequestConnection();
    };
}

std::string convertToString(const char *buff);
#endif //RYAN_DATAIO_H
