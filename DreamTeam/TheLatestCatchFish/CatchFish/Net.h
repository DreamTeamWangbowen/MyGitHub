#pragma once
#include"Sys.h"
class CNet
{
public:
	CNet(void);
	~CNet(void);
public:
	HBITMAP h_bitmap_White;
	HBITMAP h_bitmap_Black;
	int x;
	int y;
	int m_Net_Style;
public:
	void InitNet(int X, int Y, HINSTANCE hIns,int m_Bullet_Style);
	void ShowSingleNet(HDC hMemDC);
};

