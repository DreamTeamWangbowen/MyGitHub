#include "Net.h"


CNet::CNet(void)
{
	h_bitmap_White=NULL;
	h_bitmap_Black=NULL;
	x=0;
	y=0;
	m_Net_Style=0;
}


CNet::~CNet(void)
{
	::DeleteObject(h_bitmap_White);
	::DeleteObject(h_bitmap_Black);
	h_bitmap_White=NULL;
	h_bitmap_Black=NULL;
}

void CNet::InitNet(int X, int Y, HINSTANCE hIns,int m_Bullet_Style)
{
	h_bitmap_White=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Net_White));
	h_bitmap_Black=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Net_Black));
	this->x=X;
	this->y=Y;
	this->m_Net_Style=m_Bullet_Style;
}

void CNet::ShowSingleNet(HDC hMemDC)
{
	HDC hTempMem_White = ::CreateCompatibleDC(hMemDC);
	HDC hTempMem_Black= ::CreateCompatibleDC(hMemDC);
	::SelectObject(hTempMem_White,h_bitmap_White);
	::SelectObject(hTempMem_Black,h_bitmap_Black);
			switch (this->m_Net_Style)
		{
			case 0:
		::BitBlt(hMemDC,this->x,this->y,179,179,hTempMem_White,179,0,SRCAND);
		::BitBlt(hMemDC,this->x,this->y,179,179,hTempMem_Black,179,0,SRCPAINT);
			break;
			case 1:
		::BitBlt(hMemDC,this->x,this->y,179,179,hTempMem_White,179+179,0,SRCAND);
		::BitBlt(hMemDC,this->x,this->y,179,179,hTempMem_Black,179+179,0,SRCPAINT);

			break;
			case 2:
		::BitBlt(hMemDC,this->x,this->y,179,179,hTempMem_White,0,179,SRCAND);
		::BitBlt(hMemDC,this->x,this->y,179,179,hTempMem_Black,0,179,SRCPAINT);
			
			break;
		}
	

	::DeleteDC(hTempMem_White); 
	::DeleteDC(hTempMem_Black); 

}