#pragma once

extern DWORD Pid;	//Game.exe进程id
extern DWORD GameWindowHandle;	//Game窗口句柄




//extern int GetGameWindowHandle();

class Game
{
private:

public:
	static DWORD Game_ModuleHandl;	//Game.exe模块句柄
	static DWORD UI_ModuleHandl;	//ui_cegui.dll模块句柄
	static HWND Game_hGameWnd;	//窗口句柄
	static DWORD InquireNPC;	//NPC对话基址
	static DWORD LuaPlusHandl ;	//luaplus.dll模块句柄
	static DWORD Game_LuaHandl;	//模块基址
	static DWORD Game_LuaDoString ;	//Lua_DoString 地址
	static DWORD Game_Mian_Window;	//游戏主窗口句柄基址
	static DWORD Game_Player_ModuleHandl;	//人物基址
	static DWORD Game_Pet_Backpack;	//宠物背包基址
	static DWORD Game_Map_ModuleHandl;	//地图基址

public:
	Game();
	~Game();
};


class Player :public Game
{

private:


public:
	bool* Model;	//角色模型	--- 指针类型 1显示 0隐藏	
	CString Map;	//当前地图
	float X;	//X坐标
	float Y;	//Y坐标
	DWORD Player_Base;	//人物属性结构地址
	CString Name;	//角色名字
	int Hp;	//血
	int Hp_Max;	//血上限
	int Mp;	//蓝
	int Mp_Max;	//蓝上限
	int Rage;	//怒气
	int Level;	//等级
	int Exp;	//经验值
	int YB_Bind;	//绑定元宝
	int GangID;	//帮派ID
	CString GangName;	//帮派名称
	DWORD Pet_State;//当前出战宠物的id

public:
	//static void GetPlayerData();
	//static CString GetName();


public:
	Player();
	~Player();

};