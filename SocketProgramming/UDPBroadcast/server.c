// Broadcast_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#ifdef _WIN32
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

#define MAX_MSG             100

// #define BIND_SERVER
#define SERVER_PORT         1000

#define ENABLE_BROADCAST
#define BROADCAST_PORT      5001
//#define BROADCAST_ADDRESS   "255.255.255.255"
#define BROADCAST_ADDRESS   "127.255.255.255"
//#define BROADCAST_ADDRESS   "10.5.255.255"
//#define BROADCAST_ADDRESS   "10.5.3.255"

#define ENABLE_UNICAST
#define UINCAST_PORT         BROADCAST_PORT
#define UINCAST_ADDRESS      "127.0.0.1"

int main(int argc, char *argv[]) {

    int count = 0;
    int iSocket = 0;
    int iRetVal = 0;
    int broadcast = 1;

    char arrcBuffer[MAX_MSG] = {0};
    struct sockaddr_in servAddr = {0};
    struct sockaddr_in ClientAddr = {0};
    struct sockaddr_in BrdCastAddr = {0};

    #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(0x0101, &wsaData)) {
            perror("WSAStartup");
            return 1;
        }
    #endif

    /* socket creation */
    iSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(iSocket < 0) {
        printf("%d: cannot open socket \n", iSocket);
        exit(1);
    }

    #ifdef BIND_SERVER
        /* bind to server port */
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(SERVER_PORT);

        iRetVal = bind (iSocket, (struct sockaddr *) &servAddr, sizeof(servAddr));
        if(iRetVal < 0) 
        {
            printf("%d: cannot bind port number %d\n", iRetVal, SERVER_PORT);
            exit(1);
        }
    #endif

    #ifdef ENABLE_BROADCAST
        /* enable broadcast */
        if(setsockopt(iSocket, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast)) == -1) 
        {
            perror("setsockopt (SO_BROADCAST)");
            exit(1);
        }

        BrdCastAddr.sin_family = AF_INET;
        BrdCastAddr.sin_addr.s_addr = inet_addr(BROADCAST_ADDRESS);
        BrdCastAddr.sin_port = htons(BROADCAST_PORT);
    #endif

    #ifdef ENABLE_UNICAST
        ClientAddr.sin_family = AF_INET;
        ClientAddr.sin_addr.s_addr = inet_addr(UINCAST_ADDRESS);
        ClientAddr.sin_port = htons(UINCAST_PORT);
    #endif

    while(1) 
    {
        #ifdef ENABLE_UNICAST
            /* copy message */
            sprintf(arrcBuffer, "%d unicast", count);

            /* send message */
            iRetVal = sendto(iSocket, arrcBuffer, strlen(arrcBuffer), 0, (struct sockaddr *) &ClientAddr, sizeof(ClientAddr));
            if(iRetVal < 0) 
            {
                perror("cannot send unicast data");
            }
            else
            {
                printf("sent : %s\n", arrcBuffer);
            }
        #endif

        #ifdef ENABLE_BROADCAST
            sprintf(arrcBuffer, "%d broadcast", count);

            /* send message */
            iRetVal = sendto(iSocket, arrcBuffer, strlen(arrcBuffer), 0, (struct sockaddr *) &BrdCastAddr, sizeof(BrdCastAddr));
            if(iRetVal < 0) 
            {
                perror("cannot send broadcast data");
            }
            else
            {
                printf("sent : %s\n", arrcBuffer);
            }
        #endif

        #ifdef _WIN32
            Sleep(1000); /* milli seconds */
        #else
            sleep(1);
        #endif

        count++;  
    }

    #ifdef _WIN32
        WSACleanup();
    #endif

    return 0;
}
