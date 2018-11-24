#pragma once
#include "fish.h"
class CBlueWhale :
	public CFish
{
public:
	CBlueWhale(void);
	~CBlueWhale(void);
public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

