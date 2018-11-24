#include"CCaptureCtrl.h"
IMPLEMENT(CCaptureCtrl)

CCaptureCtrl::CCaptureCtrl()
{
	m_sscore=0;
	this->m_bflag_one=false;
	this->m_bflag_two=false;
	this->m_bflag_three=false;

}
CCaptureCtrl::~CCaptureCtrl()
{
	list<CBullet*>::iterator it_Bullet=m_lstBullet.begin();
	while(it_Bullet!=m_lstBullet.end())
	{
		delete (*it_Bullet);
		++it_Bullet;
	}


}
void CCaptureCtrl:: OnCreateGame()
{
	Back.InitBack(m_hIns);
		Back.ShowMusic();  ///bug开始播放可能需要时间  确实是需要初始化的时间 还是放创建里比较好
	Capture.InitCapture(m_hIns);
	//初始化等级
	Level.InitLevel(m_hIns);
	::SetTimer(m_hwnd,BULLET_MOVE_TIMER_ID,100,NULL);
	::SetTimer(m_hwnd,CREATE_FISH_TIMER_ID,2000,NULL);
	::SetTimer(m_hwnd,FISH_MOVE_TIMER_ID,100,NULL);
	::SetTimer(m_hwnd,DELETE_NET_TIMER_ID,2000,NULL);
	::SetTimer(m_hwnd,DELETE_COIN_TIMER_ID,6000,NULL);
	
} 
void CCaptureCtrl:: OnGameDraw()
{

	HDC hdc=::GetDC(m_hwnd);
	HDC hMemDC=::CreateCompatibleDC(hdc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc,800,600); 
	::SelectObject(hMemDC,hBitmap);
	if(0==Back.BACK_ID_COUNT)
	{
		Back.ShowMenu(hMemDC);
	}
	////把图片放到hMemDC中
	else
	{
	Back.ShowBack(hMemDC);
	this->ShowAllFish(hMemDC);  ///逻辑位置
	Capture.ShowCapture(hMemDC);
	this->ShowAllBullet(hMemDC);
	this->ShowNet(hMemDC);  ///显示所有渔网
	///显示得分
	this->ShowScore(hMemDC);
	///显示币子
	this->ShowCoin(hMemDC);

	Level.ShowLevel(hMemDC);///改变分数改变等级 不能让其突然闪烁上一张图
	}

	::BitBlt(hdc,0,0,800,600,hMemDC,0,0,SRCCOPY);   ///传输到窗口

	::DeleteDC(hMemDC);
	::DeleteObject(hBitmap);
	::ReleaseDC(m_hwnd,hdc);


			

}
void CCaptureCtrl::OnGameRun(WPARAM nTimeID)
{
	if(nTimeID==BULLET_MOVE_TIMER_ID)
	{
		this->AllBulletMove();//所有炮弹移动   
		///判断一下
		this->BulletHitFish();///打死没
		this->OnGameDraw();  //重绘游戏
     }

	if(nTimeID==CREATE_FISH_TIMER_ID)
	{
		this->CreateFish();
		this->OnGameDraw(); 
     }

	if(nTimeID==FISH_MOVE_TIMER_ID)
	{
		this->AllFishMove(); 
		this->OnGameDraw(); 
     }

	if(nTimeID==DELETE_NET_TIMER_ID)
	{
	this->DeleteNet();
	this->OnGameDraw(); 
	}
	if(nTimeID==DELETE_COIN_TIMER_ID)
	{
	this->DeleteCoin();
	this->OnGameDraw(); 
	}
	

}
void CCaptureCtrl::OnKeyUp(WPARAM nkey)
{


}
void CCaptureCtrl::OnKeyDown(WPARAM nkey)
{
		switch (nkey)
	{
	case VK_LEFT:

			--Capture.m_nCapture_Direction;
		
		break;

	case VK_RIGHT:

			++Capture.m_nCapture_Direction;
		
		break;
	case VK_UP:
		Capture.SendBullet(m_lstBullet,m_hIns);
		this->OnGameDraw();  
		break;

	case VK_DOWN:	
		++Capture.m_nBulletStyle;
		if(3==Capture.m_nBulletStyle)   //位置不同 结果大有不同
	{
		Capture.m_nBulletStyle=0;	
	}
	
		break;
	}

		if(Capture.m_nCapture_Direction<-1)
	{
		Capture.m_nCapture_Direction=-1;
	}
		if(Capture.m_nCapture_Direction>1)
	{
		Capture.m_nCapture_Direction=1;
	}
	


}

