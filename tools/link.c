#include "link.h"
#include <stdlib.h>

link * link_init(int val)
{
    link * head = (link *)malloc(sizeof(link));
    head->val = val;
    head->next = NULL;
    return head;
}

unsigned int link_add_position(link ** head, unsigned int position, int val)
{
    if(NULL == head){
        return LINK_ERR_NULL;
    }
    int i = 0;
    link * temp = (link *)malloc(sizeof(link));
    link * back = *head;
    link * temp_save = NULL;
    temp->val = val;
    temp->next = NULL;
    if(0 == position)
    {
        temp->next = back;
        *head = temp;
        return LINK_ERR_SUCCESSFUL;
    }
    for(i = 0; i < position; i++)
    {
        if(NULL != back){
            temp_save = back;
            back = back->next;
        }else{
            return LINK_ERR_OVER;
        }
    }
    temp_save->next = temp;
    temp->next = back;
    return LINK_ERR_SUCCESSFUL;
}

unsigned int link_print_link(link * head, char * str)
{
    if(NULL == head){
        return LINK_ERR_NULL;
    }
    link * back = head;
    int len = 0;
    while(NULL != back->next){
        len += sprintf(str + len, "%d,", back->val);
        back = back->next;
    }
    sprintf(str + len, "%d\r\n", back->val);
    return LINK_ERR_SUCCESSFUL;
}