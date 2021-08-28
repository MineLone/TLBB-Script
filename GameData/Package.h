#pragma once

//字符串转换
extern CString to_cStr(BYTE Bool);
extern CString to_cStr(INT Int);
extern CString to_cStr(FLOAT Float);
extern CString to_cStr(DWORD Dword);
extern CString to_cStr(CString cStr);

//调用lua
extern void __stdcall LuaCall(char* LuaString);//基础LuaCall
extern void DebugMessage(CString str);//发送公告
 
 //自动寻路
extern void GoTo(int x, int y);//本地图寻路
extern void GoTo(int x, int y, int city);//跨地图寻路	-- 城市对应的数值
 
 //活跃
extern void Get_Active(int value); //领取活跃值
extern void Get_Active_Award(); //领取活跃奖励
//extern void Pack_Get_Active_Award();//一键领取

extern void __stdcall InquireNPC(int NPC_ID);	//NPC对话--打开面板