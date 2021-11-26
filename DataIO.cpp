#include "DataIO.h"
#include <string>
#include <unistd.h>
#include <iostream>
#include <sstream>

Server::DataIO::DataIO() {
    req_res_map["Start"] = &Server::DataIO::ClientStart;
    req_res_map["Exit"] = &Server::DataIO::ClientExit;
    // Start and Exit execute flow control.
    // So, if you change the trigger message,
    // Exit: you must go server.cpp and change the if condition.
    // Start:
}

int Server::DataIO::ListenConnectionRequest() {
    //Server
    struct sockaddr_in saddr = {
            .sin_family = AF_INET,
            .sin_port = htons(PORT),
            .sin_addr = in_addr { .s_addr = INADDR_ANY }
    };
    int option = 1;
    socketServer = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(socketServer, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option));
    if (socketServer == -1) {
        std::cerr << "[ServerErr]:" << "Not able to create our socket! Getting out." << std::endl;
        return -1;
    }
    if (bind(socketServer, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
        std::cerr << "[ServerErr]:" << "Not able to bind to the socket." << std::endl;
        std::cout << strerror(errno) << std::endl;

        return -1;
    }

    //Listening
    listen(socketServer, SOMAXCONN);
    //Print
    std::cout << "[Server]:Listen on port " << PORT << std::endl;

    //Waiting client
    caddrSize = sizeof(caddr);
    socketClient = accept(socketServer, (struct sockaddr*)&caddr, (socklen_t*)&caddrSize);

    //Connection success.
    is_connected = true;
    std::cout << "[Server]:Client connected with success." << std::endl;

    return 0;
}

int Server::DataIO::ClientInfo() {
    char hostClient[NI_MAXHOST];
    char portClient[32];
    memset(hostClient, 0, NI_MAXHOST);
    memset(portClient, 0, 32);
    if (getnameinfo((sockaddr*)&caddr, sizeof(caddr), hostClient, NI_MAXHOST, portClient, NI_MAXSERV, 0) == 0) {
        std::cout << "[Server]:" << hostClient << " connected to the port " << portClient << std::endl;
    } else {
        inet_ntop(AF_INET, &caddr.sin_addr, hostClient, NI_MAXHOST);
        std::cout << "[Server]:" << hostClient << " connected to the port " << ntohs(caddr.sin_port) << std::endl;
    }

    return 0;
}

int Server::DataIO::ReceiveData() {
    char buff[BUFSIZE];
    ssize_t sizeInBytesOfReceiveData;

    caddrSize = sizeof(caddr);
    sizeInBytesOfReceiveData = recv(socketClient, buff, BUFSIZE, 0);

    if (sizeInBytesOfReceiveData == -1) {
        std::cerr << "[Server]:Error while receive message$" << strerror(errno) << std::endl;
        CloseSocket();
        return -1;
    } else if (sizeInBytesOfReceiveData == 0) {
        std::cout << "[Server]:Client Disconnected" << std::endl;
        CloseSocket();
        return -1;
    }
    data = convertToString(buff);
    std::cout << "[Client]:" << data << std::endl;

    return 0;
}

int Server::DataIO::SendData(const std::string& send_data) {
    char buff[BUFSIZE];
    strcpy(buff, send_data.c_str());

    if(send(socketClient, buff, BUFSIZE, 0) == -1) {
        if(errno != EINTR) {
            std::cerr << "[Server]:Send Error$" << strerror(errno) << std::endl;
            CloseSocket();
            return -1;
        }
    }
    else {
        std::cout << "[Server]:" << send_data << std::endl;
    }

    return 0;
}

int Server::DataIO::ProcessReceivedData() {
    if (req_res_map.find(data) == req_res_map.end()){
        return BadRequest();
    } else {
        return req_res_map[data](*this);
    }
}

std::string Server::DataIO::get_data() {
    return data;
}

bool Server::DataIO::IsConnected() {
    return is_connected;
}

void Server::DataIO::CloseSocket() {
    SendData(Server::MakeMessage("C", "Close connection."));
    is_connected = false;
    close(socketServer);
    close(socketClient);
}

int Server::DataIO::ClientStart() {
    ClientInfo();
    // S: Success
    return SendData(Server::MakeMessage("S", "Connect server with client."));
}

int Server::DataIO::ClientExit() {
    // C: Close
    CloseSocket();
    return 0;
}

int Server::DataIO::BadRequest() {
    //E: Error
    return SendData(Server::MakeMessage("E", "You sent bad request."));
}

//--------------------------------------------

std::string Server::MakeMessage(const char* code, const char* message) {
    std::stringstream ss;
    ss << code;
    ss << DELIMETER;
    ss << message;
    return ss.str();
}

void Server::ClientConnectionWait(std::promise<Server::DataIO> &&promised_data_io) {
    Server::DataIO data_io;

    while(true) {
        if(data_io.ListenConnectionRequest() == 0) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }

    {
        if(data_io.ReceiveData() == -1){
            promised_data_io.set_value(data_io);
        }

        if(data_io.get_data() == "Start") {
            data_io.ProcessReceivedData();
            promised_data_io.set_value(data_io);
        }
        else {
            promised_data_io.set_value(data_io);
            data_io.SendData(Server::MakeMessage("E", "Please send 'Start' first."));
        }
    }
    //Server의 Process를 따로 만들까...
}

bool Server::IsConnectedToClient(std::future_status connection_status) {
    if (connection_status == std::future_status::ready) { return true; }
    else { return false; }
}
//---------------------------Client-----------------------------
Client::DataIO::DataIO() {
    if (RequestConnection() == -1) {
        std::exit(-1);
    }
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
        std::cerr << "[Client]:Connecting Failed." << std::endl;
        return -1;
    }

    return 0;
}

int Client::DataIO::SendData(const std::string& send_data) const {
    char buff[BUFSIZE];
    strcpy(buff, send_data.c_str());

    if(send(socketServer, buff, BUFSIZE, 0) == -1) {
        if(errno != EINTR) {
            fprintf(stderr, "[Client]:Send Error: %s\n", strerror(errno)); return -1;
        }
    }
    else {
        std::cout << "[Client]:" << send_data << std::endl;
    }
    return 0;
}

int Client::DataIO::ReceiveData() {
    ssize_t sizeInBytesOfReceiveData;

    char buff[BUFSIZE];

    sizeInBytesOfReceiveData = recv(socketServer, buff, BUFSIZE, 0);
    if (sizeInBytesOfReceiveData == -1) {
        std::cerr << "[Client]:Error while receive message. Quiting: " << strerror(errno);
        return -1;
    } else if (sizeInBytesOfReceiveData == 0) {
        std::cout << "[Client]:Server Disconnected" << std::endl;
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

