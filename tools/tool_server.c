#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "link.h"
#include "tool.h"

link * head = NULL;
int connfd = 0;

void main()
{
    int sockfd = 0;

    sockfd = Socket_Init();
    if(0 > sockfd)
    {
        printf("exec failed\r\n");
        return;
    }
    Socket_Process(sockfd);
}

int Socket_Init()
{
    int sockfd = 0;    
    struct sockaddr_in ServerAddr = {0};
    
    memset(&ServerAddr, 0, sizeof(ServerAddr));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(0 > sockfd)
    {
        return -1;
    }

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(SERVER_PORT);
    ServerAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    if(0 > bind(sockfd, (struct sockaddr*)&ServerAddr,sizeof(ServerAddr)))
    {        
        return -1;
    }
    if(0 < listen(sockfd,SERVER_MAX_CON))
    {        
        return -1;
    }
    return sockfd;
}

void Socket_Process(int sockfd)
{    
    int iRes = 0;
    char szBuf[8192] = {0};
    pthread_t th_process;

    while(1)
    {
        connfd = accept(sockfd, NULL, NULL);
        if(0 > connfd)
        {
            
        }
        /* connect successful */
        iRes = recv(connfd, szBuf, 8192, 0);
        signalMessage * message = (signalMessage *)szBuf;
        switch(message->signal){
            case TOOL_SIGNAL_INITLINK:
                handle_initLink(message);
                break;
            case TOOL_SIGNAL_ADDLINKBYPOSITION:
                handle_addLinkPosition(message);
                break;
            case TOOL_SIGNAL_PRINTLINK:
                handle_linkPrint(message);
                break;
            default:
                strcpy(message->returnMessage, "inited\r\n");
                message->result = TOOL_RESULT_FAIL;
                send(connfd, (char *)message, 8192, 0);
                break;
        }
    }
}

void handle_initLink(signalMessage * message)
{
    int initVal = atoi(message->message[0]);
    if(NULL != head){
        strcpy(message->returnMessage, "inited\r\n");
        message->result = TOOL_RESULT_FAIL;
        send(connfd, (char *)message, 8192, 0);
        return;
    }
    head = link_init(initVal);
    if(NULL == head){
        strcpy(message->returnMessage, "init error\r\n");
        message->result = TOOL_RESULT_FAIL;
        send(connfd, (char *)message, 8192, 0);
        return;
    }
    strcpy(message->returnMessage, "init successful\r\n");
    message->result = TOOL_RESULT_SUCCESSFUL;
    send(connfd, (char *)message, 8192, 0);
    return;
}

void handle_addLinkPosition(signalMessage * message)
{
    int position = atoi(message->message[0]);
    int val = atoi(message->message[1]);
    int res = link_add_position(&head, position, val);
    if(!res){        
        strcpy(message->returnMessage, "add successful\r\n");
        message->result = TOOL_RESULT_SUCCESSFUL;
        send(connfd, (char *)message, 8192, 0);
        return;
    }
    strcpy(message->returnMessage, "add error\r\n");
    message->result = TOOL_RESULT_FAIL;
    send(connfd, (char *)message, 8192, 0);
    return;    
}

void handle_linkPrint(signalMessage * message)
{
    link_print_link(head, message->returnMessage);
    message->result = TOOL_RESULT_SUCCESSFUL;
    send(connfd, (char *)message, 8192, 0);
    return;
}
