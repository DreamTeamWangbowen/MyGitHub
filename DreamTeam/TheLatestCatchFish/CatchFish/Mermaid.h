#pragma once
#include "fish.h"
class CMermaid :
	public CFish
{
public:
	CMermaid(void);
	~CMermaid(void);
	public:
	virtual bool IsBulletFish(CBullet* pBullet);
	virtual void InitFish(HINSTANCE hIns); 
	virtual void MoveFish();
	virtual void ShowFish(HDC hMemDC);
};

