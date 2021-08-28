// ScriptDialog.cpp: 实现文件
#pragma once


#include "pch.h"
//#include "GameHook.h"
#include "Base.h"
#include "Package.h"
#include "Thread.h"
#include "MyDll.h"
#include "ScriptDialog.h"

#include <vector>
#include <TlHelp32.h>
#include <GameProcess.h>

using namespace std;
//string a = to_string(int);
//CString cStr = a.c_str();

//输出调试信息--在DebugView软件里面看调试信息 
//#define OUTINFO_1_PARAM(fmt, var) { CString str;str.Format(_T("%d"),var); CString buff = ( L"MSG:" + fmt ) ;OutputDebugStringW( buff + str); }
//#define OUTINFO_2_PARAM(fmt, var1, var2) { CHAR sOut[256]; CHAR sfmt[50]; sprintf_s(sfmt, "%s%s", "MSG:", fmt); sprintf_s(sOut, (sfmt), var1, var2); OutputDebugStringW(sOut); }
//#define OUTINFO_3_PARAM(fmt, var1, var2, var3) { CHAR sOut[256]; CHAR sfmt[50]; sprintf_s(sfmt, "%s%s", "MSG:", fmt); sprintf_s(sOut, (sfmt), var1, var2, var3); OutputDebugStringW(sOut);}


//00E6862A | 8B0D A402FE00 | mov ecx, dword ptr ds : [0xFE02A4] | lua
//void ScriptDialog::LuaCall( char* LuaString ) 
//{
//	//Game_LuaHandl
//	_asm
//	{
//		mov ecx, dword ptr ds : [0xFE02A4] ;
//		mov eax, dword ptr ds : [ecx] ;
//		call dword ptr ds : [eax + 0x3C] ;
//		push LuaString;
//		push dword ptr ds : [eax] ;
//		CALL DWORD PTR DS:[0x00F031A8];
//		add esp, 0x8;
//	}
//
//}

//GameData Player;

// ScriptDialog 对话框
IMPLEMENT_DYNAMIC(ScriptDialog, CDialogEx)

//创建类对象触发	构造函数
ScriptDialog::ScriptDialog( CWnd* pParent /*=nullptr*/): 
	CDialogEx(IDD_ScriptDialog, pParent)
	, My_Text(_T(""))
	, LuaString(_T(""))
{
	//HookMainThread();
	//OutputDebugStringW(L"MSG:创建类对象");//发送调试信息
}

//摧毁类对象触发	析构函数
ScriptDialog::~ScriptDialog()
{
	//delete Player;
	//MessageBox(L"0");
	//UnHookMainThread();
	//OutputDebugStringW(L"MSG:摧毁类对象");//发送调试信息
}

//bool bIsRunning;
//CWinThread* MyThread;	//创建线程
/*
UINT __cdecl MyFunction(LPVOID pParam)
{
	OutputDebugStringW(L"MSG:线程成功运行");//发送调试信息
	while ( bIsRunning )
	{
		CString Text;
		int tmpBase = *(int*)(Game_Map_ModuleHandl);	//地图基址
		tmpBase = *(int*)(tmpBase + 0x55e8);
		Text = (char*)(tmpBase + 0x58);
		//OUTINFO_1_PARAM(L"MSG:当前地图位置:",tmpBase);//发送调试信息
		tmpBase = *(int*)(Game_Player_ModuleHandl);	//人物基址
		bool* p = (bool*)(tmpBase + 0x29);
		Sleep(2000);
		OutputDebugStringW(L"MSG:" + Text);//发送调试信息
		if (Text == L"苏州")
		{
			if ( *p )
			{
				*p = 0;
			}
			continue;
		}
		if (Text == L"楼兰")
		{
			if (*p)
			{
				*p = 0;
			}
			continue;
		}
		if (Text == L"洛阳")
		{

			if (*p)
			{
				*p = 0;
			}
			continue;
		}
		if (Text == L"大理")
		{
			if (*p){*p = 0;}
			continue;
		}

	}
	return TRUE;
}
*/
BOOL ScriptDialog::OnInitDialog()//初始化窗口调用
{
	CDialogEx::OnInitDialog();
	DebugMessage("加载成功");
	//try
	//{
	//	//DWORD Game_ModuleHandl = (DWORD)GetModuleHandleA("Game.exe");	//获取模块句柄
	//	//DWORD Game_Mian_Window = Game_ModuleHandl + 0x3776D0;	//游戏主窗口句柄基址
	//	//DWORD Game_Map_ModuleHandl = Game_ModuleHandl + 0x37E6D0;	//地图基址
	//	//DWORD Game_Player_ModuleHandl = Game_ModuleHandl + 0x37E6D4;	//人物基址
	//	//OutputDebugStringW(L"获取基址");//发送调试信息
	//}
	//catch (const std::exception&)
	//{
	//	//OutputDebugStringW(L"MSG:获取模块句柄失败");//发送调试信息
	//}

	////OutputDebugStringW(L"MSG:初始化窗口");//发送调试信息

	////bIsRunning = TRUE;
	////MyThread = AfxBeginThread(MyFunction, this);	//线程

	////SetTimer(1, 1000, NULL); //时钟控件
	////GameData Player;
	return TRUE;  // return TRUE unless you set the focus to a control
}

