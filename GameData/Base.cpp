#include "pch.h"
#include "Base.h"
#include "Signa.h"
#include "GameProcess.h"

DWORD Pid = GetCurrentProcessId();	//获取自身进程id
DWORD GameWindowHandle = GetGameWindowHandle();	//Game窗口句柄




using namespace std;

//获取窗口句柄
int GetGameWindowHandle();











//1.进程id  2.模块名字  3.引用 模块起始地址 4.引用 模块大小
bool GetModuleInformation(DWORD Pid, char* ModuleName, DWORD& ModuleBaseAddr, DWORD& ModuleBaseSize);

//转换字节数组 1.字符串 2.返回的字节数组指针
bool tobyte(char* str, byte* bstr);

//查找字符字符串 1.字符串数组 2.字符串的长度 3.数据串 4.数据串长度 4.引用的动态数组
int FindString(byte* StrArray, int len, byte* dataStr, int dataLen, std::vector<int>& Array);

//查找模块内存字符串	1.进程id 2.模块名 3.特征码	--返回读取到的数量
int FindModuleStr(DWORD ProcessId, char* ModuleName, char* Signature, std::vector<int>& Array);

















DWORD Game::Game_ModuleHandl = (DWORD)GetModuleHandle(_T("Game.exe"));	//获取模块句柄
DWORD Game::UI_ModuleHandl = (DWORD)GetModuleHandle(_T("UI_CEGUI.dll"));	//获取ui_cegui.dll模块句柄
DWORD Game::Game_Mian_Window = UI_ModuleHandl + 0x55CC8;	//游戏主窗口句柄基址
DWORD Game::InquireNPC = UI_ModuleHandl + 0x55D00;	//NPC对话基址
HWND Game::Game_hGameWnd = *(HWND*)Game::Game_Mian_Window;	//游戏主窗口句柄基址
DWORD Game::LuaPlusHandl = (DWORD)GetModuleHandle(_T("luaplus.dll"));	//获取luaplus.dll模块句柄
DWORD Game::Game_LuaHandl = UI_ModuleHandl + 0x55CD0;	//Lua基址
DWORD Game::Game_LuaDoString = LuaPlusHandl + 0xE230;	//Lua模块基址	
DWORD Game::Game_Player_ModuleHandl = UI_ModuleHandl + 0x55CE4;	//人物基址
DWORD Game::Game_Map_ModuleHandl = Game_Player_ModuleHandl + 0x4;	//地图基址	等于 人物基址+4	--不用改
//DWORD Game::Game_Pet_Backpack = Game_ModuleHandl + 0x37F7F4;	//宠物背包基址


Game::Game()
{
	
}

Game::~Game()
{

}

Player::Player()
{
	Map = (char*)(*(int*)(*(int*)Game_Map_ModuleHandl + 0x63ac) + 0x58);	//当前地图
	X = *(float*)(*(int*)(*(int*)Game_Player_ModuleHandl + 0x58) + 0x54)  ;	//x坐标
	Y = *(float*)(*(int*)(*(int*)Game_Player_ModuleHandl + 0x58) + 0x44);	//y坐标
	Model = (bool*)(*(int*)Game_Player_ModuleHandl + 0x29);	//角色模型	---  1显示 0隐藏
	Player_Base = *(int*)(*(int*)(*(int*)Game_Player_ModuleHandl + 0x58) + 0x144) + 0x4;	//人物属性结构地址
	Name = (char*)(*(int*)Player_Base + 0x2C);	//角色名字
	Hp = *(int*)(*(int*)Player_Base + 0x237c);	//血
	Hp_Max = *(int*)(*(int*)Player_Base + 0x23e8);	//血上限
	Mp = *(int*)(*(int*)Player_Base + 0x2380);	//蓝
	Mp_Max = *(int*)(*(int*)Player_Base + 0x23ec);	//蓝上限
	Rage = *(int*)(*(int*)Player_Base + 0x5c);	//怒气
	Level = *(int*)(*(int*)Player_Base + 0x58);	//等级
	Exp = *(int*)(*(int*)Player_Base + 0x2384);	//经验值
	YB_Bind = *(int*)(*(int*)Player_Base + 0x24c4);	//绑定元宝
	GangID = *(int*)(*(int*)Player_Base + 0xa8);	//帮派ID
	GangName = (char*)(*(int*)Player_Base + 0x221c);	//帮派名称
	Pet_State = *(int*)(*(int*)Player_Base + 0x23bc);	//当前出战宠物的id
}

Player::~Player()
{

}



using namespace std;

#define MEMORYSIZE 20480 //每次读取内存的最大大小

