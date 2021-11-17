#include "DataIO.h"
#include <string>
#include <unistd.h>
#include <iostream>

Server::DataIO::DataIO() {
    caddrSize = sizeof(caddr);
    ListenConnectionRequest();
}

Server::DataIO::~DataIO() {
    close(socketClient);
}

int Server::DataIO::ClientInfo() {
    char hostClient[NI_MAXHOST];
    char portClient[32];
    memset(hostClient, 0, NI_MAXHOST);
    memset(portClient, 0, 32);
    if (getnameinfo((sockaddr*)&caddr, sizeof(caddr), hostClient, NI_MAXHOST, portClient, NI_MAXSERV, 0) == 0) {
        std::cout << "in if" << std::endl;
        std::cout << " --> " << hostClient << " connected to the port " << portClient << std::endl;
    } else {
        std::cout << "in else" << std::endl;
        inet_ntop(AF_INET, &caddr.sin_addr, hostClient, NI_MAXHOST);
        std::cout << " --> " << hostClient << " connected to the port " << ntohs(caddr.sin_port) << std::endl;
    }

    return 0;
}

int Server::DataIO::ListenConnectionRequest() {
    //Server
    struct sockaddr_in s_addr = {
            .sin_family = AF_INET,
            .sin_port = htons(PORT),
            .sin_addr = in_addr { .s_addr = INADDR_ANY }
    };

    int option = 1;
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(socketServer, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
    if (socketServer == -1) {
        std::cerr << "Not able to create our socket! Getting out." << std::endl;
        return -1;
    }

    if (bind(socketServer, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1) {
        std::cerr << "Not able to bind to the socket." << std::endl;
        return -1;
    }

    //Listening
    listen(socketServer, SOMAXCONN);

    //Print
    std::cout << "[Server] Listen on port " << PORT << std::endl;

    //Waiting client
    socketClient = accept(socketServer, (struct sockaddr*)&caddr, (socklen_t*)&caddrSize);

    //=============================================
    std::cout << "[Server] Client connected with success." << std::endl;
    //Try find client
    char hostClient[NI_MAXHOST];
    char portClient[32];
    memset(hostClient, 0, NI_MAXHOST);
    memset(portClient, 0, 32);
    if (getnameinfo((sockaddr*)&caddr, sizeof(caddr), hostClient, NI_MAXHOST, portClient, NI_MAXSERV, 0) == 0) {
        std::cout << "in if" << std::endl;
        std::cout << " --> " << hostClient << " connected to the port " << portClient << std::endl;
    } else {
        std::cout << "in else" << std::endl;
        inet_ntop(AF_INET, &caddr.sin_addr, hostClient, NI_MAXHOST);
        std::cout << " --> " << hostClient << " connected to the port " << ntohs(caddr.sin_port) << std::endl;
    }

    return 0;
}

int Server::DataIO::ReceiveData() {
    ssize_t sizeInBytesOfReceiveData;

    sizeInBytesOfReceiveData = recv(socketClient, buff, BUFSIZE, 0);
    if (sizeInBytesOfReceiveData == -1) {
        std::cerr << "Error while receive message. Quiting";
        return -1;
    } else if (sizeInBytesOfReceiveData == 0) {
        std::cout << "Client Disconnected" << std::endl;
        return 0;
    }
    send(socketClient, buff, sizeInBytesOfReceiveData, 0);

    std::cout << std::string(buff, 0, sizeInBytesOfReceiveData) << std::endl;

    return 0;
}


char *Server::DataIO::get_data() {
    return buff;
}