void CCaptureCtrl::OnLButtonUp(POINT point)
{
	

}
void CCaptureCtrl::OnLButtonDown(POINT point)
{
	if(0<=point.x&&point.x<=30&&0<=point.y&&point.y<=32&&Back.BACK_ID_COUNT!=0)
	{
		ChangeBack();
		this->OnGameDraw();
	}
	if(250<=point.x&&point.x<=500&&240<=point.y&&point.y<=400&&Back.BACK_ID_COUNT==0)
	{
		++Back.BACK_ID_COUNT;
	}

}

void CCaptureCtrl::ChangeBack()
{
	HDC hdc=GetDC(m_hwnd);
	HDC hdcMemDCFour=::CreateCompatibleDC(hdc);
	HDC hdcMemDCOne=::CreateCompatibleDC(hdc);
	HDC hdcMemDCTwo=::CreateCompatibleDC(hdc);
	HDC hdcMemDCThree=::CreateCompatibleDC(hdc);
	++Back.BACK_ID_COUNT;
	if(4==Back.BACK_ID_COUNT){Back.BACK_ID_COUNT=1;}
	switch(Back.BACK_ID_COUNT)
	{
	case 1:
		
		::SelectObject(hdcMemDCOne,Back.m_hBackOne);
		::SelectObject(hdcMemDCFour,Back.m_hChangeBack);
		::BitBlt(hdc,0,0,800,600,hdcMemDCOne,0,0,SRCCOPY);
		::BitBlt(hdc,0,0,30,32,hdcMemDCFour,0,0,SRCCOPY);

		
		break;
	case 2:
		
		::SelectObject(hdcMemDCTwo,Back.m_hBackTwo);
		::SelectObject(hdcMemDCFour,Back.m_hChangeBack);
		::BitBlt(hdc,0,0,800,600,hdcMemDCTwo,0,0,SRCCOPY);
		::BitBlt(hdc,0,0,30,32,hdcMemDCFour,0,0,SRCCOPY);
		

		break;
	case 3:
		
		::SelectObject(hdcMemDCThree,Back.m_hBackThree);
		::SelectObject(hdcMemDCFour,Back.m_hChangeBack);
		::BitBlt(hdc,0,0,800,600,hdcMemDCThree,0,0,SRCCOPY);
		::BitBlt(hdc,0,0,30,32,hdcMemDCFour,0,0,SRCCOPY);
		

		break;

	}		
		::DeleteDC(hdcMemDCOne);
		::DeleteDC(hdcMemDCTwo);
		::DeleteDC(hdcMemDCThree);
		::DeleteDC(hdcMemDCFour);

}

void CCaptureCtrl::ShowAllBullet(HDC hMemDC)
{
	list<CBullet*>::iterator it_Bullet=m_lstBullet.begin();
	while(it_Bullet!=m_lstBullet.end())
	{
		(*it_Bullet)->ShowBullet(hMemDC);
			++it_Bullet;
	}

}
void CCaptureCtrl::AllBulletMove()
{
	list<CBullet*>::iterator it_Bullet=m_lstBullet.begin();
	while(it_Bullet!=m_lstBullet.end())
	{
		if((*it_Bullet)->y<0||(*it_Bullet)->x<0||(*it_Bullet)->y>600||(*it_Bullet)->x>800)
		{
			delete (*it_Bullet);
			it_Bullet=m_lstBullet.erase(it_Bullet);
		
		}
		else
		{
			(*it_Bullet)->MoveBullet();
			++it_Bullet;
		}
	}


}

void CCaptureCtrl::CreateFish()
{
	CFish* pFish=NULL;
	int index=rand()%45;
	if(0<=index&&index<=2)
	{
		pFish=new CBigFish;
	}
	else if(3<=index&&index<=4)
	{
		pFish=new CGoldFish;
	}
	else if(5<=index&&index<=6)
	{
		pFish=new CBlueWhale;
	}

	else if(7<=index&&index<=12)
	{
		pFish=new CSmallFish;
	}
	else if(13<=index&&index<=16)
	{
		pFish=new CElectricRay;
	}
	else if(17<=index&&index<=19)
	{
		pFish=new CFrog;
	}
	else if(20<=index&&index<=26)
	{
		pFish=new CPurpleFish;
	}
	else if(27==index)
	{
		pFish=new CGoldenDragon;
	}
	else if(28<=index&&index<=30)
	{
		pFish=new CMermaid;
	}
	else if(31<=index&&index<=35)
	{
		pFish=new CTurtle;
	}
	else if(36<=index&&index<=40)
	{
		pFish=new CGoldenFish;
	}
	else if(41<=index&&index<=45)   ////每次只走一个  else if(36<=index&&index<=40) 与以上重复的不执行哦
	{
		pFish=new CTuna;
	}
	pFish->InitFish(m_hIns);
	this->m_lstFish.push_back(pFish);
}

