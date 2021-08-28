#include "pch.h"
#include "Base.h"
#include "Package.h"

//字符串为CString类型
CString to_cStr(BYTE Bool)
{
	CString cStr;
	cStr.Format("%d", Bool);
	return cStr;
};
CString to_cStr(INT INT)
{
	CString cStr;
	cStr.Format("%d", INT);
	return cStr;
};
CString to_cStr(FLOAT Float)
{
	CString cStr;
	cStr.Format("%.0F", Float);
	return cStr;
};
CString to_cStr(DWORD Dword)
{
	CString cStr;
	cStr.Format("%.8X", Dword);
	return cStr;
};
CString to_cStr(CString cStr)
{
	return cStr;
};

//基础LuaCall
void __stdcall LuaCall(char* LuaString)
{
	int LuaAdd;
	LuaAdd = *(int*)Game::Game_LuaHandl;
	int lua_dostr;
	lua_dostr = Game::Game_LuaDoString;
	_asm
	{
		mov ecx, LuaAdd;
		mov eax, dword ptr ds : [ecx] ;
		call dword ptr ds : [eax + 0x3C] ;
		push LuaString;
		push dword ptr ds : [eax] ;
		call lua_dostr;
		add esp, 0x8;
	}
}
//公告
void DebugMessage(CString str)
{
	CString cbuff;
	cbuff = "PushDebugMessage(\"" + str + "\");";
	char* buff;
	buff = cbuff.GetBuffer();
	LuaCall(buff);
}
//本地图寻路
void GoTo(int x,int y)
{
	CString cbuff;
	cbuff.Format("AutoRunToTarget(%d,%d);", x, y);
	char* buff;
	buff = cbuff.GetBuffer();
	LuaCall(buff);
}
//跨地图寻路
void GoTo(int x, int y,int city)
{
	CString cbuff;
	cbuff.Format("AutoRunToTargetEx(%d,%d,%d);", x, y,city);
	char* buff;
	buff = cbuff.GetBuffer();
	LuaCall(buff);
}
//领取活跃
void Get_Active(int value)
{
	CString cbuff;
	cbuff.Format("ZhouHuoYue_GetZhouHuoYueAddHuoYueZhi(%d);", value);
	char* buff;
	buff = cbuff.GetBuffer();
	LuaCall(buff);
}
//领取活跃奖励
void Get_Active_Award()
{
	CString cbuff;
	cbuff.Format("ZhouHuoYue_GetAwardClick();");
	char* buff;
	buff = cbuff.GetBuffer();
	LuaCall(buff);
}
//对话Call
void __stdcall InquireNPC(int NPC_ID)
{
	int LuaAdd;
	LuaAdd = *(int*)Game::InquireNPC;
	_asm 
	{
		mov ecx, LuaAdd;
		push 0x0;
		mov eax, dword ptr ds : [ecx] ;
		push NPC_ID;
		call dword ptr ds : [eax + 0x3C] ;
		mov ecx, dword ptr ds : LuaAdd;
		push NPC_ID;
		mov eax, dword ptr ds : [ecx] ;
		call dword ptr ds : [eax + 0x7C] ;
	}


}