//MFC控件
void ScriptDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT, My_Text);
	DDX_Control(pDX, IDC_TEXT_EDIT, My_Edit);
	DDX_Text(pDX, IDC_Lua_Edit, LuaString);
}

//MFC消息映射
BEGIN_MESSAGE_MAP(ScriptDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ScriptDialog::OnBnClickedButton1)
//	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &ScriptDialog::OnBnClickedButton2)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &ScriptDialog::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ScriptDialog::OnBnClickedButton4)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()

//MFC计时器
void ScriptDialog::OnTimer(UINT_PTR nIDEvent)
{
	/*
	
	OutputDebugStringW(L"MSG:计时器消息");//发送调试信息
	try
	{
		int tmpBase = *(int*)(Game_Map_ModuleHandl);
		//OUTINFO_1_PARAM(L"MSG:当前地图位置:",tmpBase);//发送调试信息
		tmpBase = *(int*)(tmpBase + 0x55e8);
		//OUTINFO_1_PARAM(L"MSG:当前地图位置:",tmpBase);//发送调试信息
		My_Text = (char*)(tmpBase + 0x58);

		tmpBase = *(int*)(Game_Player_ModuleHandl);
		
		if (My_Text == L"苏州")
		{
			*(bool*)(tmpBase + 0x58) = 0;
			//OutputDebugStringW(L"MSG:在洛阳" + My_Text);//发送调试信息
			OutputDebugStringW(My_Text);//发送调试信息
			return;
		}
		if (My_Text == L"楼兰")
		{
			*(bool*)(tmpBase + 0x58) = 0;
			//OutputDebugStringW(L"MSG:在洛阳" + My_Text);//发送调试信息
			OutputDebugStringW(My_Text);//发送调试信息
			return;
		}
		if (My_Text == L"洛阳")
		{

			*(bool*)(tmpBase + 0x58) = 0;
			OutputDebugStringW(My_Text);//发送调试信息
			return;
		}
		if (My_Text == L"大理")
		{
			*(bool*)(tmpBase + 0x58) = 0;
			//OutputDebugStringW(L"MSG:在洛阳" + My_Text);//发送调试信息
			OutputDebugStringW(My_Text);//发送调试信息
			return;
		}


		//OutputDebugStringW(L"MSG:当前地图位置:" + My_Text );//发送调试信息
	}
	catch (const std::exception&)
	{
		OutputDebugStringW(L"MSG:获取地图失败");//发送调试信息
	}
	*/
	//My_Text = to_cStr(*(Player.Model));
	//My_Text = to_cStr(*(Player.Model));
	//My_Text = to_cStr(Player.Map);
	//My_Text = to_cStr(Player.Map);
	//My_Text = to_cStr(Player.Map);

	//Player->to_date();

	//My_Text = /*to_cStr(Player.Map) + */ L" ( " + to_cStr(Player.xAxis) + L" , " + to_cStr(Player.yAxis) + L" ) ";
	//My_Text = to_cStr( (int)Player->Game_ModuleHandl );

	//if (*(Player.Model) == 1)
	//{
	//	if (to_cStr(Player.Map) == L"洛阳" | to_cStr(Player.Map) == L"苏州" | to_cStr(Player.Map) == L"楼兰" | to_cStr(Player.Map) == L"大理"  )
	//	{
	//		//My_Text = L"洛阳";
	//		//在城市--隐藏模型
	//		if (*(Player.Model) == 1)
	//		{
	//			*Player.Model = 0;
	//		}
	//	}
	//}


	//My_Text = to_cStr(*(Player.Model));
	//a++;

	//My_Text = to_cStr(a);

	CDialogEx::OnTimer(nIDEvent);
}

