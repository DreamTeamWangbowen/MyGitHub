#include <Spider.h>
int Spider_Queue_if_empty(queue_t *p){
        if(p->front == p->rear)
                return TRUE;
        else
                return FALSE;
}


