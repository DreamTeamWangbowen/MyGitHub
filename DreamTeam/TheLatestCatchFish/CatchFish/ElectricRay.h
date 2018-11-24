#pragma once
#include "fish.h"
class CElectricRay :
	public CFish
{
public:
	CElectricRay(void);
	~CElectricRay(void);
	public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

