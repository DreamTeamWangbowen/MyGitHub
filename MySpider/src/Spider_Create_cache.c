#include <Spider.h>



map_t * Spider_Create_cache(const char * name)
{
		int fd,size;
		char * p = NULL;
		map_t * retmap=(map_t * )malloc(sizeof(map_t));
		if((fd = open(name,O_RDWR|O_APPEND,0664))==-1)//O_RDWR  du xie da kai
				return retmap;
		size = lseek(fd,0,SEEK_END);
		if(NULL == (p = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0)))
		{
			perror("mmap error\n");
			exit(-1);
		}
		retmap->src=p;
		retmap->length=size;
		close(fd);
		return retmap;
}
