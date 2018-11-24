// MyDlgChat.cpp : 实现文件
//

#include "stdafx.h"
#include "feiq.h"
#include "MyDlgChat.h"
#include "afxdialogex.h"


// CMyDlgChat 对话框

IMPLEMENT_DYNAMIC(CMyDlgChat, CDialogEx)

CMyDlgChat::CMyDlgChat(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDlgChat::IDD, pParent)
	, m_edtSend(_T(""))
{

}

CMyDlgChat::~CMyDlgChat()
{
}

void CMyDlgChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edtSend);
	DDX_Control(pDX, IDC_LIST1, m_lstShow);
}


BEGIN_MESSAGE_MAP(CMyDlgChat, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDlgChat::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyDlgChat 消息处理程序


void CMyDlgChat::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获得要发送的内容
	UpdateData();
	//获得ip
	CString strip;
	GetWindowText(strip);

	STRU_DATAINFO sd;
	sd.m_ntype = _DEF_PROTOCOL_DATAINFO_RQ;
	memcpy(sd.m_szBuffer,m_edtSend,sizeof(sd.m_szBuffer));
	
	if(theApp.GetMediator()->SendData(inet_addr(strip),(char*)&sd,sizeof(sd)))
	{
		m_lstShow.AddString("I say:");
		m_lstShow.AddString(m_edtSend);
		m_edtSend = "";
		UpdateData(FALSE);
	}
}
