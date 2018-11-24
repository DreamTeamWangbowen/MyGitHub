
// feiqDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "MyDlgChat.h"
#include <map>
using namespace std;
// CfeiqDlg �Ի���
class CfeiqDlg : public CDialogEx
{
// ����
public:
	CfeiqDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FEIQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	LRESULT OnLineMsg(WPARAM w,LPARAM l );
	LRESULT OffLineMsg(WPARAM w,LPARAM l );
	LRESULT DataInfoMsg(WPARAM w,LPARAM l );
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	CMyDlgChat* GetMyDlg(CString strip);
public:
	CListBox m_lstip;	
    static	HHOOK m_hKeyboard;
	map<CString,CMyDlgChat*> m_mapIpToDlg;
};
