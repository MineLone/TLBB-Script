#pragma once
//进程间通讯发送的消息类型


//消息进行验证
#define Msg_wParam		9523


// 消息类型
#define	Msg_退出		999		//退出线程

#define	Msg_Debug		001		//Debug消息
#define	Msg_LuaCall		002		//Lua字符串消息
#define	Msg_领取活跃	003		//Lua字符串消息
#define Msg_NPC对话		004		//NPC打开面板

