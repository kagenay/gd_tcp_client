#ifndef TCP_CLIENT_API_H
#define TCP_CLIENT_API_H

#include <winsock2.h>

class TcpClientAPI
{
public:
    ~TcpClientAPI();
    int connectToServer(const char *server_name, int port);
    void disconnectFromServer();
    char *getData(int size);
    int getAvailableBytes();
    int sendData(char *buf, int len);

private:
    SOCKET sockfd;
};

#endif