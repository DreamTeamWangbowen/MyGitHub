#include "Back.h"


CBack::CBack(void)
{
	m_hBackOne=NULL;
	m_hBackTwo=NULL;
	m_hBackThree=NULL;
	m_hHeadPicture_W=NULL;
	m_hHeadPicture_B=NULL;
	m_lele_Catch_Fish=NULL;
	BACK_ID_COUNT=0;
	y=0;
	x=0;

}


CBack::~CBack(void)
{
	::DeleteObject(m_hBackOne);
	::DeleteObject(m_hBackTwo);
	::DeleteObject(m_hBackThree);
	::DeleteObject(m_hHeadPicture_W);
	::DeleteObject(m_hHeadPicture_B);
	::DeleteObject(m_lele_Catch_Fish);
	m_hBackOne=NULL;
	m_hBackTwo=NULL;
	m_hBackThree=NULL;
	m_hHeadPicture_W=NULL;
	m_hHeadPicture_B=NULL;
	m_lele_Catch_Fish=NULL;
}

void CBack::InitBack(HINSTANCE hIns)
{
	m_hBackOne=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MAP_0));
	m_hBackTwo=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MAP_2));
	m_hBackThree=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_MAP_3));
	m_hChangeBack=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_ChangeBack));
	m_hHeadPicture_W=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_HeadPicture_W));
	m_hHeadPicture_B=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_HeadPicture_B));
	m_lele_Catch_Fish=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_lele_Catch_Fish));
	
}
void CBack::ShowBack(HDC hMemDC)  ///背景重绘得有点特别
{
	HDC hdcMemDCOne=::CreateCompatibleDC(hMemDC);
	HDC hdcMemDCTwo=::CreateCompatibleDC(hMemDC);
	HDC hdcMemDCThree=::CreateCompatibleDC(hMemDC);
	HDC hdcMemDCFour=::CreateCompatibleDC(hMemDC);
	HDC hdcHeadPicture_W=::CreateCompatibleDC(hMemDC);
	HDC hdcHeadPicture_B=::CreateCompatibleDC(hMemDC);
	
	::SelectObject(hdcHeadPicture_W,m_hHeadPicture_W);
	::SelectObject(hdcHeadPicture_B,m_hHeadPicture_B);
	
	switch(BACK_ID_COUNT){
	case 1:
		{	
	
	::SelectObject(hdcMemDCOne,m_hBackOne);
	::SelectObject(hdcMemDCFour,m_hChangeBack);

	::BitBlt(hMemDC,x,y,800,600,hdcMemDCOne,0,0,SRCCOPY);
	::BitBlt(hMemDC,0,0,30,32,hdcMemDCFour,0,0,SRCCOPY);

		}
		   break;

	case 2:
		{

	::SelectObject(hdcMemDCTwo,m_hBackTwo);  ///选错了！！
	::SelectObject(hdcMemDCFour,m_hChangeBack);

	::BitBlt(hMemDC,x,y,800,600,hdcMemDCTwo,0,0,SRCCOPY);
	::BitBlt(hMemDC,0,0,30,32,hdcMemDCFour,0,0,SRCCOPY);
		}		
		   break;
	case 3:
		{

	::SelectObject(hdcMemDCThree,m_hBackThree);
	::SelectObject(hdcMemDCFour,m_hChangeBack);

	::BitBlt(hMemDC,x,y,800,600,hdcMemDCThree,0,0,SRCCOPY);
	::BitBlt(hMemDC,0,0,30,32,hdcMemDCFour,0,0,SRCCOPY);	
		}
		   break;
	}
	::BitBlt(hMemDC,500,500,100,100,hdcHeadPicture_W,0,0,SRCAND);
	::BitBlt(hMemDC,500,500,100,100,hdcHeadPicture_B,0,0,SRCPAINT);
	::DeleteDC(hdcMemDCOne);
	::DeleteDC(hdcMemDCTwo);
	::DeleteDC(hdcMemDCThree);
	::DeleteDC(hdcMemDCFour);
	::DeleteDC(hdcHeadPicture_W);
	::DeleteDC(hdcHeadPicture_B);

	
}

void CBack::ShowMenu(HDC hMemDC)
{
	HDC hdclele_Catch_Fish=::CreateCompatibleDC(hMemDC);
	::SelectObject(hdclele_Catch_Fish,m_lele_Catch_Fish);
	::BitBlt(hMemDC,0,0,800,600,hdclele_Catch_Fish,0,0,SRCCOPY);
	::DeleteDC(hdclele_Catch_Fish);

}
void CBack::ShowMusic()
{

	::PlaySound(TEXT("C:\\Users\\Administrator\\Documents\\Visual Studio 2012\\Projects\\CatchFish\\CatchFish\\pic\\bg_01.wav"),NULL,SND_LOOP|SND_ASYNC );//SND_FILENAME|SND_SYNC
	////用异步方式播放声音，PlaySound函数在开始播放后立即返回    这个函数解决了等待音乐结束才能继续程序的bug!!     - -b 
}