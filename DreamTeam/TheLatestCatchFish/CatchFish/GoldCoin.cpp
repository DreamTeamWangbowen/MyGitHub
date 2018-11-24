#include "GoldCoin.h"


CGoldCoin::CGoldCoin(void)
{
	hBitmap_White=NULL;
	hBitmap_Black=NULL;
	x=0;
	y=0;
	GoldCoin_Style=0;
}


CGoldCoin::~CGoldCoin(void)
{
	::DeleteObject(hBitmap_White);
	::DeleteObject(hBitmap_Black);
	hBitmap_White=NULL;
	hBitmap_Black=NULL;
}
void CGoldCoin::InitCGoldCoin(HINSTANCE m_hIns,int Position_X,int Position_Y,int GoldCoinStyle)
{
	this->x=Position_X;
	this->y=Position_Y;
	this->GoldCoin_Style=GoldCoinStyle;
	this->hBitmap_White=::LoadBitmap(m_hIns,MAKEINTRESOURCE(IDB_GoldCoin_White));
	this->hBitmap_Black=::LoadBitmap(m_hIns,MAKEINTRESOURCE(IDB_GoldCoin_Black));
}
void CGoldCoin::ShowGoldCoin(HDC hMemDC)
{
	HDC Temp_White_Hdc=::CreateCompatibleDC(hMemDC);
	HDC Temp_Black_Hdc=::CreateCompatibleDC(hMemDC);
	::SelectObject(Temp_White_Hdc,hBitmap_White);
	::SelectObject(Temp_Black_Hdc,hBitmap_Black);
	switch (this->GoldCoin_Style)
				{
				case 10:
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_White_Hdc,0,0,SRCAND);
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_Black_Hdc,0,0,SRCPAINT);

					break;
				case 20:
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_White_Hdc,0+82+82,0,SRCAND);
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_Black_Hdc,0+82+82,0,SRCPAINT);

					break;
				case 50:
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_White_Hdc,0+82+82+82,0+77,SRCAND);
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_Black_Hdc,0+82+82+82,0+77,SRCPAINT);

					break;
				case 100:
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_White_Hdc,0,0+77+77,SRCAND);
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_Black_Hdc,0,0+77+77,SRCPAINT);

					break;
				case 200:
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_White_Hdc,0+82,0+77+77,SRCAND);
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_Black_Hdc,0+82,0+77+77,SRCPAINT);

					break;
				case 500:
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_White_Hdc,0+82*5,0+77*2,SRCAND);
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_Black_Hdc,0+82*5,0+77*2,SRCPAINT);

					break;
				case 1000:
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_White_Hdc,0+82*4,0+77,SRCAND);
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_Black_Hdc,0+82*4,0+77,SRCPAINT);

					break;
				case 10000:
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_White_Hdc,0+3*82,0+77,SRCAND);
					::BitBlt(hMemDC,this->x,this->y,82,77,Temp_Black_Hdc,0+3*82,0+77,SRCPAINT);

					break;
				}


	::DeleteObject(Temp_White_Hdc);
	::DeleteObject(Temp_Black_Hdc);

}