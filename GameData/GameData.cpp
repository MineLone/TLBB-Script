// GameData.cpp : 定义静态库的函数。
//

//#ifndef _PCH_H
//#define _PCH_H
//#include "pch.h"
//#endif //PCH_H
//#ifndef _GAMEDATA_H
//#define _GAMEDATA_H
//#include "GameData.h"
//#endif
//#include <string>
//
//DWORD Game_ModuleHandl = (DWORD)GetModuleHandleA("Game.exe");	//获取模块句柄
//DWORD Game_LuaHandl = Game_ModuleHandl + 0x37F25C;//模块基址
//DWORD Game_Mian_Window = Game_ModuleHandl + 0x3776D0;	//游戏主窗口句柄基址
//DWORD Game_Map_ModuleHandl = Game_ModuleHandl + 0x37E6D0;	//地图基址
//DWORD Game_Player_ModuleHandl = Game_ModuleHandl + 0x37E6D4;	//人物基址
//
////线程句柄声明
//HANDLE Game_OverSee = NULL;	//全程监视线程句柄
//
//
//
////获取游戏主窗口句柄
//HWND GetGameWndHANDLE()
//{
//	HWND hGameWnd = NULL;
//	__try
//	{
//		hGameWnd = *(HWND*)Game_Mian_Window;
//	}
//	_except(1)
//	{
//		OutputDebugStringW(L"MSG:获取游戏主窗口异常");//发送调试信息
//		return NULL;
//	}
//	return hGameWnd;
//}



//DWORD WINAPI ThreadProc(LPVOID pM)
//{
//	//printf("子线程的线程ID号为：%d\n子线程输出Hello World\n", GetCurrentThreadId());
//	while (TRUE)
//	{
//		//定义一个指针变量
//
//		bool* pMod;
//		//int tmpBase;
//		////CString Map;
//
//		////(char*)Get_address(Game_Map_ModuleHandl, 0x55e8, 0x58)
//		//tmpBase = *(int*)Game_Player_ModuleHandl + 0x55e8;
//		//tmpBase = *(int*)tmpBase + 58;	//地图
//		//Map = (char*)tmpBase;
//
//		//if ( Map == L"洛阳" )
//		//{
//		pMod = (bool*)((int*)Game_Player_ModuleHandl + 0x29);
//
//		if (*pMod)
//		{
//			*pMod = 0;
//		}
//
//		//}
//		pMod = NULL;
//		Sleep(1000);
//	}
//	return 0;
//}

//控制线程
//void Open_OverSee_Thread()		//开启信息全局监控线程
//{
//	//g_自身血量检测开关 = 1;
//	//Game_OverSee = (HANDLE)CreateThread(NULL, NULL, Oversee_Info, NULL, NULL, NULL);
//	if (Game_OverSee == 0)
//	{
//		Game_OverSee = CreateThread(NULL, NULL, ThreadProc, 0, 0, NULL);
//		//MessageBox(NULL, L"", L"", 0);
//	}
//
//	//if (Game_OverSee)
//	//{
//	//	//MessageBox(NULL, L"提示", L"创建线程成功", 0);
//	//}
//};

//void Close_OverSee_Thread()	//关闭信息全局监控线程
//{
//	//WaitForSingleObject();
//	//_endthreadex((uintptr_t)Game_OverSee);
//	if (Game_OverSee != 0)
//	{
//		MessageBox(NULL, L"", L"", 0);
//		SuspendThread(Game_OverSee);//先暂停
//		CloseHandle(Game_OverSee);//后关闭
//	}
//
//};

