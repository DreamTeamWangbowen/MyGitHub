#include "GoldenDragon.h"

CGoldenDragon::CGoldenDragon(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=0;
	this->y=rand()%(500);
	this->m_nBlood=10;
	this->Score_Style=10000;
}


CGoldenDragon::~CGoldenDragon(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CGoldenDragon::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GoldenDragon_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GoldenDragon_Black));
}
 void CGoldenDragon::MoveFish()
 {
    x+=15;
 }
 void CGoldenDragon::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,317,126,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,317,126,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CGoldenDragon::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+100&& pBullet->x+10 <= this->x+317
		&& pBullet->y+10 >= this->y+40 && pBullet->y+10 <= this->y+126-40)
	{
		return true;
	}
	return false;
 
 
 
 }
