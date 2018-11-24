#include <Spider.h>

int Spider_Response(int webfd , ssl_t * ssl)
{
		char buf[8192];
		int len,fd;
		char * pos;
		char * reshead=NULL;
		bzero(buf,sizeof(buf));
		if(ssl){
				len = SSL_read(ssl->socket,buf,sizeof(buf));
				if((pos = strstr(buf,"\r\n\r\n"))!=NULL)
				{
						reshead = (char *)malloc(pos-buf);
						strncpy(reshead,buf,pos-buf);	
						printf("[5] https Get Response Head Success:\n%s\n",reshead);
				}
				if((fd = open("temp",O_RDWR|O_CREAT,0775))!=-1)
				{
						write(fd,pos+4,len-(pos-buf+4));
						bzero(buf,sizeof(buf));
						while((len = SSL_read(ssl->socket,buf,sizeof(buf)))>0)
						{
								write(fd,buf,len);
								bzero(buf,sizeof(buf));
						}
						printf("[6] Download Success..\n");
				}
		}else{
				len = recv(webfd,buf,sizeof(buf),0);
				if((pos = strstr(buf,"\r\n\r\n"))!=NULL)
				{
						reshead = (char *)malloc(pos-buf);
						strncpy(reshead,buf,pos-buf);	
						printf("[5] http Get Response Head Success:\n%s\n",reshead);
				}
				if((fd = open("temp",O_RDWR|O_CREAT,0775))!=-1)
				{
						write(fd,pos+4,len-(pos-buf+4));
						bzero(buf,sizeof(buf));
						while((len = recv(webfd,buf,sizeof(buf),0))>0)
						{
								write(fd,buf,len);
								bzero(buf,sizeof(buf));
						}
						printf("[6] Download Success..\n");
				}

		}
		return 0;

}