//unsigned INT _stdcall Oversee_Info(PVOID LPDATA)
//{
//	//DWORD tmpBase = *(DWORD*)(BASEROLE);
//	//tmpBase = *(DWORD*)(tmpBase + 0x54);
//	//tmpBase = *(DWORD*)(tmpBase + 0x1A0);
//	//tmpBase = *(DWORD*)(tmpBase + 0x4);
//
//	//循环检测血量
//	while (TRUE)
//	{
//		//if (Global_AutoPlay.自动吃药变量 == 1)
//		//{
//		//	DWORD 当前血量 = *(DWORD*)(tmpBase + 0x2d00);
//
//		//	DWORD nIndex = Global_AutoPlay.chiyaoIndex;
//
//		//	if (当前血量 <= Global_AutoPlay.吃药阈值 && 当前血量 > 0)//按键吃药
//		//	{
//		//		Global_Role.ANJIAN(nIndex);
//		//		DEBGPrintf("使用了药品");
//		//	}
//
//		//	if (当前血量 == 0)
//		//	{
//		//		Global_AutoPlay.StopAutoPlay();//挂起打怪线程
//		//		Global_AutoPlay.StopEATHP();//挂起吃药线程
//		//	}
//
//		//	Sleep(1000);
//		//}
//
//
//		//My_Text = /*to_cStr(Player.Map) + */ L" ( " + to_cStr(Player.xAxis) + L" , " + to_cStr(Player.yAxis) + L" ) ";
//		//My_Text = to_cStr( (INT)Player->Game_ModuleHandl );
//
//		//if (to_cStr(Player.Map) == L"洛阳" | to_cStr(Player.Map) == L"苏州" | to_cStr(Player.Map) == L"大理" | to_cStr(Player.Map) == L"楼兰")
//		//{
//		//	//My_Text = L"洛阳";
//		//	//在城市--隐藏模型
//		//	if (*(Player.Model) == 1)
//		//	{
//		//		*Player.Model = 0;
//		//	}
//
//		//}
//
//
//		//if (Global_AutoPlay.释放吃药线程 == 1)
//		//{
//		//	break;
//		//}
//		/*My_Text*/
//		Sleep(1000);
//	}
//	return 0;
//}



//构造函数 创建类对象的时候执行
//GameData::GameData()
//{
//
//}
/*
void GameData::to_date()
{

	//Map = (char*)Get_address(Game_Map_ModuleHandl, 0x55e8, 0x58);	//当前地图
	//Model = (bool*)Get_address(Game_Player_ModuleHandl, 0x29);	//角色模型	---  1显示 0隐藏

	//Name = (char*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0x2c);	//角色名字
	//xAxis = *(float*)Get_address(Game_Player_ModuleHandl, 0x58, 0x54);	//x坐标
	//yAxis = *(float*)Get_address(Game_Player_ModuleHandl, 0x58, 0x44);	//y坐标
	//Hp = *(int*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144,0x4,0x237c);	//血
	//HpMax = *(int*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0x23e8);	//血上限
	//Mp = *(int*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0x2380);	//蓝
	//MpMax = *(int*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0x23ec);	//蓝上限
	//Rage = *(int*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0x5c);	//怒气
	//Level = *(int*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0x58);	//等级
	//Exp = *(int*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0x2384);	//经验值
	//YB_Bind = *(int*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0x24c4);	//绑定元宝
	//GangID = *(int*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0xa8);	//帮派ID
	//GangName = (char*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0x221c);	//帮派名称
	//Pet_Name;	//当前出战宠物的名字
	//Pet_State = *(int*)Get_address(Game_Player_ModuleHandl, 0x58, 0x144, 0x4, 0x23bc);;	//当前出战宠物的id

}
*/

//析构函数 删除类对象的时候执行
//GameData::~GameData()
//{
//	//Model = NULL;	//角色模型	---  1显示 0隐藏	获取的是地址
//	//delete Model;	//角色模型	---  1显示 0隐藏	获取的是地址
//	////Model_Name;	//角色名字
//	//delete Name;	//角色名字	--字符串地址
//	//Map = NULL;	//角色所在地图
//	////delete xAxis;	//x坐标
//	////delete yAxis;	//y坐标
//	//Hp;	//血
//	//HpMax;	//血上限
//	//Mp;	//蓝
//	//MpMax;	//蓝上限
//	//Rage;	//怒气
//	//Level;	//等级
//	//Exp;	//经验值
//	//YB_Bind;	//绑定元宝
//	//GangID;	//帮派ID
//	//delete GangName;	//帮派名称
//	//delete Pet_Name;	//当前出战宠物的名字
//	//Pet_State;	//当前出战宠物的id
//}

