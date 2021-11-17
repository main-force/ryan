#ifndef RYAN_DATAIO_H
#define RYAN_DATAIO_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUFSIZE 4096
#define PORT 9999

class DataIO {
public:
    DataIO();
    ~DataIO();
    int ReceiveData();
    char *get_data();
    int ClientInfo();
private:
    struct sockaddr_in caddr;
    socklen_t caddrSize;
    int socketClient;
    char buff[BUFSIZE];
    int ListenConnectionRequest();
};

#endif //RYAN_DATAIO_H
