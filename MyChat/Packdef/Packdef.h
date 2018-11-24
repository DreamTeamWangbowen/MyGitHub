
#ifndef PACKDEF_H
#define PACKDEF_H


#define DEF_PORT  1234

#define DEF_PACKDEFSIZE  4096
#define DEF_BUFFERSIZE   1024


typedef char PackdefType;

#define _DEF_PROTOCOL_BASE   20
#define _DEF_PROTOCOL_ONLINE_RQ  _DEF_PROTOCOL_BASE + 1
#define _DEF_PROTOCOL_ONLINE_RS  _DEF_PROTOCOL_BASE + 2
#define _DEF_PROTOCOL_OFFLINE_RQ _DEF_PROTOCOL_BASE + 3
#define _DEF_PROTOCOL_DATAINFO_RQ _DEF_PROTOCOL_BASE +4


//消息
#define UM_ONLINEMSG   WM_USER + 1
#define UM_OFFLINEMSG  WM_USER + 2
#define UM_DATAINFOMSG  WM_USER + 3

//网络消息
#define NM_READMSG      WM_USER +100

//上线请求包，回复包 //下线请求包
typedef struct STRU_ONLINE
{
	PackdefType m_ntype; 
	//char         m_szName[MAX_PATH];
}STRU_OFFLINE;

//数据包
struct STRU_DATAINFO
{
	PackdefType m_ntype; 
	char        m_szBuffer[DEF_BUFFERSIZE];
};





#endif