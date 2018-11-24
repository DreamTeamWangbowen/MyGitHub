#include <Spider.h>

int  Spider_Queue_notin(queue_t *p,char * url)
{
		int i = p->front;
		if(Spider_Queue_if_empty(p)){
				printf("The Queue is Empty\n");
				return FALSE;
		}
		while(i!= p->rear){
				if((strcmp(p->url[i],url))==0){
						printf("去除重复\n");
						return TRUE;
				}
				i++;
		}
		return 0;
}
