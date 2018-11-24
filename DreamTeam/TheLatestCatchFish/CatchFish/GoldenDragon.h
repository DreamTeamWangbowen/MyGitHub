#pragma once
#include "fish.h"
class CGoldenDragon :
	public CFish
{
public:
	CGoldenDragon(void);
	~CGoldenDragon(void);
	public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

