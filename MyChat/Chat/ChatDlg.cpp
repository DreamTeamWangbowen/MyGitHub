
// feiqDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "feiq.h"
#include "feiqDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
HHOOK CfeiqDlg::m_hKeyboard = NULL;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CfeiqDlg �Ի���



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


// CfeiqDlg ��Ϣ�������
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
	//��ָ���˵����촰��
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

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if(!theApp.GetMediator()->Open())
		return FALSE;

	STRU_ONLINE so;
	so.m_ntype = (PackdefType)_DEF_PROTOCOL_ONLINE_RQ;
	
	theApp.GetMediator()->SendData(INADDR_BROADCAST,(char*)&so,sizeof(so));
	
	//��װ����--�ֲ�����
	m_hKeyboard = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,NULL,GetCurrentThreadId());
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CfeiqDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CfeiqDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CfeiqDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CfeiqDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	//if(pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
	//{
	//	return TRUE;
	//}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CfeiqDlg::OnLbnDblclkList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���ѡ�����ip 
	int nindex = m_lstip.GetCurSel();
	if(-1 == nindex)return;
	CString str;
	m_lstip.GetText(nindex,str);
	//�ж��Ƿ�ӳ���
	GetMyDlg(str);
}
CMyDlgChat* CfeiqDlg::GetMyDlg(CString strip)
{
	CMyDlgChat *pdlg = m_mapIpToDlg[strip];

	if(!pdlg)
	{  
		//�����´���  
		pdlg = new CMyDlgChat;
		pdlg->Create(IDD_DLG_CHAT);
		pdlg->SetWindowText(strip);
		m_mapIpToDlg[strip] = pdlg;
	}
	pdlg->ShowWindow(SW_SHOW);
	pdlg->SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	return pdlg;
}