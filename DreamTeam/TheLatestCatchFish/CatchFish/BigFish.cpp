#include "BigFish.h"


CBigFish::CBigFish(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=0;
	this->y=rand()%(500);
	this->m_nBlood=2;
	this->Score_Style=20;
}


CBigFish::~CBigFish(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CBigFish::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BigFish_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BigFish_Black));
}
 void CBigFish::MoveFish()
 {
    x+=8;
 }
 void CBigFish::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	
	::BitBlt(hMemDC,this->x,this->y,157,82,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,157,82,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CBigFish::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+10&& pBullet->x+10 <= this->x+157-80
		&& pBullet->y+10 >= this->y+20 && pBullet->y+10 <= this->y+82-20)
	{
		return true;
	}
	return false;
 
 
 
 }