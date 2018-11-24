#pragma once
#include"Sys.h"
class CGoldCoin
{
public:
	HBITMAP hBitmap_White;
	HBITMAP hBitmap_Black;
	int x;
	int y;
	int GoldCoin_Style;
public:
	CGoldCoin(void);
	~CGoldCoin(void);
public:
	void InitCGoldCoin(HINSTANCE m_hIns,int Position_X,int Position_Y,int GoldCoinStyle);
	void ShowGoldCoin(HDC hMemDC);
};

