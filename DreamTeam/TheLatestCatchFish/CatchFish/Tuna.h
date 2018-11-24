#pragma once
#include "fish.h"
class CTuna :
	public CFish
{
public:
	CTuna(void);
	~CTuna(void);
	public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

