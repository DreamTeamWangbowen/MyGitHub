#pragma once
#include "afxwin.h"


// CMyDlgChat 对话框

class CMyDlgChat : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDlgChat)

public:
	CMyDlgChat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDlgChat();

// 对话框数据
	enum { IDD = IDD_DLG_CHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_edtSend;
	CListBox m_lstShow;
};