//窗口销毁触发的消息
void ScriptDialog::OnDestroy()
{
	//bIsRunning = FALSE;
	//MyThread
	//delete Player;
	//KillTimer(1);
	//OutputDebugStringW(L"MSG:窗口即将关闭");//发送调试信息
}

// ScriptDialog 消息处理程序
void ScriptDialog::OnBnClickedButton1()
{

	UpdateData(true);

	//DebugMessage(LuaString);
	//int value;
	//value = 5;

	//CString cbuff;
	//cbuff.Format("ZhouHuoYue_GetZhouHuoYueAddHuoYueZhi(%d);", value);


	//My_Text.Format("ZhouHuoYue_GetZhouHuoYueAddHuoYueZhi(%d);", value);

	//DebugMessage(My_Text);
	//AfxBeginThread(Pack_Get_Active_Award, this);
	//Pack_Get_Active_Award();

	UpdateData(false);


	//FLOAT x;
	//x = *(float*)Get_address(Game_Player_ModuleHandl, 0x58, 0x54);	//x坐标
	// 
	//string a;
	//a = to_string(Player.xAxis);

	//My_Text = to_cStr(Player.xAxis);

	//My_Edit.setText()
	//	+ to_cStr(Player.xAxis) + L"\r\n"
	//	+ to_cStr(Player.yAxis) + L"\r\n"
	//	+ to_cStr(Player.yAxis) + L"\r\n"
	//	+ to_cStr(Player.Hp) + L"\r\n"
	//	+ to_cStr(Player.HpMax) + L"\r\n"
	//	+ to_cStr(Player.Mp) + L"\r\n"
	//	+ to_cStr(Player.MpMax) + L"\r\n"
	//	+ to_cStr(Player.Rage) + L"\r\n"
	//	+ to_cStr(Player.Level) + L"\r\n"
	//	+ to_cStr(Player.Exp) + L"\r\n"
	//	+ to_cStr(Player.YB_Bind) + L"\r\n"
	//	+ to_cStr(Player.GangID) + L"\r\n"
	//	+ to_cStr(Player.GangName) + L"\r\n"
	//	+ to_cStr(Player.Pet_State) + L"\r\n";

	//My_Text = Player.Name;

	//((CEdit*)GetDlgItem(IDC_TEXT_EDIT))->SetSel(GetDlgItem(IDC_TEXT_EDIT)->GetWindowTextLength(), GetDlgItem(IDC_TEXT_EDIT)->GetWindowTextLength());
	//((CEdit*)GetDlgItem(IDC_TEXT_EDIT))->ReplaceSel(
	//	to_cStr(Player.xAxis) + L"\r\n"
	//	+ to_cStr(Player.yAxis) + L"\r\n"
	//	+ to_cStr(Player.Hp) + L"\r\n"
	//	+ to_cStr(Player.HpMax) + L"\r\n"
	//	+ to_cStr(Player.Mp) + L"\r\n"
	//	+ to_cStr(Player.MpMax) + L"\r\n"
	//	+ to_cStr(Player.Rage) + L"\r\n"
	//	+ to_cStr(Player.Level) + L"\r\n"
	//	+ to_cStr(Player.Exp) + L"\r\n"
	//	+ to_cStr(Player.YB_Bind) + L"\r\n"
	//	+ to_cStr(Player.GangID) + L"\r\n"
	//	+ to_cStr(Player.GangName) + L"\r\n"
	//	+ to_cStr(Player.Pet_State) + L"\r\n"
	//);

	//::SendMessageA(GetGameWndHANDLE(), MyMSGCode, MSG_人物血量检测, NULL);
	//Global_AutoPlay.handle_血量控制线程 = (HANDLE)_beginthreadex(NULL, NULL, 血量控制线程, NULL, NULL, NULL);
	//Open_Oversee_Thread();

	//OutputDebugStringW(L"asd");//发送调试信息

	//Open_OverSee_Thread();
	//INT16 a = Game_LuaHandl;

	//My_Text.Format(L"%x", Game_LuaHandl);

	//UpdateData(false);	//传递 false
}

