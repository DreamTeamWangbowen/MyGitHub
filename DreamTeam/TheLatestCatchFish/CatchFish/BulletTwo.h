#pragma once
#include "bullet.h"
class CBulletTwo :
	public CBullet
{
public:
	CBulletTwo(void);
	~CBulletTwo(void);
public:
	virtual void InitBullet(int X, int Y, HINSTANCE hIns);
	virtual void MoveBullet();
	virtual void ShowBullet(HDC hMemDC);
};