void CCaptureCtrl::AllFishMove()
{
	list<CFish*>::iterator it_Fish=this->m_lstFish.begin();  
	while(it_Fish!=m_lstFish.end())
	{
		if((*it_Fish)->y>600)
		{
			delete (*it_Fish);
			it_Fish=m_lstFish.erase(it_Fish);
		}
		else
		{
			(*it_Fish)->MoveFish();
			++it_Fish;
		}
	}

}

void CCaptureCtrl::ShowAllFish(HDC hMemDC)
{
	list<CFish*>::iterator it_Fish=m_lstFish.begin();
	while(it_Fish!=m_lstFish.end())
	{
		(*it_Fish)->ShowFish(hMemDC);
			++it_Fish;
	}


}
void CCaptureCtrl::BulletHitFish()
{
	list<CBullet*>::iterator it_Bullet=m_lstBullet.begin();
	while(it_Bullet!=m_lstBullet.end())
	{
		bool n_flag=false;
		list<CFish*>::iterator it_Fish=m_lstFish.begin(); 
		while(it_Fish!=m_lstFish.end())
		{
			if((*it_Fish)->IsBulletFish(*it_Bullet))
			{
				CNet* Net=new CNet;
				Net->InitNet((*it_Fish)->x,(*it_Fish)->y,this->m_hIns,(*it_Bullet)->m_Bullet_Style);///传入网标
				///加分
				///金币
				CGoldCoin* GoldCoin=new CGoldCoin;

				switch ((*it_Fish)->Score_Style)
				{
				case 10:
					this->m_sscore+=10;
					GoldCoin->InitCGoldCoin(this->m_hIns,(*it_Fish)->x,(*it_Fish)->y,10);
					break;
				case 20:
					this->m_sscore+=20;
					GoldCoin->InitCGoldCoin(this->m_hIns,(*it_Fish)->x,(*it_Fish)->y,20);
					break;
				case 50:
					this->m_sscore+=50;
					GoldCoin->InitCGoldCoin(this->m_hIns,(*it_Fish)->x,(*it_Fish)->y,50);
					break;
				case 100:
					this->m_sscore+=100;
					GoldCoin->InitCGoldCoin(this->m_hIns,(*it_Fish)->x,(*it_Fish)->y,100);
					break;
				case 200:
					this->m_sscore+=200;
					GoldCoin->InitCGoldCoin(this->m_hIns,(*it_Fish)->x,(*it_Fish)->y,200);
					break;
				case 500:
					this->m_sscore+=500;
					GoldCoin->InitCGoldCoin(this->m_hIns,(*it_Fish)->x,(*it_Fish)->y,500);
					break;
				case 1000:
					this->m_sscore+=1000;
					GoldCoin->InitCGoldCoin(this->m_hIns,(*it_Fish)->x,(*it_Fish)->y,1000);
					break;
				case 10000:
					this->m_sscore+=10000;
					GoldCoin->InitCGoldCoin(this->m_hIns,(*it_Fish)->x,(*it_Fish)->y,10000);
					break;
				}
				   
				this->m_lstNet.push_back(Net);
				
				n_flag=true;
				delete (*it_Bullet);
				it_Bullet=m_lstBullet.erase(it_Bullet);
				(*it_Fish)->DownBlood();
				if((*it_Fish)->IsDead())   
				{
					this->m_lstBeated.splice(this->m_lstBeated.end(),m_lstFish,it_Fish);
					///死了给金币
					this->m_lstGoldCoin.push_back(GoldCoin);
				}
				break;
			}
		
			++it_Fish;
		}
		if(false==n_flag)
		++it_Bullet;
		
	}


}
void CCaptureCtrl::ShowAllBeated(HDC hMemDC)
{
	list<CFish*>::iterator it_Beated= m_lstBeated.begin();  
	while(it_Beated!=m_lstBeated.end())
	{
		
		++it_Beated;	
	}

}

void CCaptureCtrl::ShowNet(HDC hMemDC)
{
	list<CNet*>::iterator it_Net= m_lstNet.begin();  
	while(it_Net!=m_lstNet.end())
	{
		(*it_Net)->ShowSingleNet(hMemDC);
		++it_Net;	
	}


}
void CCaptureCtrl::DeleteNet()
{
	list<CNet*>::iterator it_Net= m_lstNet.begin();  
	while(it_Net!=m_lstNet.end())
	{
		
		it_Net=m_lstNet.erase(it_Net);	
	
	}


}

