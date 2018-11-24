#include "Tuna.h"


CTuna::CTuna(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=0;
	this->y=rand()%(500);
	this->m_nBlood=2;
	this->Score_Style=50;
}


CTuna::~CTuna(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CTuna::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TunaFish_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TunaFish_Black));
}
 void CTuna::MoveFish()
 {
    x+=6;
 }
 void CTuna::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,237,78,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,237,78,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CTuna::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+20&& pBullet->x+10 <= this->x+237-20
		&& pBullet->y+10 >= this->y+10 && pBullet->y+10 <= this->y+78-20)
	{
		return true;
	}
	return false;
 
 
 
 }