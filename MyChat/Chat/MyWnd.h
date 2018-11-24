#pragma once


// CMyWnd 框架

class CMyWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMyWnd)
protected:
	CMyWnd();           // 动态创建所使用的受保护的构造函数
	virtual ~CMyWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	static CMyWnd *m_pWnd;
	static CMyWnd* GetMyWnd()
	{
		return m_pWnd;
	}
	static void DeleteMyWnd()
	{
		if(m_pWnd)
		{
			delete m_pWnd;
			m_pWnd = NULL;
		}
	}
public:
	LRESULT OnReadMsg(WPARAM w,LPARAM l);
};


