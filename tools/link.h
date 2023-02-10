#ifndef _LINK_H_
#define _LINK_H_

#include <stdio.h>

#define LINK_ERR_SUCCESSFUL     0 //successful
#define LINK_ERR_OVER           1 //the position is over than the border
#define LINK_ERR_NULL           3 //the pointer of head is nullpointer


typedef struct Link{
    int val;
    struct Link * next;
}link;

extern link * link_init(int val);
extern unsigned int link_add_position(link ** head, unsigned int position, int val);
extern unsigned int link_print_link(link * head, char * str);

#endif