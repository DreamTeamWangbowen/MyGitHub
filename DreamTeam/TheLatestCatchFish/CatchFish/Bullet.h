#pragma once
#include"Sys.h"
class CBullet
{
public:
	HBITMAP m_hBmpBullet_1;
	HBITMAP m_hBmpBullet_2;
	HBITMAP m_hBmpBullet_15_plus_left;
	HBITMAP m_hBmpBullet_15_minus_left;
	HBITMAP m_hBmpBullet_15_plus_right;
	HBITMAP m_hBmpBullet_15_minus_right;
	int x;
	int y;
	int m_Bullet_Style;
	int m_Bullet_Direction;
public:
	CBullet(void);
	virtual~CBullet(void);
public:
	virtual void InitBullet(int X, int Y, HINSTANCE hIns)=0;
	virtual void MoveBullet()=0;
	virtual void ShowBullet(HDC hMemDC)=0;
};