//1.进程id  2.模块名字  3.引用 模块起始地址 4.引用 模块大小
bool GetModuleInformation(DWORD Pid, char* ModuleName, DWORD& ModuleBaseAddr, DWORD& ModuleBaseSize)
{

	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Pid); //  获取进程快照中包含在th32ProcessID中指定的进程的所有的模块

	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		_tprintf(TEXT("CreateToolhelp32Snapshot (of modules)"));
		return(FALSE);
	}

	//HANDLE hSnapshot = INVALID_HANDLE_VALUE;
	MODULEENTRY32 lpme;

	//  Set the size of the structure before using it. 
	lpme.dwSize = sizeof(MODULEENTRY32);

	//  Retrieve information about the first module, 
	//  and exit if unsuccessful 
	if (!Module32First(hModuleSnap, &lpme))
	{
		_tprintf(TEXT("Module32First"));  // Show cause of failure 
		CloseHandle(hModuleSnap);     // Must clean up the snapshot object! 
		return(FALSE);
	}

	do
	{
		//std::cout << lpme.szModule << endl;
		if (strcoll(lpme.szModule, ModuleName) == 0)	//比较模块名字	相同返回0
		{
			/*
			std::cout << "MODULE NAME   " << lpme.szModule << endl;
			std::cout << "executable    " << lpme.szExePath << endl;
			std::cout << "process ID    " << lpme.th32ProcessID << endl;
			std::cout << "base address  " << (DWORD)lpme.modBaseAddr << endl;
			std::cout << "base size     " << lpme.modBaseSize << endl;
			*/

			/*
			//_tprintf(TEXT("\n         %s"), lpme.szModule);	//模块名称。
			//_tprintf(TEXT("\n       = %s"), lpme.szExePath);	//模块路径。
			//_tprintf(TEXT("\n       = 0x%08X"), lpme.th32ProcessID);	//进程的标识符。
			//_tprintf(TEXT("\n       =     0x%04X"), lpme.GlblcntUsage);	//模块的加载次数，一般无意义，通常等于0xFFFF。
			//_tprintf(TEXT("\n       =     0x%04X"), lpme.ProccntUsage);	//模块的加载计数（与GlblcntUsage相同），通常没有意义，通常等于 0xFFFF。
			//_tprintf(TEXT("\n       = 0x%08X"), (DWORD)lpme.modBaseAddr);	//拥有进程上下文中模块的基地址。
			//_tprintf(TEXT("\n       = %d"), lpme.modBaseSize);	//模块的大小，以字节为单位。
			*/

			ModuleBaseAddr = (DWORD)lpme.modBaseAddr;
			ModuleBaseSize = lpme.modBaseSize;

			CloseHandle(hModuleSnap);	//清理
			return(TRUE);
			//break;	//跳出while循环
		}

		if (!Module32Next(hModuleSnap, &lpme))	//如果为空..说明没有模块信息啦
		{
			CloseHandle(hModuleSnap);
			return FALSE;	//结束函数循环  说明没有找到
		}

	} while (TRUE);	//一直循环

	return(TRUE);
}

//去除特征码的空格
char* RemoveSpaces(char* str)
{
	int len = strlen(str);
	//char* x = new char[len - (len / 3) + 1 ];
	char* x = (char*)malloc(len - (len / 3) + 1);

	int j = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] != 0x20)
		{
			x[j] = str[i];
			j++;
		}
	}
	x[j] = 0x0;
	return x;
}

//转换字节数组 1.字符串 2.返回的字节数组指针
bool tobyte(char* str, byte* bstr)
{

	for (unsigned int i = 0; i < (strlen(str) / 2); i++) {

		char c[] = { str[i * 2], str[i * 2 + 1], '\0' };

		if (*c != *"??")
		{
			bstr[i * 2] = (BYTE)::strtol(c, NULL, 16);	//将字符串转为整数
			bstr[i * 2 + 1] = 0x00;
		}
		else
		{
			bstr[i * 2] = 0x00;
			bstr[i * 2 + 1] = 0x01;
		}
	}

	return 1;

}

//查找字符字符串 1.字符串数组 2.字符串的长度 3.数据串 4.数据串长度 4.引用的动态数组
int FindString(byte* StrArray, int len, byte* dataStr, int dataLen, vector<int>& Array)
{
	vector<int>Arr;	//动态数组

	for (int i = 0; i <= (dataLen - len); i++)	// i <= 数据长度 - 子串长度
	{
		int k = i;

		for (int j = 0; StrArray[j * 2 + 1] == 1 || StrArray[j * 2] == dataStr[k]; j++, k++)	//判断匹配不匹配
		{

			if (j + 1 >= len)	//后面还需不需要匹配
			{
				Array.push_back(i);	//记录位置
				Arr.push_back(i);
			}

		}

	}

	return Arr.size();	//返回找到的数量
}

