#include "Frog.h"


CFrog::CFrog(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=rand()%(800);
	this->y=0;
	this->m_nBlood=3;
	this->Score_Style=200;
}


CFrog::~CFrog(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CFrog::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Frog_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Frog_Black));
}
 void CFrog::MoveFish()
 {
    y+=10;
 }
 void CFrog::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,229,185,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,229,185,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CFrog::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+20&& pBullet->x+10 <= this->x+229-20
		&& pBullet->y+10 >= this->y+20 && pBullet->y+10 <= this->y+185-20)
	{
		return true;
	}
	return false;
 
 
 
 }