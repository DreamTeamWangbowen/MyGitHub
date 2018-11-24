#include "stdafx.h"
#include "UDPNet.h"
UDPNet::UDPNet(IMediator *pMediator)
{
	m_sock = NULL;
	m_hThread = NULL;
	m_bFlagQuit = true;
	m_pMediator = pMediator;
}

UDPNet::~UDPNet()
{}

bool UDPNet::InitNetWork()
{
	//1.选择种类 -- 加载库
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
     
        return false;
    }


    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
      
      
        UnInitNetWork();
        return false;
    }
   
        
	//2.找个人干 --- 创建socket  套接字
	m_sock =  socket(AF_INET ,SOCK_DGRAM ,IPPROTO_UDP);
	if(INVALID_SOCKET  == m_sock)
	{
		 UnInitNetWork();
        return false;
	}
	//将socket 属性改为非阻塞
	 u_long argp = 1;

	ioctlsocket(m_sock,FIONBIO ,&argp);
	//将socket 设置为广播属性
	BOOL opval = TRUE;
	setsockopt(m_sock,SOL_SOCKET,SO_BROADCAST,(const char*)&opval,sizeof(BOOL));
	//3.找个地方--绑定 地址  bind
	sockaddr_in  addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr =INADDR_ANY;
	addr.sin_port = htons(DEF_PORT);
	if(SOCKET_ERROR == bind(m_sock,(const sockaddr*)&addr,sizeof(addr)))
	{
		 UnInitNetWork();
        return false;
	}
	//创建窗口
	if(!CMyWnd::GetMyWnd()->Create(NULL,"MyWnd"))
	{
	    UnInitNetWork();
        return false;
	}
	//注册
	WSAAsyncSelect(m_sock,CMyWnd::GetMyWnd()->m_hWnd,NM_READMSG,FD_READ);


	//创建线程--recvfrom
//	m_hThread =(HANDLE)_beginthreadex(NULL,0,&ThreadProc,this,0,0);
	return true;
}

unsigned _stdcall UDPNet::ThreadProc( void *lpvoid )
{
	UDPNet *pthis = (UDPNet*)lpvoid;
	char szbuf[DEF_PACKDEFSIZE] = {0};
	sockaddr_in addrClient;
	int nSize = sizeof(addrClient);
	while(pthis->m_bFlagQuit)
	{
		if(!pthis->SelectMySocket(pthis->m_sock))
			continue;

		int nRes = recvfrom(pthis->m_sock,szbuf,DEF_PACKDEFSIZE,0,( sockaddr*)&addrClient,&nSize);
		//int nRes = recvfrom(pthis->m_sock1,szbuf,DEF_PACKDEFSIZE,0,( sockaddr*)&addrClient,&nSize);
		if(nRes >0)
		{
			//交给中介者处理
			pthis->m_pMediator->DealData(szbuf,addrClient.sin_addr.S_un.S_addr);

		}
	}

	return 0;
}

void UDPNet::UnInitNetWork()
{
	m_bFlagQuit = false;
	WSACleanup();
	if(m_sock)
	{
		closesocket(m_sock);
		m_sock = NULL;
	}
	if(m_hThread)
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(m_hThread,100))
			TerminateThread(m_hThread,-1);

		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	CMyWnd::DeleteMyWnd();
}

bool UDPNet::SendData(long lSendIp, char *szbuf,int nlen)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = lSendIp;
	addr.sin_port = htons(DEF_PORT);
	if(sendto(m_sock,szbuf,nlen,0,(const sockaddr*)&addr,sizeof(addr))<=0)
		return false;
	return true;
} 

bool UDPNet::SelectMySocket(SOCKET sock)
{
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 100;
	fd_set fdsets;
	FD_ZERO(&fdsets);
	FD_SET(sock,&fdsets);
	select(NULL,&fdsets,NULL,NULL,&tv);

	if(!FD_ISSET(sock,&fdsets))
		return false;



	return true;
}