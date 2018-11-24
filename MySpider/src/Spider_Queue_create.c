#include <Spider.h>


int Spider_Queue_create(queue_t * p,int maxsize){
        p->url = (char**)malloc(sizeof(char*)*maxsize);
        if(p->url == NULL){
				printf("Spider Queue Create Error\n");
				return -1;
		}
        p->front=0;
        p->rear=0;
        p->size=0;
        p->maxsize = maxsize;
        return 0;
}

