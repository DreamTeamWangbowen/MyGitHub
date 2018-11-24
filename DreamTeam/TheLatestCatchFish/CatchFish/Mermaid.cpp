#include "Mermaid.h"


CMermaid::CMermaid(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=0;
	this->y=rand()%(500);
	this->m_nBlood=6;
	this->Score_Style=1000;
}


CMermaid::~CMermaid(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CMermaid::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Mermaid_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Mermaid_Black));
}
 void CMermaid::MoveFish()
 {
    x+=8;
 }
 void CMermaid::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,378,137,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,378,137,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CMermaid::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+20&& pBullet->x+10 <= this->x+378-20
		&& pBullet->y+10 >= this->y+40 && pBullet->y+10 <= this->y+137-40)
	{
		return true;
	}
	return false;
 
 
 
 }
