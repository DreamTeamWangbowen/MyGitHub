#pragma once
#include"sys.h"
#pragma comment(lib, "winmm.lib")  ///声音播放头文件
class CBack
{
public:
	CBack(void);
	~CBack(void);
public:HBITMAP m_hBackOne;
	   HBITMAP m_hBackTwo;
	   HBITMAP m_hBackThree;
	   HBITMAP m_hChangeBack;
	   HBITMAP m_hHeadPicture_W;
	   HBITMAP m_hHeadPicture_B;
	   HBITMAP m_lele_Catch_Fish;
	  unsigned int BACK_ID_COUNT;
	   int x;
	   int y;
	   void InitBack(HINSTANCE hIns);
	   void ShowBack(HDC hMemDC);
	   void ShowMenu(HDC hMemDC);
	   void ShowMusic();
};

