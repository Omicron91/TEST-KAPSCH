#include "networking.h"


int hostLocalServer(int port)
{
    int socketFd;
    struct sockaddr_in serverAddr;

    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
    {
        printf("Socket creation failed\n");
        return -1;
    }

    printf("Socket created!\n");

    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    if ((bind(socketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) != 0)
    {
        printf("Socketed bind failed\n");
        return -2;
    }

    printf("Socket binded!\n");

    if ((listen(socketFd, 5)) != 0)
    {
        printf("Listen failed\n");
        return -3;
    }

    printf("Socket listening on port %d...\n", port);

    return socketFd;
}


int connect2server(char *host, int port)
{
    int socketFd, ServerAddrLen;
    struct sockaddr_in serverAddr, ServerAddr;

    ServerAddrLen = sizeof(ServerAddr);

    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFd == -1)
    {
        printf("Socket creation failed...\n");
        return -1;
    }

    printf("Socket created!\n");

    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &serverAddr.sin_addr) <= 0) {
        printf("Invalid address or address not supported...\n");
        return -2;
    }

    if ((connect(socketFd, (struct sockaddr *)&serverAddr, ServerAddrLen)) < 0)
    {
        printf("Connection failed...\n");
        return -3;
    }
    
    printf("Connected to the server %s @ %d...\n", host, port);

    return socketFd;
}
