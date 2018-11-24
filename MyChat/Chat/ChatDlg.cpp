
// feiqDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "feiq.h"
#include "feiqDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
HHOOK CfeiqDlg::m_hKeyboard = NULL;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CfeiqDlg 对话框



CfeiqDlg::CfeiqDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CfeiqDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfeiqDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstip);
}

BEGIN_MESSAGE_MAP(CfeiqDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(UM_ONLINEMSG,&CfeiqDlg::OnLineMsg)
	ON_MESSAGE(UM_OFFLINEMSG,&CfeiqDlg::OffLineMsg)
	ON_MESSAGE(UM_DATAINFOMSG,&CfeiqDlg::DataInfoMsg)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_LBN_DBLCLK(IDC_LIST1, &CfeiqDlg::OnLbnDblclkList1)
END_MESSAGE_MAP()


// CfeiqDlg 消息处理程序
LRESULT CfeiqDlg::OnLineMsg(WPARAM w,LPARAM l )
{
	
	in_addr addr;
	addr.S_un.S_addr = l;
	char *szip = inet_ntoa(addr);
	//MultiByteToWideChar
	m_lstip.AddString(szip);
	return 0;
}

LRESULT CfeiqDlg::OffLineMsg(WPARAM w,LPARAM l )
{
	in_addr addr;
	addr.S_un.S_addr = l;
	char *szip = inet_ntoa(addr);
	CString strip;
	for(int i =0; i <m_lstip.GetCount();i++)
	{
		m_lstip.GetText(i,strip);
		if(strip == szip)
		{
			m_lstip.DeleteString(i);
			break;
		}
	}
	return 0;
}

LRESULT CfeiqDlg::DataInfoMsg(WPARAM w,LPARAM l )
{
	char *szbuf = (char*)w;
	//找指定人的聊天窗口
	in_addr addr;
	addr.S_un.S_addr = l;
	char *szip = inet_ntoa(addr);
	CMyDlgChat *pDlg = GetMyDlg(szip);
	CString strip = szip;
	strip += ":";
	pDlg->m_lstShow.AddString(strip);
	pDlg->m_lstShow.AddString(szbuf);
	return 0;
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam,LPARAM lParam)
{
	if(wParam == VK_RETURN )
	{
		return TRUE;
	}
	return CallNextHookEx(CfeiqDlg::m_hKeyboard,code,wParam,lParam);
}



BOOL CfeiqDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if(!theApp.GetMediator()->Open())
		return FALSE;

	STRU_ONLINE so;
	so.m_ntype = (PackdefType)_DEF_PROTOCOL_ONLINE_RQ;
	
	theApp.GetMediator()->SendData(INADDR_BROADCAST,(char*)&so,sizeof(so));
	
	//安装钩子--局部钩子
	m_hKeyboard = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,NULL,GetCurrentThreadId());
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CfeiqDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CfeiqDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CfeiqDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CfeiqDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if(m_hKeyboard)
	{
	
		UnhookWindowsHookEx(m_hKeyboard);
		m_hKeyboard = NULL;
	}

	STRU_OFFLINE so;
	so.m_ntype = _DEF_PROTOCOL_OFFLINE_RQ;

	theApp.GetMediator()->SendData(INADDR_BROADCAST,(char*)&so,sizeof(so));

	auto ite = m_mapIpToDlg.begin();
	while(ite != m_mapIpToDlg.end())
	{
		if(ite->second)
		{
			delete ite->second;
			ite->second = NULL;
		}
		ite++;
	}
}


void CfeiqDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CfeiqDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
	//{
	//	return TRUE;
	//}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CfeiqDlg::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	//获得选中项的ip 
	int nindex = m_lstip.GetCurSel();
	if(-1 == nindex)return;
	CString str;
	m_lstip.GetText(nindex,str);
	//判断是否映射过
	GetMyDlg(str);
}
CMyDlgChat* CfeiqDlg::GetMyDlg(CString strip)
{
	CMyDlgChat *pdlg = m_mapIpToDlg[strip];

	if(!pdlg)
	{  
		//创建新窗口  
		pdlg = new CMyDlgChat;
		pdlg->Create(IDD_DLG_CHAT);
		pdlg->SetWindowText(strip);
		m_mapIpToDlg[strip] = pdlg;
	}
	pdlg->ShowWindow(SW_SHOW);
	pdlg->SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	return pdlg;
}