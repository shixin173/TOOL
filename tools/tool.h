#ifndef _TOOL_H_
#define _TOOL_H_

#include <stdio.h>

typedef struct SiganlMessage{
    unsigned int signal;
    char message[20][128];
    char returnMessage[1024];
    unsigned int result;
}signalMessage;

#define SERVER_PORT     14000
#define SERVER_MAX_CON  5
#define SERVER_IP       "127.0.0.1"
#define MAX_LOG_SIZE    4096

/* tool result define */
#define TOOL_RESULT_SUCCESSFUL                          0x00000
#define TOOL_RESULT_FAIL                                0x00001

/* signal define */
#define TOOL_SIGNAL_INITLINK                            0x10000
#define TOOL_SIGNAL_ADDLINKBYPOSITION                   0x10001
#define TOOL_SIGNAL_PRINTLINK                           0x10002


int  Socket_Init();
void Socket_Process(int sockfd);
void handle_initLink(signalMessage * message);
void handle_addLinkPosition(signalMessage * message);
void handle_linkPrint(signalMessage * message);

#endif