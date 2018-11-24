#include "GoldenFish.h"


CGoldenFish::CGoldenFish(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=0;
	this->y=rand()%(500);
	this->m_nBlood=2;
	this->Score_Style=50;
}


CGoldenFish::~CGoldenFish(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CGoldenFish::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GoldenFish_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GoldenFish_Black));
}
 void CGoldenFish::MoveFish()
 {
    x+=8;
 }
 void CGoldenFish::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,157,78,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,157,78,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CGoldenFish::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+10&& pBullet->x+10 <= this->x+157-10
		&& pBullet->y+10 >= this->y+10 && pBullet->y+10 <= this->y+78-20)
	{
		return true;
	}
	return false;
 
 
 
 }
