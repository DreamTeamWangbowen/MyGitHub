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

	//1.  ��ƴ���
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;  //  �Ƿ�Ҫ���� ����Ŀռ�
	wndclass.cbSize = sizeof(wndclass);  //  �ڵ�Ĵ�С
	wndclass.cbWndExtra = 0;  //  �Ƿ�Ҫ���� ����Ŀռ�
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;  //  ������ɫ
	wndclass.hCursor = ::LoadCursor(hIns,MAKEINTRESOURCE(IDC_CURSOR1));   //  ����һ�����  ����ϵͳ���Ҫ��ʵ���������
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;   //  ���ϵ�Сͼ��
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = "Dream";   //  ע�ᴰ���������
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW|CS_VREDRAW;   


	//2.  ע��
	if(!::RegisterClassEx(&wndclass))
	{
		::MessageBox(NULL,"ע��ʧ��!","��ʾ",MB_OK);
		return 0;
	}



	//3.  ����
	//  CreateWindow()   ������  WM_CREATE
	HWND hwnd = ::CreateWindow("Dream","Dream team",WS_OVERLAPPEDWINDOW,300,100,800+16,600+38,NULL,NULL,hInstance,NULL);
	////��һ������Ϊ��������
	if(hwnd == NULL)
	{
		::MessageBox(NULL,"����ʧ��!","��ʾ",MB_OK);
		return 0;
	}
	

	//4.  ��ʾ
	::ShowWindow(hwnd,nCmdShow/*SW_HIDE ����*/);


	//5.  ��Ϣѭ��
	MSG msg;
	while(::GetMessage(&msg,NULL,0,0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);  // ���� �ص� ���� ����
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
			::MessageBox(NULL,"��Ϸ����ʧ��!","��ʾ",MB_OK);
			::DestroyWindow(hwnd);  //  ���ٴ���
			::PostQuitMessage(0);  //  �˳�����
		}
		else
		{
			ctrl = (*CGameCtrl::pfnCreateObject)();  //  ����һ����Ϸ�� �������Ķ���
			ctrl->SetHandle(hwnd,hIns);    //  �������ֵ
			ctrl->OnCreateGame();  //  ��Ϸ�ĳ�ʼ��
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
		::PostQuitMessage(0);   //  �����˳�����Ϣ
		break;
	case WM_QUIT:
		delete ctrl;
		ctrl = NULL;
		break;
	}
	return ::DefWindowProc(hwnd,uMsg,wParam,lParam);   // û�д���� ��Ϣ ִ��Ĭ�ϴ����
}