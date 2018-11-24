#include "Level.h"


CLevel::CLevel(void)
{
	m_One_W=0;
	m_One_B=0;
	m_Two_W=0;
	m_Two_B=0;
	m_Three_W=0;
	m_Three_B=0;
	m_Four_W=0;
	m_Four_B=0;
	this->x=300;
	this->y=15;
	this->m_slevel_up=0;
}


CLevel::~CLevel(void)
{
	::DeleteObject(m_One_W);
	::DeleteObject(m_One_B);
	::DeleteObject(m_Two_W);
	::DeleteObject(m_Two_B);
	::DeleteObject(m_Three_W);
	::DeleteObject(m_Three_B);
	::DeleteObject(m_Four_W);
	::DeleteObject(m_Four_B);
}
void CLevel::InitLevel(HINSTANCE hIns)
{
	m_One_W=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_ONE_W));
	m_One_B=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_ONE_B));
	m_Two_W=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TWO_W));
	m_Two_B=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_TWO_B));
	m_Three_W=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_THREE_W));
	m_Three_B=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_THREE_B));
	m_Four_W=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_FOUR_W));
	m_Four_B=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_FOUR_B));

}
void CLevel::ShowLevel(HDC hMemDC)
{
	HDC Temp_Hdc_W=::CreateCompatibleDC(hMemDC);
	HDC Temp_Hdc_B=::CreateCompatibleDC(hMemDC);

	switch(this->m_slevel_up)
	{
	case 0:
		{
	::SelectObject(Temp_Hdc_W,m_One_W);
	::SelectObject(Temp_Hdc_B,m_One_B);
		}
	break;
	case 1:
		{
	::SelectObject(Temp_Hdc_W,m_Two_W);
	::SelectObject(Temp_Hdc_B,m_Two_B);
		}
	break;
	case 2:
		{
	::SelectObject(Temp_Hdc_W,m_Three_W);
	::SelectObject(Temp_Hdc_B,m_Three_B);
		}
	break;
	case 3:
		{
	::SelectObject(Temp_Hdc_W,m_Four_W);
	::SelectObject(Temp_Hdc_B,m_Four_B);
		}
	break;

	}



	::BitBlt(hMemDC,this->x,this->y,48,42,Temp_Hdc_W,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,48,42,Temp_Hdc_B,0,0,SRCPAINT);
	::DeleteObject(Temp_Hdc_W);
	::DeleteObject(Temp_Hdc_B);
}