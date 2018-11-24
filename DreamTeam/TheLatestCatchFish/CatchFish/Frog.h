#pragma once
#include "fish.h"
class CFrog :
	public CFish
{
public:
	CFrog(void);
	~CFrog(void);
	public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

