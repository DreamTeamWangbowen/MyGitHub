#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#define DEFAULT_TIME 10			/*timeout 10s*/	
#define MIN_WAIT_TASK_NUM 10	/*任务数*/
#define	DEFAULT_THREAD_VARY 10  /*创建与销毁*/
#define true  1
#define	false 0
#define	BUFLEN		1500
#define	PORT		8000
#define	LISTEN		128
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
/*任务队列*/
typedef	struct
{
		int i;
		int listenfd;
}thread_arg;
typedef struct
{
		void*(*function)(void*);		
		void*arg;					
}threadpool_task_t;
/*线程池*/
typedef struct threadpool_t
{
		pthread_mutex_t lock;			/*锁TP_T结构*/           
		pthread_mutex_t thread_counter; /*锁忙状态线程*/    
		pthread_cond_t queue_not_full;	/*生产者锁，队列已满->阻塞，队列不满添加任务*/	
		pthread_cond_t queue_not_empty; /*消费者锁，队列为空->阻塞,队列不为空拿任务执行*/
		pthread_t * threads;            /*线程tid数组*/
		pthread_t adjust_tid;           /*线程池管理线程tid*/
		threadpool_task_t * task_queue; /*任务队列*/ 
		int min_thr_num;                /*线程池最小线程数*/
		int max_thr_num;                /*线程池最大线程数*/
		int live_thr_num;               /*存活线程数*/
		int busy_thr_num;               /*忙的线程数量*/
		int wait_exit_thr_num;          /*即将销毁的线程数*/
		int queue_front;                /*标记任务队列头*/
		int queue_rear;					/*标记任务队列尾*/
		int queue_size;                 /*任务队列中任务数*/
		int queue_max_size;             /*任务队列限制值*/
		int shutdown;                   /*线程池开关，false线程池工作，true销毁线程池*/
}TP_T;
int serverfd;
void *threadpool_thread(void *threadpool); 
void *adjust_thread(void *threadpool);
int is_thread_alive(pthread_t tid);
int threadpool_free(TP_T *pool);


//创建线程池
TP_T *threadpool_create(int min_thr_num,int max_thr_num,int queue_max_size)
{		
		int i;
		TP_T *pool = NULL;
		do{
				/*申请线程池空间*/
				if((pool = (TP_T *)malloc(sizeof(TP_T))) == NULL)
				{
						printf("malloc threadpool error\n");	
						break;
				}				
				/*线程池结构初始化*/
				pool->min_thr_num = min_thr_num; //最小任务数，参数传入
				pool->max_thr_num = max_thr_num; //最大任务数，参数传入
				pool->busy_thr_num = 0;			 //忙线程个数，初始0
				pool->live_thr_num = min_thr_num;//存活线程数，以创建线程池初始线程参数为准
				pool->queue_size = 0;            //任务队列数，初始0
				pool->queue_max_size = queue_max_size;//任务队列最大任数，参数传入
				pool->queue_front = 0;           //环形任务队列头索引
				pool->shutdown = false;			 //线程池状态false(线程池开启)
				pool->threads = (pthread_t *)malloc(sizeof(pthread_t)*max_thr_num);//线程tid数组
				if(pool->threads == NULL)
				{
						printf("malloc threads error\n");
						break;
				}
				memset(pool->threads,0,sizeof(pool->threads));//线程数组初始化
				pool->task_queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t)*queue_max_size);//申请任务队列空间
				if(pool->task_queue == NULL)
				{
						printf("malloc task_queue error\n");
						break;
				}
				/*初始化锁or环境变量*/
				if(pthread_mutex_init(&(pool->lock),NULL) != 0
								|| pthread_mutex_init(&(pool->thread_counter),NULL) != 0
								|| pthread_cond_init(&(pool->queue_not_empty),NULL) != 0
								|| pthread_cond_init(&(pool->queue_not_full),NULL) != 0)
				{
						printf("init lock or cond error\n");
						break;
				}
				/*根据min_thr_num 创建线程*/
				for(int i=0;i<min_thr_num;i++)
				{
						pthread_create(&(pool->threads[i]),NULL,threadpool_thread,(void *)pool);
				}
				pthread_create(&(pool->adjust_tid),NULL,adjust_thread,(void *)pool);
				/*成功返回线程池首地址*/
				return pool;

		}while(0);
		/*失败返回NULL*/
		threadpool_free(pool);
		return NULL;
}
/*添加任务*/
int threadpool_add(TP_T *pool,void *(*function)(void *arg),void *arg)
{

		pthread_mutex_lock(&(pool->lock));
		/*如果任务队列已满为真 & 线程池状态取反为真(当前false)*/
		while((pool->queue_size == pool->queue_max_size) && (!pool->shutdown))
		{
				/*生产者阻塞，等待消费者拿取任务，释放队列，继续工作*/
				pthread_cond_wait(&(pool->queue_not_full),&(pool->lock));
		}
		/*线程池开关为true,解锁*/
		if(pool->shutdown)
		{
				pthread_mutex_unlock(&(pool->lock));
		}
		/*如果任务队列被占用，释放占用，初始化*/
		if(pool->task_queue[pool->queue_rear].arg != NULL)
		{
				free(pool->task_queue[pool->queue_rear].arg);
				pool->task_queue[pool->queue_rear].arg = NULL;
		}
		/*任务队列添加一个任务*/
		pool->task_queue[pool->queue_rear].function = function;
		pool->task_queue[pool->queue_rear].arg = arg;
		/*环形队列计算*/
		pool->queue_rear = (pool->queue_rear + 1 )%pool->queue_max_size;
		pool->queue_size++;
		/*添加至少一个任务后，通知任意一个消费者，使其唤醒消费任务*/
		pthread_cond_signal(&(pool->queue_not_empty));
		pthread_mutex_unlock(&(pool->lock));
		return 0;
}

