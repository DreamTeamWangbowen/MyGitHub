#include "Fish.h"


CFish::CFish(void)
{
	m_hBmpFish_White=0;
	m_hBmpFish_Black=0;
	m_nBlood=0;
	x=0;
	y=0;
	Score_Style=0;
}


CFish::~CFish(void)
{
	::DeleteObject(m_hBmpFish_White);
	::DeleteObject(m_hBmpFish_Black);
	m_hBmpFish_White=NULL;
	m_hBmpFish_Black=NULL;
}
