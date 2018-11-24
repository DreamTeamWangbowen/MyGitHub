#pragma once
#include"Sys.h"///里面含有windows头文件 所以要加
class CLevel
{
public:
	HBITMAP m_One_W;
	HBITMAP m_One_B;
	HBITMAP m_Two_W;
	HBITMAP m_Two_B;
	HBITMAP m_Three_W;
	HBITMAP m_Three_B;
	HBITMAP m_Four_W;
	HBITMAP m_Four_B;
	int x;
	int y;
	size_t m_slevel_up;
public:
	CLevel(void);
	~CLevel(void);
public:
	void InitLevel(HINSTANCE hIns);
	void ShowLevel(HDC hMemDC);
};