void CCaptureCtrl::ShowScore(HDC hMemDC)
{
	LOGFONT logfont;//改变输出字体
	ZeroMemory(&logfont,sizeof(LOGFONT));
	logfont.lfCharSet=GB2312_CHARSET;
	logfont.lfHeight=50;
	HFONT hFont=CreateFontIndirect(&logfont);
	::SetTextColor(hMemDC,RGB(237,28,36));
	::SetBkColor(hMemDC,RGB(200,200,0));
	::SetBkMode(hMemDC,TRANSPARENT);
	::SelectObject(hMemDC,hFont);
	char *Grade=new char[100];
	 _itoa_s(this->m_sscore,Grade,100,10);
	 
		if(this->m_sscore>=999999999)
		{
			TextOut(hMemDC,87,15,"999999999",9);

	 
		}
		else if(this->m_sscore>=100000000)
		{
				if(1==this->Level.m_slevel_up)
				this->Level.m_slevel_up=2;
			TextOut(hMemDC,87,15,Grade,9);
			if(false==this->m_bflag_three)
			{

			this->Level.m_slevel_up=3;
			this->m_bflag_three=true;
			this->EndTimer();
			::MessageBox(this->m_hwnd,"Level Up!","提示",MB_OK); 
			this->BeginTimer();
			}
		}
		else if(this->m_sscore>=10000000)
		{
				if(1==this->Level.m_slevel_up)
				this->Level.m_slevel_up=2;
			TextOut(hMemDC,87,15,Grade,8);
	 
		}
		else if(this->m_sscore>=1000000)
		{
			if(1==this->Level.m_slevel_up)
				this->Level.m_slevel_up=2;
			TextOut(hMemDC,87,15,Grade,7);

		}
		else if(this->m_sscore>=100000)
		{
			
			TextOut(hMemDC,87,15,Grade,6);	
			if(false==this->m_bflag_two)
			{

			this->Level.m_slevel_up=2;
			
			this->m_bflag_two=true;
			this->EndTimer();
			::MessageBox(this->m_hwnd,"Level Up!","提示",MB_OK); 
			this->BeginTimer();
			
			}
		}
		 else if(this->m_sscore>=10000)
		{
			if(0==this->Level.m_slevel_up)
				this->Level.m_slevel_up=1;
			TextOut(hMemDC,87,15,Grade,5);
		}
		else if (this->m_sscore>=1000)
		{
			TextOut(hMemDC,87,15,Grade,4);
				if(false==this->m_bflag_one)///防止多个窗口弹出 
			{

			this->Level.m_slevel_up=1;
			this->m_bflag_one=true;			
			this->EndTimer();
			::MessageBox(this->m_hwnd,"Level Up!","提示",MB_OK); 
			this->BeginTimer();
			}
		}
		else if(this->m_sscore>=100)
		 {
			 TextOut(hMemDC,87,15,Grade,3);
		 }
		 else if(this->m_sscore>=10)
		 {
			  TextOut(hMemDC,87,15,Grade,2);
			  
		 }
		 else
		 {
			 TextOut(hMemDC,87,15,Grade,1);
		 }
		 delete Grade;
		 ::DeleteObject(hFont);

}

void CCaptureCtrl::ShowCoin(HDC hMemDC)
{
	list<CGoldCoin*>::iterator it_GoldCoin= m_lstGoldCoin.begin();  
	while(it_GoldCoin!=m_lstGoldCoin.end())
	{
		(*it_GoldCoin)->ShowGoldCoin(hMemDC);
		++it_GoldCoin;	
	}


}

void CCaptureCtrl::DeleteCoin()
{
	list<CGoldCoin*>::iterator it_GoldCoin= m_lstGoldCoin.begin();  
	while(it_GoldCoin!=m_lstGoldCoin.end())
	{
		
		it_GoldCoin=m_lstGoldCoin.erase(it_GoldCoin);	
	
	}


}

void CCaptureCtrl::BeginTimer()
{
	::SetTimer(m_hwnd,BULLET_MOVE_TIMER_ID,100,NULL);
	::SetTimer(m_hwnd,CREATE_FISH_TIMER_ID,2000,NULL);
	::SetTimer(m_hwnd,FISH_MOVE_TIMER_ID,100,NULL);
	::SetTimer(m_hwnd,DELETE_NET_TIMER_ID,2000,NULL);
	::SetTimer(m_hwnd,DELETE_COIN_TIMER_ID,6000,NULL);
}
void CCaptureCtrl::EndTimer()
{
	::KillTimer(m_hwnd,BULLET_MOVE_TIMER_ID);
	::KillTimer(m_hwnd,CREATE_FISH_TIMER_ID);
	::KillTimer(m_hwnd,FISH_MOVE_TIMER_ID);
	::KillTimer(m_hwnd,DELETE_NET_TIMER_ID);
	::KillTimer(m_hwnd,DELETE_COIN_TIMER_ID);

}