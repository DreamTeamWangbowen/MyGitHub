#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <regex.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/mman.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <mysql/mysql.h>

//http 类型为true    https 类型为false
#define TRUE 1
#define	FALSE 0
#define	WEBPORT 80
#define	HTTPS	443

typedef struct
{
		SSL * socket;
		SSL_CTX * ctx;
}ssl_t;

typedef struct 
{
		char url[2048];
		char domain[256];
		char name[1024];
		char ip[16];
		int types;
		int port;
		int status;
}url_t;

typedef struct queue{
		char ** url;
		int front;             
		int rear;             
		int maxsize;          
		int size;            
}queue_t;

typedef struct retmap{
		char * src;
		int length;
}map_t;

url_t * Spider_Analytic_url(char * url);
ssl_t * Spider_Openssl_Create(int);
int Spider_Connect_server(url_t * u);
int Spider_Request(url_t * ,int  ,ssl_t *);
int Spider_Response(int ,ssl_t *);
map_t* Spider_Create_cache(const char * filename);
int Spider_Analytic_html(queue_t *,char *);
int Spider_Queue_create(queue_t * ,int );
int Spider_Queue_if_full(queue_t *);
int Spider_Queue_if_empty(queue_t *);
int Spider_Queue_en(queue_t * ,char *);
int Spider_Queue_notin(queue_t *,char *);
char * Spider_Queue_de(queue_t *);
int Spider_Download(int filefd);
url_t * Spider_Queue_show(queue_t *);

char * My_Analytic_html(map_t *);
int LoadData();
