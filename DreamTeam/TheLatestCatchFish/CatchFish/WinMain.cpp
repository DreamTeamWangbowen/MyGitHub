#include <windows.h>
#include "CGameCtrl.h"
#include <time.h>
#include"resource.h"

PFUN_CREATE_OBJECT CGameCtrl::pfnCreateObject = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hIns = NULL;

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR pCmdLine,int nCmdShow)
{
	srand((unsigned int)time(NULL));

	hIns = hInstance;

	//1.  设计窗口
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;  //  是否要分配 额外的空间
	wndclass.cbSize = sizeof(wndclass);  //  节点的大小
	wndclass.cbWndExtra = 0;  //  是否要分配 额外的空间
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;  //  背景颜色
	wndclass.hCursor = ::LoadCursor(hIns,MAKEINTRESOURCE(IDC_CURSOR1));   //  加载一个光标  不是系统光标要用实例句柄加载
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;   //  左上的小图标
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = "Dream";   //  注册窗口类的名字
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW|CS_VREDRAW;   


	//2.  注册
	if(!::RegisterClassEx(&wndclass))
	{
		::MessageBox(NULL,"注册失败!","提示",MB_OK);
		return 0;
	}



	//3.  创建
	//  CreateWindow()   发送了  WM_CREATE
	HWND hwnd = ::CreateWindow("Dream","Dream team",WS_OVERLAPPEDWINDOW,300,100,800+16,600+38,NULL,NULL,hInstance,NULL);
	////第一个坐标为窗口坐标
	if(hwnd == NULL)
	{
		::MessageBox(NULL,"创建失败!","提示",MB_OK);
		return 0;
	}
	

	//4.  显示
	::ShowWindow(hwnd,nCmdShow/*SW_HIDE 隐藏*/);


	//5.  消息循环
	MSG msg;
	while(::GetMessage(&msg,NULL,0,0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);  // 调用 回调 函数 处理
	}
	return 0;
}


CGameCtrl* ctrl = NULL;


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		if(CGameCtrl::pfnCreateObject == NULL)
		{
			::MessageBox(NULL,"游戏创建失败!","提示",MB_OK);
			::DestroyWindow(hwnd);  //  销毁窗口
			::PostQuitMessage(0);  //  退出程序
		}
		else
		{
			ctrl = (*CGameCtrl::pfnCreateObject)();  //  创建一个游戏的 控制器的对象
			ctrl->SetHandle(hwnd,hIns);    //  给句柄赋值
			ctrl->OnCreateGame();  //  游戏的初始化
		}
		break;
	case WM_PAINT:
		ctrl->OnGameDraw();
		break;
	case WM_TIMER:
		ctrl->OnGameRun(wParam);
		break;
	case WM_KEYDOWN:
		ctrl->OnKeyDown(wParam);
		break;
	case WM_KEYUP:
		ctrl->OnKeyUp(wParam);
		break;
	case WM_LBUTTONDOWN:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnLButtonDown(point);
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnLButtonUp(point);
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			ctrl->OnMouseMove(point);
		}
		break;
	case WM_CLOSE:
		//ctrl->StopGame();
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);   //  发送退出的消息
		break;
	case WM_QUIT:
		delete ctrl;
		ctrl = NULL;
		break;
	}
	return ::DefWindowProc(hwnd,uMsg,wParam,lParam);   // 没有处理的 消息 执行默认处理的
}