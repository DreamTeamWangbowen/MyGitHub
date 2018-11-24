#pragma once
#include "fish.h"
class CBigFish :
	public CFish
{
public:
	CBigFish(void);
	~CBigFish(void);
public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

