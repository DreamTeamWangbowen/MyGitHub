#ifndef IMEDIATOR_H
#define IMEDIATOR_H
#include "INet.h"

class IMediator
{
public:
	IMediator(){}
	virtual ~IMediator(){}
public:
	virtual bool Open() = 0;
	virtual void Close() = 0;
	virtual bool SendData(long lSendIp, char *szbuf,int nlen) = 0;
	virtual void DealData(char *szbuf,long lRecvIp) = 0;
protected:
	INet *m_pNet;	
};




#endif