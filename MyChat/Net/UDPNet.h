#ifndef UDPNET_H
#define UDPNET_H
#include "INet.h"
#include "IMediator.h"
#include "MyWnd.h"
class UDPNet:public INet
{
public:
	UDPNet(IMediator *pMediator);
	virtual ~UDPNet();
public:
	bool InitNetWork();
	void UnInitNetWork();
	bool SendData(long lSendIp, char *szbuf,int nlen);
public:
	static unsigned _stdcall ThreadProc( void * );
public:
	bool SelectMySocket(SOCKET sock);
private:
	SOCKET  m_sock;
	HANDLE  m_hThread;
	bool    m_bFlagQuit;
	IMediator *m_pMediator;
	

};





#endif