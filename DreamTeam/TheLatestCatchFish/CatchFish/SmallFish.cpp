#include "SmallFish.h"


CSmallFish::CSmallFish(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=0;
	this->y=rand()%(500);
	this->m_nBlood=1;
	this->Score_Style=10;
}


CSmallFish::~CSmallFish(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CSmallFish::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SmallFish_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_SmallFish_Black));
}
 void CSmallFish::MoveFish()
 {
    x+=5;
 }
 void CSmallFish::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,98,69,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,98,69,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CSmallFish::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+10&& pBullet->x+10 <= this->x+98-10
		&& pBullet->y+10 >= this->y+10 && pBullet->y+10 <= this->y+69-10)
	{
		return true;
	}
	return false;
 
 
 
 }
