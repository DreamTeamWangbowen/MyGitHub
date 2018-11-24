#ifndef INET_H
#define INET_H

#include <Winsock2.h>
#include "Packdef.h"

#pragma comment(lib,"Ws2_32.lib")
class INet
{
public:
	INet(){}
	virtual ~INet(){}
public:
	virtual bool InitNetWork() = 0;
	virtual void UnInitNetWork() = 0;
	virtual bool SendData(long lSendIp, char *szbuf,int nlen) = 0;
public:
	static long GetValidIp()
	{
		//1.获得本机名称
		char szName[100] = {0};
		in_addr addr;
		if(!gethostname(szName,sizeof(szName)))
		{
				//2.获得本机的iplist
			 hostent* remoteHost = gethostbyname(szName);
			 if (remoteHost->h_addr_list[0] != 0) 
			 {
                addr.s_addr = *(u_long *) remoteHost->h_addr_list[0];
               
            }


		}
	

		 return addr.s_addr;
	}
};





#endif