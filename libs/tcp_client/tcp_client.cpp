#include "tcp_client.h"
#include <ws2tcpip.h>
#include <string>

TcpClientAPI::~TcpClientAPI()
{
    // Close the socket
    closesocket(sockfd);

    // Clean up the Winsock library
    WSACleanup();
}

int TcpClientAPI::connectToServer(const char *server_name, int port)
{
    // Initialize Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET)
    {
        // printf("Error creating socket: %d\n", WSAGetLastError());
        return -1;
    }

    // Resolve the server address and port
    struct addrinfo hints;
    struct addrinfo *result;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    const char *port_char = std::to_string(port).c_str();

    int iResult = getaddrinfo(server_name, port_char, &hints, &result);
    if (iResult != 0)
    {
        // printf("getaddrinfo failed: %d\n", iResult);
        closesocket(sockfd);
        return -1;
    }

    // Connect to the server
    iResult = connect(sockfd, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        // printf("Error connecting to server: %d\n", WSAGetLastError());
        closesocket(sockfd);
        return -1;
    }

    // Free the addrinfo struct
    freeaddrinfo(result);

    return 0;
}

void TcpClientAPI::disconnectFromServer()
{
    closesocket(sockfd);
    WSACleanup();
}

int TcpClientAPI::getAvailableBytes()
{
    u_long available = 0;
    if (ioctlsocket(sockfd, FIONREAD, &available) == SOCKET_ERROR)
    {
        // std::cerr << "ioctlsocket failed: " << WSAGetLastError() << std::endl;
        return -1;
    }
    return static_cast<int>(available);
}

char *TcpClientAPI::getData(int size)
{
    char *buffer = new char[size];
    int totalReceived = 0;
    while (totalReceived < size)
    {
        int bytesToReceive = size - totalReceived;
        int received = recv(sockfd, buffer + totalReceived, bytesToReceive, 0);
        if (received <= 0)
        {
            if (received == 0)
            {
                // std::cerr << "Server closed the connection." << std::endl;
            }
            else
            {
                // std::cerr << "Error receiving data: " << WSAGetLastError() << std::endl;
            }
            delete[] buffer;
            return nullptr;
        }
        totalReceived += received;
    }
    return buffer;
}

int TcpClientAPI::sendData(char *buf, int len)
{
    int sent = send(sockfd, buf, len, 0);
    if (sent < 0)
    {
        // printf("Error sending data: %d\n", WSAGetLastError());
        return -1;
    }
    return 0;
}
