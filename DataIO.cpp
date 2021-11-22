#include "DataIO.h"
#include <string>
#include <unistd.h>
#include <iostream>
#include <sstream>


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
    struct sockaddr_in saddr = {
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

    if (bind(socketServer, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
        std::cerr << "Not able to bind to the socket." << std::endl;
        return -1;
    }

    //Listening
    listen(socketServer, SOMAXCONN);

    //Print
    std::cout << "[Server] Listen on port " << PORT << std::endl;

    //Waiting client
    caddrSize = sizeof(caddr);
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
    char buff[BUFSIZE];
    ssize_t sizeInBytesOfReceiveData;

    caddrSize = sizeof(caddr);
    sizeInBytesOfReceiveData = recv(socketClient, buff, BUFSIZE, 0);

    if (sizeInBytesOfReceiveData == -1) {
        std::cerr << "Error while receive message. Quiting: " << strerror(errno);
        return -1;
    } else if (sizeInBytesOfReceiveData == 0) {
        std::cout << "Client Disconnected" << std::endl;
        return -1;
    }
    std::cout << std::string(buff, 0, sizeInBytesOfReceiveData) << std::endl;

    data = convertToString(buff);

    return 0;
}

std::string Server::DataIO::MakeMessage(const char* code, const char* message){
    std::stringstream ss;
    ss << code;
    ss << DELIMETER;
    ss << message;
    return ss.str();
}

int Server::DataIO::SendData(const std::string& send_data) const {
    char buff[BUFSIZE];
    strcpy(buff, send_data.c_str());

    if(send(socketClient, buff, BUFSIZE, 0) == -1) {
        if(errno != EINTR) {
            fprintf(stderr, "Send Error: %s\n", strerror(errno)); return -1;
        }
    }
    else {
        std::cout << "Completely send the message." << std::endl;
    }

    return 0;
}
std::string Server::DataIO::get_data() {
    return data;
}

//---------------------------Client-----------------------------
Client::DataIO::DataIO() {
    RequestConnection();
}

Client::DataIO::~DataIO() {
    close(socketServer);

}


int Client::DataIO::RequestConnection() {
    struct sockaddr_in saddr = {
            .sin_family = AF_INET,
            .sin_port = htons(PORT),
            .sin_addr = in_addr { .s_addr = inet_addr(SERVERIP) }
    };

    socketServer = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(socketServer, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
        std::cerr << "Connecting Failed." << std::endl;
        return -1;
    }

    return 0;
}

int Client::DataIO::SendData(const std::string& send_data) const {
    char buff[BUFSIZE];
    strcpy(buff, send_data.c_str());

    if(send(socketServer, buff, BUFSIZE, 0) == -1) {
        if(errno != EINTR) {
            fprintf(stderr, "Send Error: %s\n", strerror(errno)); return -1;
        }
    }
    else {
        std::cout << "Completely send the message." << std::endl;
    }
    return 0;
}

int Client::DataIO::ReceiveData() {
    ssize_t sizeInBytesOfReceiveData;

    char buff[BUFSIZE];

    sizeInBytesOfReceiveData = recv(socketServer, buff, BUFSIZE, 0);
    if (sizeInBytesOfReceiveData == -1) {
        std::cerr << "Error while receive message. Quiting: " << strerror(errno);
        return -1;
    } else if (sizeInBytesOfReceiveData == 0) {
        std::cout << "Server Disconnected" << std::endl;
        return -1;
    }

    //Receive Complete.
    data = convertToString(buff);
    return 0;
}

std::string Client::DataIO::get_result_code() {
    const std::string received_string = data;
    size_t pos = received_string.find(DELIMETER);
    return received_string.substr(0, pos);
}

std::string Client::DataIO::get_result_message() {
    const std::string received_string = data;
    size_t pos = received_string.find(DELIMETER);
    return received_string.substr(pos + 1, received_string.length());
}

//==============================================

std::string convertToString(const char *buff) {
    std::string buff_to_string(buff);
    return buff_to_string;
}