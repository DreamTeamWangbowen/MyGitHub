#include "GoldFish.h"


CGoldFish::CGoldFish(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=0;
	this->y=rand()%(500);
	this->m_nBlood=8;
	this->Score_Style=200;
}


CGoldFish::~CGoldFish(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CGoldFish::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WhiteWhale_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_WhileWhale_Black));
}
 void CGoldFish::MoveFish()
 {
    x+=4;
 }
 void CGoldFish::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,235,123,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,235,123,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CGoldFish::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+20&& pBullet->x+10 <= this->x+235-20
		&& pBullet->y+10 >= this->y+20 && pBullet->y+10 <= this->y+123-20)
	{
		return true;
	}
	return false;
 
 
 
 }