#include "BlueWhale.h"

CBlueWhale::CBlueWhale(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=rand()%(500);
	this->y=600;
	this->m_nBlood=5;
	this->Score_Style=100;
}


CBlueWhale::~CBlueWhale(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CBlueWhale::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BlueWhale_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BlueWhale_Black));
}
 void CBlueWhale::MoveFish()
 {
    x+=5;
    y-=5;
 }
 void CBlueWhale::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,162,151,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,162,151,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CBlueWhale::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+80&& pBullet->x+10<= this->x+162
		&& pBullet->y+10 >= this->y && pBullet->y+10 <= this->y+151-50)
	{
		return true;
	}
	return false;
 
 
 
 }
