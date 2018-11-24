#include "BulletOne.h"


CBulletOne::CBulletOne(void)
{
	m_hBmpBullet_1=0;
	m_hBmpBullet_2=0;
	m_hBmpBullet_15_plus_left=0;
	m_hBmpBullet_15_minus_left=0;
	m_hBmpBullet_15_plus_right=0;
	m_hBmpBullet_15_minus_right=0;
	m_Bullet_Direction=0;
	m_Bullet_Style=0;
}


CBulletOne::~CBulletOne(void)
{
	::DeleteObject(m_hBmpBullet_1);
	::DeleteObject(m_hBmpBullet_2);
	::DeleteObject(m_hBmpBullet_15_plus_left);
	::DeleteObject(m_hBmpBullet_15_minus_left);
	::DeleteObject(m_hBmpBullet_15_plus_right);
	::DeleteObject(m_hBmpBullet_15_minus_right);
	m_hBmpBullet_1=0;
	m_hBmpBullet_2=0;
	m_hBmpBullet_15_plus_left=0;
	m_hBmpBullet_15_minus_left=0;
	m_hBmpBullet_15_plus_right=0;
	m_hBmpBullet_15_minus_right=0;

}

void CBulletOne::InitBullet(int X,int Y ,HINSTANCE hIns)
{

	this->x=350;
	this->y=460;
	m_hBmpBullet_1=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Bullet_1));
	m_hBmpBullet_2=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Bullet_2));
	m_hBmpBullet_15_plus_left=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Bullet_15_plus_left));
	m_hBmpBullet_15_minus_left=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Bullet_15_minus_left));
	m_hBmpBullet_15_plus_right=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Bullet_15_plus_right));
	m_hBmpBullet_15_minus_right=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Bullet_15_minus_right));

}
void CBulletOne::MoveBullet()
{
	switch(m_Bullet_Direction)
	{
	case -1:
		(this->x)-=10;
		(this->y)-=10;
		break;
	case 0:
		(this->y)-=10;
		break;
	case 1:
		(this->x)+=10;
		(this->y)-=10;
		break;
	}
}
void CBulletOne::ShowBullet(HDC hMemDC)
{
	HDC tem_hdc_1=::CreateCompatibleDC(hMemDC);
	HDC tem_hdc_2=::CreateCompatibleDC(hMemDC);
	HDC tem_15_plus_left=::CreateCompatibleDC(hMemDC);
	HDC tem_15_minus_left=::CreateCompatibleDC(hMemDC);
	HDC tem_15_plus_right=::CreateCompatibleDC(hMemDC);
	HDC tem_15_minus_right=::CreateCompatibleDC(hMemDC);

	switch (m_Bullet_Direction)
	{
	case -1:	
	::SelectObject(tem_15_plus_left,m_hBmpBullet_15_plus_left);
	::SelectObject(tem_15_minus_left,m_hBmpBullet_15_minus_left);
	::BitBlt(hMemDC,this->x,this->y,53,49,tem_15_plus_left,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,53,49,tem_15_minus_left,0,0,SRCPAINT);
		break;
	case 0:
	::SelectObject(tem_hdc_1,m_hBmpBullet_1);
	::SelectObject(tem_hdc_2,m_hBmpBullet_2);
	::BitBlt(hMemDC,this->x,this->y,45,39,tem_hdc_1,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,45,39,tem_hdc_2,0,0,SRCPAINT);
		break;
	case 1:	
	::SelectObject(tem_15_plus_right,m_hBmpBullet_15_plus_right);
	::SelectObject(tem_15_minus_right,m_hBmpBullet_15_minus_right);	
	::BitBlt(hMemDC,this->x,this->y,53,49,tem_15_plus_right,0,0,SRCAND);
	::BitBlt(hMemDC,this->x,this->y,53,49,tem_15_minus_right,0,0,SRCPAINT);
		break;
	}
	
	::DeleteDC(tem_hdc_1);
	::DeleteDC(tem_hdc_2);
	::DeleteDC(tem_15_plus_left);
	::DeleteDC(tem_15_minus_left);
	::DeleteDC(tem_15_plus_right);
	::DeleteDC(tem_15_minus_right);
}