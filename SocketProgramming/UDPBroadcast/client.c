// Broadcast_client.cpp : Defines the entry point for the console application.
//
#ifdef _WIN32
    #include "stdafx.h"
    #include <Winsock2.h> // before Windows.h, else Winsock 1 conflict
    #include <Ws2tcpip.h> // needed for ip_mreq definition for multicast
    #include <Windows.h>
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MSG                       100
#define BROADCAST_PORT                5001


int main(int argc, char *argv[]) {

    int iRetVal = 0;
    int iSocket = 0;
    int cliLen = 0;
    int broadcast = 1;
    int ireuse = 1;

    char arrcBuffer[MAX_MSG] = {0};
    struct sockaddr_in BrdCastServAddr = {0};
    struct sockaddr_in ClientAddr = {0};

    #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(0x0101, &wsaData)) {
            perror("WSAStartup");
            return 1;
        }
    #endif

    /* socket creation */
    iSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(iSocket < 0) 
    {
        printf("%d: cannot open socket \n", iSocket);
        exit(1);
    }

    /* allow multiple sockets to use the same PORT number */
    if (setsockopt(iSocket, SOL_SOCKET, SO_REUSEADDR, (char*) &ireuse, sizeof(ireuse)) < 0)
    {
       perror("Reusing ADDR failed");
       exit(1);
    }

    /* bind to broadcast port */   
    ClientAddr.sin_family = AF_INET;
    ClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ClientAddr.sin_port = htons(BROADCAST_PORT);

    iRetVal = bind (iSocket, (struct sockaddr *) &ClientAddr, sizeof(ClientAddr));
    if(iRetVal < 0) 
    {
        printf("%d: cannot bind port number %d\n", iRetVal, BROADCAST_PORT);
        exit(1);
    }

    while(1)
    {
        memset(arrcBuffer, 0, sizeof(arrcBuffer));

        cliLen = sizeof(BrdCastServAddr);
        iRetVal = recvfrom(iSocket, arrcBuffer, MAX_MSG, 0, (struct sockaddr *) &BrdCastServAddr, &cliLen);
        if(iRetVal < 0)
        {
            printf("%d: cannot receive data \n", iRetVal);
        }
        else
        {
            printf("received: %s\n", arrcBuffer);
        }
    }

    #ifdef _WIN32
        WSACleanup();
    #endif

    return 0;
}
