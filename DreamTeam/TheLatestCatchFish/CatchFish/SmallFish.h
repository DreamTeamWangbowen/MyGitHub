#pragma once
#include "fish.h"
class CSmallFish :
	public CFish
{
public:
	CSmallFish(void);
	~CSmallFish(void);
	public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