void ScriptDialog::OnBnClickedButton2()
{
	//Close_OverSee_Thread();
	UpdateData(true);	//传递 false


	//DWORD Lua = (DWORD)Game::Game_LuaHandl;
	if (LuaString != "" )
	{
		char* LuaName = LuaString.GetBuffer();
		::LuaCall(LuaName);
		//My_Text.Format("%d", Lua);
	}
	else
	{
		DebugMessage("请输入lua指令");
	}
	//DWORD Lua = (DWORD)Game::Game_LuaHandl;
	
	//My_Text.Format("%x", Lua);

	UpdateData(false);	//传递 false

}


//CWinThread* MyThread = AfxBeginThread(MyThreadFunction, pParam, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

//UINT MyThreadFunction(LPVOID pParam)
//
//{
//
//	//函数体
//
//	return 0;
//
//}

//DWORD asd


void ScriptDialog::OnBnClickedButton3()
{
	UpdateData(true);

	//if (!GameInitialization())
	//{
	//	MessageBox("初始化失败");
	//	return;
	//}

	int start = clock();

	CString debug;

	debug.Format("窗口句柄为 : %X", GameWindowHandle);

	int end = clock();

	DebugMessage(debug.GetBuffer());

	debug.Format("用时：%d 毫秒", end - start);

	DebugMessage(debug.GetBuffer());
	

	//std::cout << "用时：" << end - start << "毫秒" << endl;


	//DWORD ce;
	//ce = (DWORD)GetModuleHandleA("UI_CEGUI.dll");
	//CString aaa;
	////aaa.Format()
	//My_Text.Format(_T("%d"), ce);
	//Player* asdasda;

	//asdasda = new Player;


	//My_Text.Format("%d",*Player::Model);
	//Player::GetPlayerData();

	//Player* Play;
	//Play = new Player;

	//My_Text = Player::GetName();
	//My_Text = "";
	//Player Play;	// 需要登陆角色后才能调用
	//My_Text = Play.Name;
	//My_Text += (to_cStr(*Play.Model) += _T(" - "));
	//My_Text += (to_cStr(Play.Map) += _T(" - "));
	//My_Text += (to_cStr(Play.Name) += _T("---"));
	//My_Text += (to_cStr(Play.X) += _T(" / "));
	//My_Text += (to_cStr(Play.Y) += _T("\r\n"));
	//My_Text += (to_cStr(Play.Hp) += _T(" / "));
	//My_Text += (to_cStr(Play.Hp_Max) += _T("\r\n"));
	//My_Text += (to_cStr(Play.Mp) += _T(" / "));
	//My_Text += (to_cStr(Play.Mp_Max) += _T("\r\n"));
	//My_Text += (to_cStr(Play.Rage) += _T("\r\n"));
	//My_Text += (to_cStr(Play.Level) += _T("\r\n"));
	//My_Text += (to_cStr(Play.Exp) += _T("\r\n"));
	//My_Text += (to_cStr(Play.YB_Bind) += _T("\r\n"));
	//My_Text += (to_cStr(Play.GangID) += _T("\r\n"));
	//My_Text += (to_cStr(Play.GangName) += _T("\r\n"));
	//My_Text += (to_cStr(Play.Pet_State) += _T("\r\n"));



	UpdateData(false);

}


void ScriptDialog::PostNcDestroy()
{
	DebugMessage("卸载成功");
	CDialogEx::PostNcDestroy();
}


void ScriptDialog::OnBnClickedButton4()
{
	//AfxBeginThread(Pack_Get_Active_Award, this);
}


BOOL ScriptDialog::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	CString strMsg;
	strMsg.Format("%d", pCopyDataStruct->dwData);
	//GetDlgItem(IDC_EDIT_ReceiveData)->SetWindowText(strMsg);
	//EditText = strMsg;
	//UpdateData(false);
	//return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
	//return TRUE;
	LuaString = strMsg;
	UpdateData(FALSE);
	return TRUE;
}
