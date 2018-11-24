#pragma once
#include "fish.h"
class CGoldenFish :
	public CFish
{
public:
	CGoldenFish(void);
	~CGoldenFish(void);
	public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

