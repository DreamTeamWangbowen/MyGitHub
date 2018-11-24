#include <Spider.h>
int Spider_Queue_en(queue_t * p,char * u)
{
        if(Spider_Queue_if_full(p))
                return FALSE;
        else{
                p->url[p->rear]=u;
                p->rear = (p->rear+1)%p->maxsize;
                return TRUE;
        }
}

