// MyDll.cpp: 定义 DLL 的初始化例程。
//#include "pch.h"

#include "pch.h"
#include "ScriptDialog.h"
#include "MyDll.h"
#include "Base.h"
#include "Hook.h"
#include "Package.h"

// CMyDllApp
BEGIN_MESSAGE_MAP(CMyDllApp, CWinApp)
END_MESSAGE_MAP()


CMyDllApp theApp;	//唯一的MFC对象
HHOOK Game_Hook;	//消息钩子
HANDLE Dll_Thread;	//线程句柄	-- 用于挂起 恢复


DWORD WINAPI HookGame(LPVOID lpData)
{
	//HWND hGameWnd = *(HWND*)((DWORD)GetModuleHandle(_T("UI_CEGUI.dll")) + 0x55CC8);	//获取窗口句柄
	DWORD ndThreadID = GetWindowThreadProcessId( Game::Game_hGameWnd, NULL);	//获取进程的标识符
	Game_Hook = SetWindowsHookEx(WH_CALLWNDPROC, GameWndProc, NULL, ndThreadID);

	if (Game_Hook)
	{
		DebugMessage("安装Hook成功,等待执行功能");
	}

	SuspendThread(Dll_Thread);	//将线程挂起

	if (UnhookWindowsHookEx(Game_Hook))
	{
		DebugMessage("卸载消息钩子成功");
	}

	if (theApp.m_hInstance)
	{
		DebugMessage("卸载成功");
		FreeLibraryAndExitThread(theApp.m_hInstance, 1);//结束DLL和线程/1.DLL句柄2.返回码exitcode//thapp当前程序的句柄，是dll的句柄
	}

	return TRUE;

};



DWORD WINAPI ShowDialog(LPVOID lpData)
{
	ScriptDialog* dlg;
	dlg = new ScriptDialog;
	dlg->DoModal();
	delete dlg;
	FreeLibraryAndExitThread(theApp.m_hInstance, 1);//结束DLL和线程/1.DLL句柄2.返回码exitcode//thapp当前程序的句柄，是dll的句柄
	return TRUE;
};


// CMyDllApp 初始化
BOOL CMyDllApp::InitInstance()
{
	CWinApp::InitInstance();
	DebugMessage("注入DLL成功");
	//Dll_Thread = ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HookGame, NULL, NULL, NULL);
	::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ShowDialog, NULL, NULL, NULL);
	return TRUE;	//结束进程后,接着消息循环
}
