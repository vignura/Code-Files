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

int processRequest(char* request, int requestSize, char* response, int* responseSize);

int main(int argc, char *argv[]) {

    int count = 0;
    int iSocket = 0;
    int iRetVal = 0;
    int broadcast = 1;

    char arrcRXBuffer[MAX_MSG] = {0};
    char arrcTXBuffer[MAX_MSG] = {0};
    int iTxMsgSize = 0;
    struct sockaddr_in servAddr = {0};
    struct sockaddr_in ClientAddr = {0};
    int ClientAddrSize = 0;
    struct sockaddr_in BrdCastAddr = {0};

    /* socket creation */
    iSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(iSocket < 0) {
        printf("%d: cannot open socket \n", iSocket);
        exit(1);
    }

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
   
   	printf("Unicast Server running on port %d\n", SERVER_PORT);

   	// set the client address size 
   	ClientAddrSize = sizeof(ClientAddr);

    while(1) 
    {
    	memset(arrcTXBuffer, 0, sizeof(arrcTXBuffer));
        memset(arrcRXBuffer, 0, sizeof(arrcRXBuffer));	

    	/* listen for incoming requests */
		iRetVal =  recvfrom(iSocket, arrcRXBuffer, sizeof(arrcRXBuffer), /*flags*/ 0, (struct sockaddr *) &ClientAddr, &ClientAddrSize);
		if(iRetVal > 0) /* no errors */
		{
			/* process request */
			iTxMsgSize = sizeof(arrcTXBuffer);
			iRetVal = processRequest(arrcRXBuffer, iRetVal /*rx msg size*/, arrcTXBuffer, &iTxMsgSize);
			if(iRetVal == 0)
			{
				/* send message */
		        iRetVal = sendto(iSocket, arrcTXBuffer, iTxMsgSize, /*flags*/ 0, (struct sockaddr *) &ClientAddr, sizeof(ClientAddr));
		        if(iRetVal < 0) 
		        {
		            perror("cannot send unicast data");
		        }
		        else
		        {
		            printf("sent : %s\n", arrcTXBuffer);
		        }
			}
			else
			{
				printf("Error [%d]: failed to process request ", iRetVal);
			}	
		}
    }

    return 0;
}


int processRequest(char* request, int requestSize, char* response, int* responseSize)
{
	int iRetVal = 0;
	int size = 0;

	if((request == NULL) || (response == NULL) || (responseSize == NULL))
	{
		printf("Error: Null pointer\n");
		return -1;
	}

	printf("Processing Request: %s\n", request);
	size = snprintf(response, *responseSize, "server: success [%s]", request);
	*responseSize = size;

	return iRetVal;
}