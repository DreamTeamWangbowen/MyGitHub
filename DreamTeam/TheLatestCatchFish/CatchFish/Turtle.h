#pragma once
#include "fish.h"
class CTurtle :
	public CFish
{
public:
	CTurtle(void);
	~CTurtle(void);
	public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

