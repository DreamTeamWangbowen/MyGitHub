
// feiq.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
#include "UDPMediator.h"
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CfeiqApp:
// �йش����ʵ�֣������ feiq.cpp
//

class CfeiqApp : public CWinApp
{
public:
	CfeiqApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
private:
	IMediator *m_pUDPMediator;
public:
	virtual int ExitInstance();
	IMediator* GetMediator()
	{
		return m_pUDPMediator;
	}
};

extern CfeiqApp theApp;