

#include "pch.h"
#include "Package.h"
#include "Thread.h"



//һ����ȡ��Ծ����
//UINT __cdecl Pack_Get_Active_Award(LPVOID pParam) 
//{
//	for (int i = 0; i < 53; i++)
//	{
//		Get_Active(i);
//		Sleep(300);
//	}
//	Get_Active_Award();
//	//DebugMessage("��ȡ��Ծ����");
//	return 0;
//}
// 
//һ����ȡ��Ծ����
unsigned int _stdcall Pack_Get_Active_Award(PVOID LPDATA)
{
	for (int i = 0; i < 53; i++)
	{
		Get_Active(i);
		Sleep(400);
	}
	Get_Active_Award();
	//DebugMessage("��ȡ��Ծ����");
	return 0;
}
