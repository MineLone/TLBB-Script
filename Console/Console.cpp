#include "pch.h"
#include "resource.h"		// 主符号
#include "Console.h"
#include "ConsoleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(ConsoleApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

ConsoleApp::ConsoleApp()
{
}

ConsoleApp theApp;	// 唯一的 ConsoleApp 对象

// ConsoleApp 初始化
BOOL ConsoleApp::InitInstance()
{
	WNDCLASS Console;
	// 获取窗口类信息。MFC默认的所有对话框的窗口类名为 #32770
	::GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &Console);
	// 改变窗口类名
	Console.lpszClassName = _T("Script Console");
	// 注册新窗口类，使程序能使用它
	AfxRegisterClass(&Console);

	CWinApp::InitInstance();

	CConsoleDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return FALSE;	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
}

