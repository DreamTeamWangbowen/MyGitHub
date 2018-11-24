#include <Spider.h>

int main(void)
{
		url_t * u_info;
		int webfd;
		ssl_t * ssl=NULL;
		queue_t  new;
		queue_t  old;
		//const char * tmpurl = "http://img.zcool.cn/community/018a1d57d761f60000012e7ece7fff.png@1280w_1l_2o_100sh.png";
		//char * tmpurl = "https://baike.baidu.com/item/linux/27050?fr=aladdin";
		int page=0;
		char * tmpurl = "http://www.youdict.com/ciku/";
		char * MyURL=(char*)malloc(sizeof(char)*1024);
		bzero(MyURL,sizeof(char)*1024);

		int fd_StoreURL;
		if(-1 == (fd_StoreURL = open("MYURL",O_RDWR|O_CREAT,0664)))
		{
			perror("open errors!\n");
		}
		int size=lseek(fd_StoreURL,0,SEEK_END);//设置光标在末尾
		lseek(fd_StoreURL,0,SEEK_SET);//设置为头
		int readsize=read(fd_StoreURL,MyURL,size);
		printf("size:%d\n",size);
		printf("readsize:%d\n",readsize);
		if(strlen(MyURL)==0)
		{
			printf("MyURL is NULL,start strncpy!\n");
			strncpy(MyURL,tmpurl,strlen(tmpurl));
		}
		else
		{
			printf("MURL is %s!\n",MyURL);	
		}
		
		Spider_Queue_create(&new,100);
		Spider_Queue_create(&old,500);


		while(1)
		{
		Spider_Queue_en(&new,MyURL);
		Spider_Queue_show(&new);
		if((u_info = Spider_Analytic_url(Spider_Queue_de(&new)))!=NULL){
				printf("[1] Analytical URL Success:\nURL:%s\nDOMAIN:%s\nIP:%s\nPORT:%d\nNAME:%s\nTYPES:%d\n",u_info->url,u_info->domain,u_info->ip,u_info->port,u_info->name,u_info->types);
		}else
			{	
				printf("ERROR:Analytical URL Call Failed..\n");
				exit(-1);
			}
		webfd = Spider_Connect_server(u_info);
		

		if(u_info->types){
				Spider_Request(u_info,webfd,ssl);
				Spider_Response(webfd,ssl);
		}else{
				ssl = Spider_Openssl_Create(webfd);
				Spider_Request(u_info,webfd,ssl);
				Spider_Response(webfd,ssl);
		}
		
		map_t * map = Spider_Create_cache("temp");
		char* pNextPage=My_Analytic_html(map);
		page++;//page++
		printf("当前第%d页单词爬取完成！\n",page);
		sleep(5);
		bzero(MyURL,sizeof(char)*1024);
		strncpy(MyURL,tmpurl,strlen(tmpurl));
		strcat(MyURL,pNextPage);
		printf("pNextPage:%s\n",pNextPage);
		lseek(fd_StoreURL,0,SEEK_SET);
		write(fd_StoreURL,MyURL,strlen(MyURL));
		}
		close(fd_StoreURL);
		/*if((LoadData())==1)
		{
			printf("LoadData Finish!\n");
		}*/
		//Spider_Analytic_html(&new,src);
		//Spider_Queue_show(&new);
		return 0;
}
