
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


//��Ϣ
#define UM_ONLINEMSG   WM_USER + 1
#define UM_OFFLINEMSG  WM_USER + 2
#define UM_DATAINFOMSG  WM_USER + 3

//������Ϣ
#define NM_READMSG      WM_USER +100

//������������ظ��� //���������
typedef struct STRU_ONLINE
{
	PackdefType m_ntype; 
	//char         m_szName[MAX_PATH];
}STRU_OFFLINE;

//���ݰ�
struct STRU_DATAINFO
{
	PackdefType m_ntype; 
	char        m_szBuffer[DEF_BUFFERSIZE];
};





#endif