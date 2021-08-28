#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif


class CMyDllApp : public CWinApp
{
public:


public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};


extern CMyDllApp theApp;	//唯一的MFC对象
extern HHOOK Game_Hook;	//消息钩子
extern HANDLE Dll_Thread;	//线程句柄	-- 用于挂起 恢复