#include "ElectricRay.h"

CElectricRay::CElectricRay(void)
{
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
	this->x=0;
	this->y=rand()%(500);
	this->m_nBlood=3;
	this->Score_Style=50;
}


CElectricRay::~CElectricRay(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	this->m_hBmpFish_White=NULL;
	this->m_hBmpFish_Black=NULL;
}


void CElectricRay::InitFish(HINSTANCE hIns)
{
	m_hBmpFish_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_ElectricRay_White));
	m_hBmpFish_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_ElectricRay_Black));
}
 void CElectricRay::MoveFish()
 {
    x+=6;
 }
 void CElectricRay::ShowFish(HDC hMemDC)
 {
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,m_hBmpFish_White);
	::SelectObject(hTempMem_Black,m_hBmpFish_Black);
	::BitBlt(hMemDC,this->x,this->y,159,215,hTempMem_White,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,159,215,hTempMem_Black,0,0,SRCPAINT);

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 
 
 }
bool CElectricRay::IsBulletFish(CBullet* pBullet)
 {
 if(pBullet->x+10 >= this->x+80&& pBullet->x+10 <= this->x+159
		&& pBullet->y+10 >= this->y+20 && pBullet->y+10 <= this->y+215-20)
	{
		return true;
	}
	return false;
 
 
 
 }
