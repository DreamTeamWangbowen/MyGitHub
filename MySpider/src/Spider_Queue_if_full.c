#include <Spider.h>
int Spider_Queue_if_full(queue_t *p){
        if(p->front == (p->rear+1) % p->maxsize)
                return TRUE;
        else
                return FALSE;
}