//查找模块内存字符串	1.进程id 2.模块名 3.特征码	--返回读取到的数量
int FindModuleStr(DWORD ProcessId, char* ModuleName, char* Signa, vector<int>& Array)
{

	char* Signature = RemoveSpaces(Signa);

	byte* StrArray = (byte*)malloc(strlen(Signature));	//开辟一个堆空间

	tobyte(Signature, StrArray);	//转换字节数组

	int len = strlen(Signature) / 2;	//模式串数量

	free(Signature);

	DWORD ModuleAddr = NULL;	//模块地址
	DWORD ModuleSize = NULL;	//模块大小

	if (!GetModuleInformation(ProcessId, ModuleName, ModuleAddr, ModuleSize))	//获取模块信息
	{
		//std::cout << "获取模块信息失败/n" << endl;
		OutputDebugStringW(L"MSG:获取模块信息失败");//发送调试信息
		free(StrArray);	//释放掉特征码的字节数组
		return false;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessId);//通过进程ID获取进程句柄

	if (!hProcess)
	{
		//std::cout << "打开进程句柄失败/n" << endl;
		OutputDebugStringW(L"MSG:打开进程句柄失败");//发送调试信息
		//CloseHandle(hProcess);	//及时关闭
		free(StrArray);	//释放掉特征码的字节数组
		return false;
	}

	vector<int> Arr;	//储存地址的动态数组

	int BlockSize = ModuleSize;		//读取的内存大小
	DWORD BaseAddr = ModuleAddr;	//读取的内存地址


	int Page = 0;	//用来记录读取的页数

	int memorySize = MEMORYSIZE;

	//std::cout << "模块地址" << hex << ModuleAddr << endl;
	//std::cout << "模块大小" << hex << ModuleSize << endl;

	int ModuleEnd = ModuleAddr + ModuleSize - 1;	//模块结束地址

	while (BaseAddr + memorySize != ModuleEnd)
	{

		if (memorySize >= BlockSize)
		{
			memorySize = BlockSize - 1;
		}

		byte* MemoryData = (byte*)malloc(memorySize);	//每次读取的内存大小	创建读取内存地址的拷贝区

		if (MemoryData)
		{
			if (!ReadProcessMemory(hProcess, (LPCVOID)BaseAddr, MemoryData, memorySize, NULL))	//读取内存
			{
				//std::cout << "读取内存地址失败/n" << endl;
				OutputDebugStringW(L"MSG:读取内存地址失败");//发送调试信息
				free(StrArray);	//释放掉特征码的字节数组
				free(MemoryData);	//释放内存空间
				return false;
			}
		}

		if (FindString(StrArray, len, MemoryData, memorySize, Arr)) //查找字符串
		{
			for (size_t i = 0; i < Arr.size(); i++)	//循环打印
			{
				//std::cout << "第" << Page << "页找到的 内存地址 :" << hex << (ModuleAddr + Page * (MEMORYSIZE - len + 1) + Arr[i]) << endl;
				Array.push_back(ModuleAddr + Page * (memorySize - len + 1) + Arr[i]);
			}
		}

		Page++;

		if (BaseAddr + memorySize == ModuleEnd)
		{
			//std::cout << hex << (BaseAddr + memorySize) << endl;
			break;
		}
		else
		{
			BaseAddr = BaseAddr + (memorySize - len + 1);	//更新读取的地址
			BlockSize = BlockSize - (memorySize - len + 1); //更新读取剩余的总量
		}

		free(MemoryData);	//用完释放读取的内存

	}
	free(StrArray);	//释放掉特征码的字节数组
	CloseHandle(hProcess);	//关闭打开的进程句柄对象
	return true;
}

//获取窗口句柄
int GetGameWindowHandle()
{
	char ModuleName[] = "Game.exe";	//搜索的的模块名
	char Signa[] = 窗口句柄基址;	//8D 45 F8 50 8B F1 FF 15 ?? ?? ?? ?? 8D 45 F8 50 FF 35
	vector<int> Array;	//用来接收返回的地址
	FindModuleStr(Pid, ModuleName, Signa, Array);
	if (Array.size() != 1)
	{
		MessageBox(0, "初始化窗口句柄失败", "", 0);
		return 0;
	}
	GameWindowHandle = *(int*)(*(int*)(Array[0] + 窗口句柄偏移));
	return GameWindowHandle;
}

//获取Lua基址
int GetGameLuaBase()
{
	char ModuleName[] = "UI_CEGUI.dll";	//搜索的的模块名
	char Signa[] = 窗口句柄基址;	//8D 45 F8 50 8B F1 FF 15 ?? ?? ?? ?? 8D 45 F8 50 FF 35
	vector<int> Array;	//用来接收返回的地址
	FindModuleStr(Pid, ModuleName, Signa, Array);
	if (Array.size() != 1)
	{
		MessageBox(0, "初始化窗口句柄失败", "", 0);
		return 0;
	}
	GameWindowHandle = *(int*)(*(int*)(Array[0] + 窗口句柄偏移));
	return GameWindowHandle;
}