/*线程任务*/
void *threadpool_thread(void *threadpool)
{
		TP_T *pool = (TP_T *)threadpool;
		threadpool_task_t task;

		while(true)
		{
				pthread_mutex_lock(&(pool->lock));
				/*任务队列任务数==0为真 & 线程池状态取反为真*/
				while((pool->queue_size == 0) && (!pool->shutdown))
				{
						printf("服务器(0x%x)等待任务.\n",(unsigned int)pthread_self());
						/*当前任务队列为空，消费者阻塞，等待生产者生产至少一个任务，唤醒执行*/
						pthread_cond_wait(&(pool->queue_not_empty),&(pool->lock));
						if(pool->wait_exit_thr_num > 0)
						{
								pool->wait_exit_thr_num--;
								if(pool->live_thr_num > pool->min_thr_num)
								{ 
										printf("闲置线程回收:0x%x\n",(unsigned int)pthread_self());
										pool->live_thr_num--;
										pthread_mutex_unlock(&(pool->lock));
										pthread_exit(NULL);
								}
						}
				}		
				if(pool->shutdown)
				{
						pthread_mutex_unlock(&(pool->lock));
						printf("thread 0x%x is exit\n",(unsigned int)pthread_self());
						pthread_exit(NULL);
				}
				/*消费者被唤醒，拿取队列中的任务执行*/
				task.function = pool->task_queue[pool->queue_front].function;
				task.arg = pool->task_queue[pool->queue_front].arg;
				/*任务队列计算*/
				pool->queue_front = (pool->queue_front + 1)%pool->queue_max_size;
				pool->queue_size--;
				/*消费者拿取任务后，通知生产者可以继续生产任务*/
				pthread_cond_broadcast(&(pool->queue_not_full));
				pthread_mutex_unlock(&(pool->lock));
				/*线程开始执行任务，当前忙线程数+1*/
				printf("服务器(0x%x)已就绪.\n",(unsigned int)pthread_self());
				pthread_mutex_lock(&(pool->thread_counter));
				pool->busy_thr_num++;
				pthread_mutex_unlock(&(pool->thread_counter));
				(*(task.function))(task.arg);
				printf("服务器(0x%x)工作结束.\n",(unsigned int)pthread_self());
				pthread_mutex_lock(&(pool->thread_counter));
				/*任务执行完，忙状态数-1*/
				pool->busy_thr_num--;
				pthread_mutex_unlock(&(pool->thread_counter));
		}
		pthread_exit(NULL);
		return (NULL);
}
/*线程池管理*/
void *adjust_thread(void *threadpool)
{
		int i;
		TP_T *pool = (TP_T *)threadpool;
		while(!pool->shutdown)
		{
				/*等待超时，每10s扫描线程池*/
				sleep(DEFAULT_TIME);				
				pthread_mutex_lock(&(pool->lock));
				int queue_size = pool->queue_size;	
				int live_thr_num = pool->live_thr_num; 	
				pthread_mutex_unlock(&(pool->lock));

				pthread_mutex_lock(&(pool->thread_counter));
				int busy_thr_num = pool->busy_thr_num;
				pthread_mutex_unlock(&(pool->thread_counter));
				/*线程池扩展，当任务数>=当前线程数为真 & 存活线程数 < 线程池最大数,那么创建新线程*/
				if(queue_size >= MIN_WAIT_TASK_NUM && live_thr_num < pool->max_thr_num)
				{
						pthread_mutex_lock(&(pool->lock));
						int add = 0;
						printf("检测任务过多，创建新工作线程\n");
						for(i = 0;i<pool->max_thr_num && add < DEFAULT_THREAD_VARY &&
										pool->live_thr_num < pool->max_thr_num;i++)
						{
								if(pool->threads[i] == 0 || !is_thread_alive(pool->threads[i]))
								{
										pthread_create(&(pool->threads[i]),NULL,threadpool_thread,(void *)pool);
										add++;
										pool->live_thr_num++;
								}
						}
						pthread_mutex_unlock(&(pool->lock));
				}
				/*如果忙线程*2还是<当前存活线程,那么释放一部分线程*/
				if((busy_thr_num * 2) < live_thr_num
								&& live_thr_num > pool->min_thr_num)
				{
						pthread_mutex_lock(&(pool->lock));
						pool->wait_exit_thr_num = DEFAULT_THREAD_VARY;
						pthread_mutex_unlock(&(pool->lock));
						for(i=0;i<DEFAULT_THREAD_VARY;i++)
						{
								pthread_cond_signal(&(pool->queue_not_empty));
						}
				}
		}
}
/*线程池销毁,线程池开关为true*/
int threadpool_destroy(TP_T *pool)
{
		int i;
		if(pool == NULL)
				return -1;

		pool->shutdown = true;
		pthread_join(pool->adjust_tid,NULL);
		pthread_cond_broadcast(&(pool->queue_not_empty));
		for(i=0; i<pool->min_thr_num;i++)
		{
				pthread_join(pool->threads[i],NULL);
		}
		threadpool_free(pool);
		return 0;
}
/*线程池资源回收*/
int threadpool_free(TP_T *pool)
{
		if(pool == NULL)
				return -1;

		if(pool->task_queue)
				free(pool->task_queue);

		if(pool->threads)
		{
				free(pool->threads);
				pthread_mutex_lock(&(pool->lock));
				pthread_mutex_destroy(&(pool->lock));
				pthread_mutex_lock(&(pool->thread_counter));
				pthread_mutex_destroy(&(pool->thread_counter));
				pthread_cond_destroy(&(pool->queue_not_empty));
				pthread_cond_destroy(&(pool->queue_not_full));
		}
		free(pool);
		pool = NULL;
		return 0;
}
/*获取存活线程数*/
int threadpool_all_threadnum(TP_T *pool)
{
		int all_threadnum = -1;
		pthread_mutex_lock(&(pool->lock));
		all_threadnum = pool->live_thr_num;
		pthread_mutex_unlock(&(pool->lock));
		return all_threadnum;
}
/*获取忙线程数*/
int threadpool_busy_threadnum(TP_T *pool)
{
		int busy_threadnum = -1;
		pthread_mutex_lock(&(pool->thread_counter));
		busy_threadnum = pool->busy_thr_num;
		pthread_mutex_unlock(&(pool->thread_counter));
		return busy_threadnum;
}
/*信号判断线程是否存活(kill函数中，signo==0,则测试线程)*/
int is_thread_alive(pthread_t tid)
{
		int kill_rc = pthread_kill(tid,0);
		if(kill_rc == ESRCH)
				return false;

		return true;
}
/*错误处理*/
void err_str(char* str,int err_no)
{
		perror(str);
		exit(err_no);
}
/*线程工作,每个线程accept,小写转大写用户请求*/
void *process(void *arg)
{
		thread_arg ts = *(thread_arg*)arg;
		struct sockaddr_in clientaddr;
		int clientfd,sock_len,len;
		char buf[BUFLEN];
		char ipstr[16];
		pthread_mutex_lock(&lock);
		sock_len = sizeof(clientaddr);
		printf("**服务器(0x%x),Accepting...\n",(unsigned int)pthread_self());
		clientfd = accept(ts.listenfd,(struct sockaddr*)&clientaddr,&sock_len);
		pthread_mutex_unlock(&lock);
		printf("**服务器(0x%x),客户端(IP:%s\tPORT:%d)\n",(unsigned int)pthread_self(),inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ipstr,sizeof(ipstr)),ntohs(clientaddr.sin_port));
		while((len = read(clientfd,buf,sizeof(buf))))
		{
				if(len == -1) err_str("read client error",-3);
				else{
						int i=0;
						while(i<len){
								buf[i] = toupper(buf[i]);
								i++;
						}
						write(clientfd,buf,len);
				}

		}
		close(clientfd);
		printf("服务器(0x%x),终止\n",(unsigned int)pthread_self());
		return NULL;
}
/*接口函数*/
int main(void)
{
		struct sockaddr_in serveraddr;
		int reval,serverfd;
		thread_arg t_arg;
		serverfd = socket(AF_INET,SOCK_STREAM,0);
		if(serverfd == -1) err_str("create socket error",-1);
		bzero(&serveraddr,sizeof(serveraddr));
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
		serveraddr.sin_port = htons(PORT);
		reval = bind(serverfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
		if(reval == -1) err_str("bind error",-2);
		reval = listen(serverfd,LISTEN);
		if(reval == -1) err_str("listen error",-3);
		TP_T *thp = threadpool_create(10,4500,50);
		printf("pool inited\n");
		t_arg.listenfd = serverfd;
		for(int i=0;i<20;i++)
		{
				threadpool_add(thp,process,(void *)&t_arg);
		}
		while(1);
		threadpool_destroy(thp);
}
