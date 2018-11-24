#pragma once
#include"CGameCtrl.h"
#include"Back.h"
#include"Capture.h"
#include"Bullet.h"
#include"Fish.h"
#include"BigFish.h"
#include"BlueWhale.h"
#include"electricray.h"
#include"frog.h"
#include"goldendragon.h"
#include"goldenfish.h"
#include"goldfish.h"
#include"Mermaid.h"
#include"purplefish.h"
#include"smallfish.h"
#include"tuna.h"
#include"turtle.h"
#include"net.h"
#include"goldcoin.h"
#include"level.h"
class CCaptureCtrl:public CGameCtrl
{
public:
	CCaptureCtrl();
	~CCaptureCtrl();
	DECLARE()
public:
	CBack Back;
	CCapture Capture;
	CLevel Level;
	list<CBullet*>m_lstBullet;
	list<CFish*>m_lstBeated;
	list<CFish*>m_lstFish;
	list<CNet*>m_lstNet;
	list<CGoldCoin*>m_lstGoldCoin;
	size_t m_sscore;
	bool m_bflag_one;///防止多个Level up窗口弹出
	bool m_bflag_two;
	bool m_bflag_three;
public:

	virtual void OnCreateGame();
	virtual void OnGameDraw();
	virtual void OnGameRun(WPARAM nTimeID);
	virtual void OnKeyDown(WPARAM nKey);
	virtual void OnKeyUp(WPARAM nKey);
	virtual void OnLButtonDown(POINT point);
	virtual void OnLButtonUp(POINT point);
		   void ChangeBack();

public:
	void ShowAllBullet(HDC hMemDC);
	void AllBulletMove();
	void CreateFish();
	void ShowAllFish(HDC hMemDC);
	void AllFishMove();
	void BulletHitFish();
	void ShowAllBeated(HDC hMemDC);
	void ShowNet(HDC hMemDC);
	void DeleteNet();
	void ShowScore(HDC hMemDC);
	void ShowCoin(HDC hMemDC);
	void DeleteCoin();
	void BeginTimer();
	void EndTimer();
};