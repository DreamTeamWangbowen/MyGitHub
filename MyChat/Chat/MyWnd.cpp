// MyWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "feiq.h"
#include "MyWnd.h"
#include "Packdef.h"

// CMyWnd

IMPLEMENT_DYNCREATE(CMyWnd, CFrameWnd)
 CMyWnd *CMyWnd::m_pWnd = new CMyWnd;
CMyWnd::CMyWnd()
{

}

CMyWnd::~CMyWnd()
{
}


BEGIN_MESSAGE_MAP(CMyWnd, CFrameWnd)
	ON_MESSAGE(NM_READMSG,&CMyWnd::OnReadMsg)
END_MESSAGE_MAP()


// CMyWnd ��Ϣ�������
LRESULT CMyWnd::OnReadMsg(WPARAM w,LPARAM l)
{
	char szbuf[DEF_PACKDEFSIZE] = {0};
	sockaddr_in addrClient;
	int nSize = sizeof(addrClient);
	

	int nRes = recvfrom(w,szbuf,DEF_PACKDEFSIZE,0,( sockaddr*)&addrClient,&nSize);
	
	if(nRes >0)
	{
		//�����н��ߴ���
		theApp.GetMediator()->DealData(szbuf,addrClient.sin_addr.S_un.S_addr);
	}

	return 0;
}