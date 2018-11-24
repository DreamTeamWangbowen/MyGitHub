#include "PurpleFish.h"

CPurpleFish::CPurpleFish(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=800;
	this->y=rand()%(500);
	this->m_nBlood=3;
	this->Score_Style=20;
}


CPurpleFish::~CPurpleFish(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CPurpleFish::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PurPle_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Purple_Black));
}
 void CPurpleFish::MoveFish()
 {
    x-=8;
	y+=4;
 }
 void CPurpleFish::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,97,40,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,97,40,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CPurpleFish::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+15 >= this->x&& pBullet->x <= this->x+70
		&& pBullet->y+15 >= this->y+10 && pBullet->y <= this->y+40)
	{
		return true;
	}
	return false;
 
 
 
 }