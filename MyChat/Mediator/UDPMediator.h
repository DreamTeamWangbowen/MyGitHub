#ifndef UDPMEDIATOR_H
#define UDPMEDIATOR_H
#include "IMediator.h"

class UDPMediator;
typedef void (UDPMediator::*PFUN)(char *,long );

struct ProtocolMap
{
	PackdefType m_ntype; //协议
	PFUN       m_pfun;   //函数地址
};

class  UDPMediator :public IMediator
{
public:
	UDPMediator();
	virtual ~UDPMediator();
public:
	bool Open();
	void Close();
	bool SendData(long lSendIp, char *szbuf,int nlen);
	void DealData(char *szbuf,long lRecvIp);
public:
   void OnLineRq(char *szbuf,long lRecvIp);
   void OnLineRs(char *szbuf,long lRecvIp);
   void OffLineRq(char *szbuf,long lRecvIp);
   void DataInfoRq(char *szbuf,long lRecvIp);

};




#endif