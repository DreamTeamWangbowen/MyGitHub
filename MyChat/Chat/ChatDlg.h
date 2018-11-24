
// feiqDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MyDlgChat.h"
#include <map>
using namespace std;
// CfeiqDlg 对话框
class CfeiqDlg : public CDialogEx
{
// 构造
public:
	CfeiqDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FEIQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
