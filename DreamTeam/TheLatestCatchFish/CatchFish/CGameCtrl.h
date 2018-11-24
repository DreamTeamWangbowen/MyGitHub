#pragma once


#ifndef _CGAMECTRL_H_
#define _CGAMECTRL_H_
#define DECLARE() static CGameCtrl* CreateObject();

#define IMPLEMENT(ThisClass) \
	CGameCtrl* ThisClass::CreateObject()\
	{\
		return new ThisClass;\
	}\
	Init init##ThisClass(&ThisClass::CreateObject);

#include<windows.h>
class CGameCtrl;
typedef CGameCtrl* (*PFUN_CREATE_OBJECT)();  //创建对象的函数指针类型

class CGameCtrl{
public:static PFUN_CREATE_OBJECT pfnCreateObject;  //创建对象的函数指针变量
protected: HWND m_hwnd;
		   HINSTANCE m_hIns;

public:CGameCtrl()
	   {
			m_hwnd=NULL;
			m_hIns=NULL;
	   }
	   void SetHandle(HWND hwnd,HINSTANCE hins)
	   {
			m_hwnd=hwnd;
			m_hIns=hins;
	   }
	  virtual ~CGameCtrl()
	   {

	   }
public:
	virtual void OnCreateGame(){};   //WM_CREAT 创建游戏 初始化
	virtual void OnGameDraw(){};    //WM_PAINT 游戏的绘图
	virtual void OnGameRun(WPARAM nTimeID){};     //WM_TIMER游戏的运行
	virtual void OnKeyUp(WPARAM nkey){};
	virtual void OnKeyDown(WPARAM nkey){};
	virtual void OnLButtonDown(POINT point){};
	virtual void OnLButtonUp(POINT point){};
	virtual void OnMouseMove(POINT point){};
};

class Init
{
public:
	Init(PFUN_CREATE_OBJECT pfn)    //  负责给 函数指针 重新赋值
	{
		CGameCtrl::pfnCreateObject = pfn;
	}
};

#endif //_CGAMECTRL_H_