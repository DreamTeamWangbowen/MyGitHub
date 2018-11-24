#pragma once
#include"Sys.h"
#include"Bullet.h"
#include"capture.h"
class CFish
{
public:
	CFish(void);
	virtual~CFish(void);
public:
	public:
	HBITMAP m_hBmpFish_White;
	HBITMAP m_hBmpFish_Black;
	int Score_Style;
	int m_nBlood;
	int x;
	int y;
public:
	bool IsDead()
	{
		if(0==m_nBlood)
		return true;
		return false;
	}
	virtual bool IsBulletFish(CBullet* pBullet)=0;
	virtual void InitFish(HINSTANCE hIns)=0; 
	virtual void MoveFish()=0;
	virtual void ShowFish(HDC hMemDC)=0;
	void DownBlood()
	{
		--m_nBlood;
	}
};

