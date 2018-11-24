#include "stdafx.h"
#include "UDPMediator.h"
#include "UDPNet.h"
#include "feiq.h"
UDPMediator::UDPMediator()
{
	m_pNet = new UDPNet(this);
}

UDPMediator::~UDPMediator()
{
	if(m_pNet)
	{
		delete m_pNet;
		m_pNet = NULL;
	}
}

static const ProtocolMap g_protocolMapEntries[]=
{
	{_DEF_PROTOCOL_ONLINE_RQ,&UDPMediator::OnLineRq},
	{_DEF_PROTOCOL_ONLINE_RS,&UDPMediator::OnLineRs},
	{_DEF_PROTOCOL_OFFLINE_RQ,&UDPMediator::OffLineRq},
	{_DEF_PROTOCOL_DATAINFO_RQ,&UDPMediator::DataInfoRq},
	{0,0}
};
 


bool UDPMediator::Open()
{
	if(!m_pNet->InitNetWork())
		return false;
	

	return true;
}

void UDPMediator::Close()
{
	m_pNet->UnInitNetWork();
}

bool UDPMediator::SendData(long lSendIp, char *szbuf,int nlen)
{
	if(!m_pNet->SendData(lSendIp,szbuf,nlen))
		return false;

	return true;
}

void UDPMediator::DealData(char *szbuf,long lRecvIp)
{
	//处理数据
	//判断这个包的类型
	PackdefType *pType = (PackdefType *)szbuf;
	//遍历协议映射表
	int i = 0;
	while(1)
	{
		if(g_protocolMapEntries[i].m_ntype ==  *pType)
		{
			//调用函数指针
			(this->*g_protocolMapEntries[i].m_pfun)(szbuf,lRecvIp);
			break;
		}
		else if(g_protocolMapEntries[i].m_ntype ==0 &&g_protocolMapEntries[i].m_pfun ==0 )
			break;

		i++;
	}
	

}

void UDPMediator::OnLineRq(char *szbuf,long lRecvIp)
{
	PostMessage(theApp.m_pMainWnd->m_hWnd,UM_ONLINEMSG,0,lRecvIp);
		//2.给好友回复-- 判断是不是自己
	if(INet::GetValidIp() == lRecvIp)
		return;

	STRU_ONLINE so;
	so.m_ntype = _DEF_PROTOCOL_ONLINE_RS;
	m_pNet->SendData(lRecvIp,(char*)&so,sizeof(so));
}

void UDPMediator::OnLineRs(char *szbuf,long lRecvIp)
{
	PostMessage(theApp.m_pMainWnd->m_hWnd,UM_ONLINEMSG,0,lRecvIp);
}

void UDPMediator::OffLineRq(char *szbuf,long lRecvIp)
{
	if(INet::GetValidIp() != lRecvIp)
	{
		PostMessage(theApp.m_pMainWnd->m_hWnd,UM_OFFLINEMSG,0,lRecvIp);
	}
}

void UDPMediator::DataInfoRq(char *szbuf,long lRecvIp)
{
	STRU_DATAINFO *psd = (STRU_DATAINFO *)szbuf;
	SendMessage(theApp.m_pMainWnd->m_hWnd,UM_DATAINFOMSG,(WPARAM)psd->m_szBuffer,lRecvIp);
}