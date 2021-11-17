#ifndef RYAN_DATAIO_H
#define RYAN_DATAIO_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUFSIZE 4096
#define PORT 9999
#define SERVERIP "127.0.0.1" //Default is local. Change this with your server ip.

namespace Server{
    class DataIO {
    public:
        DataIO();
        ~DataIO();
        int ReceiveData();
        char *get_data();
        int ClientInfo();
    private:
        struct sockaddr_in caddr{};
        socklen_t caddrSize;
        int socketClient{};
        char buff[BUFSIZE]{};
        int ListenConnectionRequest();
    };
}

//Until here. World 요구사항을 Server로부터 당겨오기.
namespace Client{
    class DataIO {
    public:
        DataIO();
        ~DataIO();
        int ReceiveData();
        int SendData();
        char *get_data();
    private:
        int socketClient{};
        char buff[BUFSIZE]{};
        int RequestConnection();
    };
}

#endif //RYAN_DATAIO_H
