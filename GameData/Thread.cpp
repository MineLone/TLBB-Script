

#include "pch.h"
#include "Package.h"
#include "Thread.h"



//一键领取活跃功能
//UINT __cdecl Pack_Get_Active_Award(LPVOID pParam) 
//{
//	for (int i = 0; i < 53; i++)
//	{
//		Get_Active(i);
//		Sleep(300);
//	}
//	Get_Active_Award();
//	//DebugMessage("领取活跃结束");
//	return 0;
//}
// 
//一键领取活跃功能
unsigned int _stdcall Pack_Get_Active_Award(PVOID LPDATA)
{
	for (int i = 0; i < 53; i++)
	{
		Get_Active(i);
		Sleep(400);
	}
	Get_Active_Award();
	//DebugMessage("领取活跃结束");
	return 0;
}
