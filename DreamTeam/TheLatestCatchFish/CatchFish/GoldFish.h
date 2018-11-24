#pragma once
#include "fish.h"
class CGoldFish :
	public CFish
{
public:
	CGoldFish(void);
	~CGoldFish(void);
	public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

