#include "Capture.h"


CCapture::CCapture(void)
{

	h_BitMap_Up_1=0;
	h_BitMap_Up_2=0;
	h_BitMap_Gun_1=0;
	h_BitMap_Gun_2=0;
	h_BitMap_Gun_15_plus_left=0;
	h_BitMap_Gun_15_minus_left=0;
	h_BitMap_Gun_15_plus_right=0;
	h_BitMap_Gun_15_minus_right=0;
	x=300;
	y=500;
	m_nBulletStyle=0;
	m_nGunStyle=0;
	m_nBulletCount=0;
	m_nCapture_Direction=0;
}


CCapture::~CCapture(void)
{

	::DeleteObject(h_BitMap_Up_1);
	::DeleteObject(h_BitMap_Up_2);
	::DeleteObject(h_BitMap_Gun_1);
	::DeleteObject(h_BitMap_Gun_2);
	::DeleteObject(h_BitMap_Gun_15_plus_left);
	::DeleteObject(h_BitMap_Gun_15_minus_left);
	::DeleteObject(h_BitMap_Gun_15_plus_right);
	::DeleteObject(h_BitMap_Gun_15_minus_right);
	h_BitMap_Up_1=0;
	h_BitMap_Up_2=0;
	h_BitMap_Gun_1=0;
	h_BitMap_Gun_2=0;
	h_BitMap_Gun_15_plus_left=0;
	h_BitMap_Gun_15_minus_left=0;
	h_BitMap_Gun_15_plus_right=0;
	h_BitMap_Gun_15_minus_right=0;

}

void CCapture::InitCapture(HINSTANCE hIns)
{

	h_BitMap_Up_1=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Up_1));
	h_BitMap_Up_2=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Up_2));
	h_BitMap_Gun_1=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Gun_One));
	h_BitMap_Gun_2=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Gun_Two));
	h_BitMap_Gun_15_plus_left=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Gun_15_plus_left));
	h_BitMap_Gun_15_minus_left=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Gun_15_minus_left));
	h_BitMap_Gun_15_plus_right=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Gun_15_plus_right));
	h_BitMap_Gun_15_minus_right=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_Gun_15_minus_right));
	
}
void CCapture::ShowCapture(HDC hMemDC)
{

	HDC tem_hdc_Up_1=::CreateCompatibleDC(hMemDC);
	HDC tem_hdc_Up_2=::CreateCompatibleDC(hMemDC);
	HDC tem_hdc_Gun_1=::CreateCompatibleDC(hMemDC);
	HDC tem_hdc_Gun_2=::CreateCompatibleDC(hMemDC);
	HDC tem_15_plus_left=::CreateCompatibleDC(hMemDC);
	HDC tem_15_minus_left=::CreateCompatibleDC(hMemDC);
	HDC tem_15_plus_right=::CreateCompatibleDC(hMemDC);
	HDC tem_15_minus_right=::CreateCompatibleDC(hMemDC);
	
	::SelectObject(tem_hdc_Up_1,h_BitMap_Up_1);
	::SelectObject(tem_hdc_Up_2,h_BitMap_Up_2);
	BitBlt(hMemDC,this->x,this->y+25,152,73,tem_hdc_Up_1,0,0,SRCAND);
	BitBlt(hMemDC,this->x,this->y+25,152,73,tem_hdc_Up_2,0,0,SRCPAINT);
	switch (m_nCapture_Direction)
	{
	case -1:	
	::SelectObject(tem_15_plus_left,h_BitMap_Gun_15_plus_left);
	::SelectObject(tem_15_minus_left,h_BitMap_Gun_15_minus_left);
	::BitBlt(hMemDC,this->x+5,(this->y)-5,110,70,tem_15_plus_left,0,163,SRCAND);
	::BitBlt(hMemDC,this->x+5,(this->y)-5,110,70,tem_15_minus_left,0,163,SRCPAINT);
		break;
	case 0:	
	::SelectObject(tem_hdc_Gun_1,h_BitMap_Gun_1);
	::SelectObject(tem_hdc_Gun_2,h_BitMap_Gun_2);
	::BitBlt(hMemDC,this->x+22,(this->y)-5,103,70,tem_hdc_Gun_1,0,50,SRCAND);
	::BitBlt(hMemDC,this->x+22,(this->y)-5,103,70,tem_hdc_Gun_2,0,50,SRCPAINT);
		break;
	case 1:	
	::SelectObject(tem_15_plus_right,h_BitMap_Gun_15_plus_right);
	::SelectObject(tem_15_minus_right,h_BitMap_Gun_15_minus_right);
	::BitBlt(hMemDC,this->x+22,(this->y)-5,110,70,tem_15_plus_right,20,55,SRCAND);
	::BitBlt(hMemDC,this->x+22,(this->y)-5,110,70,tem_15_minus_right,20,55,SRCPAINT);
		break;

	}
	::DeleteDC(tem_hdc_Up_1);
	::DeleteDC(tem_hdc_Up_2);
	::DeleteDC(tem_hdc_Gun_1);
	::DeleteDC(tem_hdc_Gun_2);
	::DeleteDC(tem_15_plus_left);
	::DeleteDC(tem_15_minus_left);
	::DeleteDC(tem_15_plus_right);
	::DeleteDC(tem_15_minus_right);
}


void CCapture::SendBullet(list<CBullet*>&m_lstBullet, HINSTANCE hIns)
{
	CBullet* pBullet=NULL;
	switch (m_nBulletStyle)
	{
	case 0:
		pBullet=new CBulletOne;
		break;
	case 1:
		pBullet=new CBulletTwo;
		break;
	case 2:
		pBullet=new CBulletThree;
		break;
	}

	pBullet->InitBullet(this->x+22,this->y-40,hIns);
	m_lstBullet.push_back(pBullet);
	this->ChangeBullet(m_lstBullet); ///每发射一个 初始化方向

}

void CCapture::ChangeBullet(list<CBullet*>&m_lstBullet)
{
	list<CBullet*>::iterator it_Bullet=m_lstBullet.begin();
	while(it_Bullet!=m_lstBullet.end())
	{
		if(350==(*it_Bullet)->x&&460==(*it_Bullet)->y)		///使已经射出去的炮弹不随Capture旋转
		{
			(*it_Bullet)->m_Bullet_Direction=this->m_nCapture_Direction;
		}
			++it_Bullet;
	}


}
