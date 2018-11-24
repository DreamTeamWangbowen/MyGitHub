#include <Spider.h>

url_t * Spider_Queue_show(queue_t *p){
		int i = p->front;
		if(Spider_Queue_if_empty(p)){
				printf("The Queue is Empty\n");
				return NULL;
		}
		printf("SPIDER URL QUEUE START:\n");
		while(i!= p->rear){
				printf("URL:%s\n",p->url[i]);
				i++;
		}
		printf("PRINT END\n");
		return NULL;
}
