#pragma once
#include "fish.h"
class CPurpleFish :
	public CFish
{
public:
	CPurpleFish(void);
	~CPurpleFish(void);
	public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

