#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "tool.h"

int sockfd = 0;

int ConnectServer()
{    
    struct sockaddr_in cli_addr;

    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port   = htons(SERVER_PORT);
    cli_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        
    }
    if(0 > connect(sockfd, (struct sockaddr *)&cli_addr, sizeof(cli_addr)))
    {
        
    }    
    return sockfd;
}

void link_tool(int argc, char *argv[])
{
    signalMessage * message = (signalMessage *)malloc(sizeof(signalMessage));
    char szBuf[8192] = {0};
    if(!strcmp(argv[0], "init"))
    {
        message->signal = TOOL_SIGNAL_INITLINK;
        strcpy(message->message[0], argv[1]);
        printf("%s\r\n", message->message[0]);
    }
    else if(!strcmp(argv[0], "add"))
    {
        message->signal = TOOL_SIGNAL_ADDLINKBYPOSITION;
        // argv[1]:position  argv[2]:val
        strcpy(message->message[0], argv[1]);
        strcpy(message->message[1], argv[2]);
    }
    else if(!strcmp(argv[0], "print"))
    {
        message->signal = TOOL_SIGNAL_PRINTLINK;
    }
    send(sockfd, (char *)message, 8192, 0);
    printf("send\r\n");
    recv(sockfd, szBuf, 8192, 0);
    signalMessage * message1 = (signalMessage *)szBuf;
    if(!message1->result){
        printf("Successful: %s\r\n", message1->returnMessage);
    }else{
        printf("Failed: %s\r\n", message1->returnMessage);
    }
}

void printHelp()
{
    printf("./tool_client FUNC ARGV[] ...\r\n");
    printf("FUNC:\r\n");
    printf("\tlink           -  opreation the link table\r\n");
}


void main(int argc, char *argv[])
{
    if(argc <= 1){
        printHelp();
        return;
    }
    
    sockfd = ConnectServer();

    if(!strcmp(argv[1], "link")){
        link_tool(argc - 2, &argv[2]);
    }
}