#pragma once
#include "afxwin.h"


// CMyDlgChat �Ի���

class CMyDlgChat : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDlgChat)

public:
	CMyDlgChat(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDlgChat();

// �Ի�������
	enum { IDD = IDD_DLG_CHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_edtSend;
	CListBox m_lstShow;
};
