#pragma once
#include"Sys.h"
#include"Bullet.h"
#include"BulletOne.h"
#include"BulletTwo.h"
#include"BulletThree.h"
class CCapture
{
public:
	HBITMAP h_BitMap_Up_1;
	HBITMAP h_BitMap_Up_2;
	HBITMAP h_BitMap_Gun_1;
	HBITMAP h_BitMap_Gun_2;
	HBITMAP h_BitMap_Gun_15_plus_left;
	HBITMAP h_BitMap_Gun_15_minus_left;
	HBITMAP h_BitMap_Gun_15_plus_right;
	HBITMAP h_BitMap_Gun_15_minus_right;
	int m_nBulletStyle;
	int m_nGunStyle;
	int m_nBulletCount;
	int m_nCapture_Direction;
public:
	CCapture(void);
	~CCapture(void);
public:
	   int x;
	   int y;
	   void InitCapture(HINSTANCE hIns);
	   void ShowCapture(HDC hMemDC);
	   void SendBullet(list<CBullet*>&m_lstBullet, HINSTANCE hIns);
	   		   void ChangeBullet(list<CBullet*>&m_lstBullet);
};

