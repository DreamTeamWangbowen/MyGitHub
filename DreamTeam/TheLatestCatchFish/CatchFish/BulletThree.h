#pragma once
#include "bullet.h"
class CBulletThree :
	public CBullet
{
public:
	CBulletThree(void);
	~CBulletThree(void);
public:
	virtual void InitBullet(int X, int Y, HINSTANCE hIns);
	virtual void MoveBullet();
	virtual void ShowBullet(HDC hMemDC);
};

