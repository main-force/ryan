#ifndef RYAN_DATAIO_H
#define RYAN_DATAIO_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>

#define BUFSIZE 4096
#define PORT 9999
#define SERVERIP "127.0.0.1" //Default is local. Change this with your server ip.
#define DELIMETER '$'

namespace Server{
    class DataIO {
    public:
        int ReceiveData();
        static std::string MakeMessage(const char* code, const char* message);
        int SendData(const std::string& send_data) const;
        std::string get_data();
        int ListenConnectionRequest();
        int ClientInfo();
    private:
        struct sockaddr_in caddr{};
        socklen_t caddrSize;
        int socketClient{};
        std::string data;
    };
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
    private:
        int socketServer{};
        std::string data;
        int RequestConnection();
    };
}

std::string convertToString(const char *buff);
#endif //RYAN_DATAIO_H
