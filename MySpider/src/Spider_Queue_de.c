#include <Spider.h>

char * Spider_Queue_de(queue_t*p)
{
		char * u;
        if(Spider_Queue_if_empty(p))
                return NULL;
        else{
                u = p->url[p->front];
                p->front = (p->front+1)%p->maxsize;
                return u;
        }
}

