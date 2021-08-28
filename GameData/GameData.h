//#pragma once
//#include <windows.h>
//
//extern DWORD Game_ModuleHandl;//模块基址
//extern DWORD Game_LuaHandl;//模块基址
//extern DWORD Game_Map_ModuleHandl;//人物怪物基址
//extern DWORD Game_Mian_Window;	//游戏主窗口句柄基址
//extern DWORD Game_Player_ModuleHandl;	//地图基址
//
////全局句柄声明
//extern HWND GetGameWndHANDLE();//获取游戏主窗口句柄
//
////控制线程声明
//extern void Open_OverSee_Thread();		//开启信息全局监控线程
//extern void Close_OverSee_Thread();	//关闭信息全局监控线程

//unsigned int _stdcall Oversee_Info(PVOID LPDATA); //线程回调
/*

//字符串转换
extern CString to_cStr(BYTE Bool);
extern CString to_cStr(INT Int);
extern CString to_cStr(INT* Stradd);
extern CString to_cStr(FLOAT Float);
extern CString to_cStr(FLOAT* Float);
extern CString to_cStr(CString cStr);
//获取内存地址
extern int Get_address(DWORD Base_Address, INT Offset1);
extern int Get_address(DWORD Base_Address, INT Offset1, INT Offset2);
extern int Get_address(DWORD Base_Address, INT Offset1, INT Offset2, INT Offset3);
extern int Get_address(DWORD Base_Address, INT Offset1, INT Offset2, INT Offset3, INT Offset4);
extern int Get_address(DWORD Base_Address, INT Offset1, INT Offset2, INT Offset3, INT Offset4, INT Offset5);

*/

//class GameData
//{
//private:
//
//public:
//	
//	bool *Model;	//角色模型	---  1显示 0隐藏	获取的是地址
//	//CString Model_Name;	//角色名字
//	//CString Name;	//角色名字	--字符串地址
//	CString Map;	//角色所在地图
//	float xAxis;	//x坐标
//	float yAxis;	//y坐标
//	//int Hp;	//血
//	//int HpMax;	//血上限
//	//int Mp;	//蓝
//	//int MpMax;	//蓝上限
//	//int Rage;	//怒气
//	//int Level;	//等级
//	//int Exp;	//经验值
//	//int YB_Bind;	//绑定元宝
//	//int GangID;	//帮派ID
//	//CString GangName;	//帮派名称
//	//CString Pet_Name;	//当前出战宠物的名字
//	//int Pet_State;	//当前出战宠物的id
//
//public:
//
//	//DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter);
//
//	//HANDLE CreateThread
//	//void to_date();
//
//	GameData();	//构造函数	-- 初始化类数据
//	~GameData();//析构函数 -- 结束时触发
//};



