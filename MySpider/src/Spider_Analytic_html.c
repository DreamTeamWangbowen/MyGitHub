#include <Spider.h>

char* My_Analytic_html(map_t * map)
{
	char * pos1=NULL;
	char * pos2=NULL;
	char * pos3=NULL;
	char * pos4=NULL;
	int fd_write;
	if((fd_write = open("letter",O_RDWR|O_CREAT|O_APPEND,0775))==-1)
	{
		perror("open write errors\n");
		
	}
	char * pos=map->src;
	char tab[]="\t";
	char * temp=NULL;
	while(((pos1 = strstr(pos,"href=\"/w/"))!=NULL) 
		&& ((pos3 = strstr(pos,"<p>"))!=NULL)
		&& ((pos4 = strstr(pos,"</p>"))!=NULL))
	{
			int flag=0;
			while((*pos1) != '>')
			{
				pos1++;	
			}
			pos1++;
			//printf("pos1+4:%c\n",*(pos1+4));//一个空格一个换行。。。。。
			if(*(pos1+4) == '\n')//有换行赋
			{
				pos1+=5;
				flag=1;
			}
			pos2=pos1;
			while((*pos2) != '<' && (!flag))
			{
				pos2++;	
			}
			while((*pos2) != '\n' && flag)//有换行赋
			{
				pos2++;	
			}
			if(flag)
			{
				pos2--;	
			}
			//printf("*(pos2-1)-----%c\n",*(pos2-1));//回车赋前还有个空格赋
			write(fd_write,pos1,pos2-pos1);
			write(fd_write,tab,strlen(tab));
			
	
																				//char b[]="w";w 和\0 字节两个 长度是1
			temp=pos3+4;
			char * preMark=NULL;
			char * behMark=NULL;

			while((preMark=strstr(temp,"."))!=NULL && ((pos4-preMark)>0))
			{
				while((*preMark) != '\n')
				{
					preMark--;
				}
				preMark++;
				
				behMark=preMark;
				while((*behMark) !='\n')
				{
					behMark++;
				}
				write(fd_write,preMark,behMark-preMark);
				temp=behMark;//update
			}
			
			write(fd_write,"\n",1);
			pos=pos4+4;
		
	
	}
	
	//next page
	char * pNextPage=NULL;
	char * NextPage=(char*)malloc(sizeof(char)*1024);
	bzero(NextPage,sizeof(char)*1024);
	if((pNextPage = strstr(pos,"\">下一页"))!=NULL)
	{
		pNextPage-=17;	
		strncpy(NextPage,pNextPage,17);
	}
	close(fd_write);
	munmap(map->src,map->length);		
	return NextPage;
}

int Spider_Analytic_html(queue_t * new,char * src)
{
		char title[1024];
		char descrip[4096];
		char * url;
		//char * jsrc = src;
		regex_t treg,areg,dreg;
		regmatch_t tmatch[2];
		regmatch_t amatch[2];
		regmatch_t dmatch[2];
		regcomp(&treg,"<h1 >\\([^<]\\+\\?\\)</h1>",0);	
		regcomp(&dreg,"<meta name=\"description\" content=\"\\([^\"]\\+\\?\"[^>]\\+\\?\\)>",0);	
		regcomp(&areg,"<a[^>]\\+\\?href=\"\\(/item/[^\"]\\+\\?\\)\"[^>]\\+\\?>[^<]\\+\\?</a>",0);	
		while((regexec(&dreg,src,2,dmatch,0))==0)
		{
				bzero(descrip,sizeof(descrip));
				snprintf(descrip,dmatch[1].rm_eo - dmatch[1].rm_so + 1,"%s",src+dmatch[1].rm_so);
				printf("Description: %s\n",descrip);
				src += dmatch[0].rm_eo;
		}
		while((regexec(&treg,src,2,tmatch,0))==0)
		{
				bzero(title,sizeof(title));
				snprintf(title,tmatch[1].rm_eo - tmatch[1].rm_so + 1,"%s",src+tmatch[1].rm_so);
				printf("Title : %s\n",title);
				src += tmatch[0].rm_eo;
		}

		while((regexec(&areg,src,2,amatch,0))==0)
		{
				url = (char *)malloc(sizeof(char)*1024);
				bzero(url,sizeof(char)*1024);
				strncpy(url,src+amatch[1].rm_so,amatch[1].rm_eo - amatch[1].rm_so);
				if((Spider_Queue_notin(new,url))==FALSE)
						Spider_Queue_en(new,url);
				else
						free(url);
				src += amatch[0].rm_eo;
		}
		regfree(&areg);
		regfree(&treg);
		regfree(&dreg);
		//unlink("temp");
		//munmap();
		return 0;
}
