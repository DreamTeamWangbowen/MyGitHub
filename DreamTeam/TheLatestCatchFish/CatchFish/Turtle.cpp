#include "Turtle.h"


CTurtle::CTurtle(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=0;
	this->y=600;
	this->m_nBlood=3;
	this->Score_Style=50;
}


CTurtle::~CTurtle(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CTurtle::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Turtle_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Turtle_Black));
}
 void CTurtle::MoveFish()
 {
    x+=4;
	y-=4;
 }
 void CTurtle::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,68,55,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,68,55,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CTurtle::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+10&& pBullet->x+10 <= this->x+68-10
		&& pBullet->y+10 >= this->y+10 && pBullet->y+10 <= this->y+55-10)
	{
		return true;
	}
	return false;
 
 
 
 }
