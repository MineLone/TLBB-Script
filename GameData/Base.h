#pragma once

extern DWORD Pid;	//Game.exe����id
extern DWORD GameWindowHandle;	//Game���ھ��




//extern int GetGameWindowHandle();

class Game
{
private:

public:
	static DWORD Game_ModuleHandl;	//Game.exeģ����
	static DWORD UI_ModuleHandl;	//ui_cegui.dllģ����
	static HWND Game_hGameWnd;	//���ھ��
	static DWORD InquireNPC;	//NPC�Ի���ַ
	static DWORD LuaPlusHandl ;	//luaplus.dllģ����
	static DWORD Game_LuaHandl;	//ģ���ַ
	static DWORD Game_LuaDoString ;	//Lua_DoString ��ַ
	static DWORD Game_Mian_Window;	//��Ϸ�����ھ����ַ
	static DWORD Game_Player_ModuleHandl;	//�����ַ
	static DWORD Game_Pet_Backpack;	//���ﱳ����ַ
	static DWORD Game_Map_ModuleHandl;	//��ͼ��ַ

public:
	Game();
	~Game();
};


class Player :public Game
{

private:


public:
	bool* Model;	//��ɫģ��	--- ָ������ 1��ʾ 0����	
	CString Map;	//��ǰ��ͼ
	float X;	//X����
	float Y;	//Y����
	DWORD Player_Base;	//�������Խṹ��ַ
	CString Name;	//��ɫ����
	int Hp;	//Ѫ
	int Hp_Max;	//Ѫ����
	int Mp;	//��
	int Mp_Max;	//������
	int Rage;	//ŭ��
	int Level;	//�ȼ�
	int Exp;	//����ֵ
	int YB_Bind;	//��Ԫ��
	int GangID;	//����ID
	CString GangName;	//��������
	DWORD Pet_State;//��ǰ��ս�����id

public:
	//static void GetPlayerData();
	//static CString GetName();


public:
	Player();
	~Player();

};