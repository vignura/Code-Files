// socket headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
// c headers
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MSG             100
#define SERVER_PORT         5555
#define SERVER_ADDR         "127.0.0.1"

int readMessage(char* Msg, int msgSize);
int readLine(char* line, int size);

int main(int argc, char *argv[]) {

    int iRetVal = 0;
    int iSocket = 0;
    int iAddrSize = 0;
    int clientID = 0;
    int iTxMsgSize = 0;

    char arrcTXBuffer[MAX_MSG] = {0};
    char arrcRXBuffer[MAX_MSG] = {0};
    struct sockaddr_in ServAddr = {0};
    struct sockaddr_in ClientAddr = {0};

    if(argc < 2)
    {
        printf("usage: %s <client ID>\n", argv[0]);
        return 0;
    }

    // get the client ID from arguments
    sscanf(argv[1], "%d", &clientID);
    printf("Creating client with Client ID: %d\n", clientID);

    /* socket creation */
    iSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(iSocket < 0) 
    {
        printf("%d: cannot open socket \n", iSocket);
        return 0;
    }

    // set the client address length
    iAddrSize = sizeof(ServAddr);
    // set the server address
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    ServAddr.sin_port = htons(SERVER_PORT);


    while(1)
    {
        memset(arrcTXBuffer, 0, sizeof(arrcTXBuffer));
        memset(arrcRXBuffer, 0, sizeof(arrcRXBuffer));

        // read message from CLI
        // add client ID
        iRetVal = snprintf(arrcTXBuffer, sizeof(arrcTXBuffer), "[Client ID: %d] ", clientID);
        iTxMsgSize = iRetVal;
        iTxMsgSize += readMessage((arrcTXBuffer + iRetVal), sizeof(arrcTXBuffer));

        // send message to server
        iRetVal = sendto(iSocket, arrcTXBuffer, iTxMsgSize, /*flags*/ 0, (struct sockaddr *) &ServAddr, sizeof(ServAddr));
        if(iRetVal < 0) 
        {
            perror("cannot send to server");
        }
        else
        {
            iRetVal =  recvfrom(iSocket, arrcRXBuffer, sizeof(arrcRXBuffer), /*flags*/ 0, (struct sockaddr *) &ServAddr, &iAddrSize);
            if(iRetVal > 0) /* no errors */
            {
                // print response
                printf("%s\n", arrcRXBuffer);
            }
            else
            {
                perror("falied to receive response from server");       
            }
        }
        
    }

    return 0;
}


int readMessage(char* Msg, int msgSize)
{
    int iRetVal = 0;

    if(Msg == NULL)
    {
        return -1;
    }

    memset(Msg, 0, msgSize);
    printf("Enter a message: ");
    iRetVal = readLine(Msg, msgSize);

    return iRetVal;
}


int readLine(char* line, int size)
{
    int count = 0;
    char ch = 0;

    while(count < (size -1))
    {
        ch = getchar();
        if((ch == EOF) || (ch == '\n'))
        {
            break;
        }
        line[count] = ch;
        count++;
    }

    /*fill null character at the end*/
    line[count] = '\0';

    return count;
}

#if 0
void *eventListener()
{
    char arrcRXBuffer[MAX_MSG] = {0};
    struct sockaddr_in ServAddr = {0};
    struct sockaddr_in ClientAddr = {0};

    /* socket creation */
    iSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(iSocket < 0)
    {
        printf("%d: cannot open event listener socket \n", iSocket);
        return ;
    }

    // set the client address length
    iAddrSize = sizeof(ServAddr);
    // set the server address
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    ServAddr.sin_port = htons(1995);

    while (1)
    {
        memset(arrcRXBuffer, 0, sizeof(arrcRXBuffer));
    }
}
#endif
