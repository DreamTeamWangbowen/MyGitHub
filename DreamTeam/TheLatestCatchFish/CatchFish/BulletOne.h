#pragma once
#include "bullet.h"
class CBulletOne :
	public CBullet
{
public:
	CBulletOne(void);
	~CBulletOne(void);
public:
	virtual void InitBullet(int X, int Y, HINSTANCE hIns);
	virtual void MoveBullet();
	virtual void ShowBullet(HDC hMemDC);
};

