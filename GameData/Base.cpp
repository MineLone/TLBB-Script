#include "pch.h"
#include "Base.h"
#include "Signa.h"
#include "GameProcess.h"

DWORD Pid = GetCurrentProcessId();	//��ȡ�������id
DWORD GameWindowHandle = GetGameWindowHandle();	//Game���ھ��




using namespace std;

//��ȡ���ھ��
int GetGameWindowHandle();











//1.����id  2.ģ������  3.���� ģ����ʼ��ַ 4.���� ģ���С
bool GetModuleInformation(DWORD Pid, char* ModuleName, DWORD& ModuleBaseAddr, DWORD& ModuleBaseSize);

//ת���ֽ����� 1.�ַ��� 2.���ص��ֽ�����ָ��
bool tobyte(char* str, byte* bstr);

//�����ַ��ַ��� 1.�ַ������� 2.�ַ����ĳ��� 3.���ݴ� 4.���ݴ����� 4.���õĶ�̬����
int FindString(byte* StrArray, int len, byte* dataStr, int dataLen, std::vector<int>& Array);

//����ģ���ڴ��ַ���	1.����id 2.ģ���� 3.������	--���ض�ȡ��������
int FindModuleStr(DWORD ProcessId, char* ModuleName, char* Signature, std::vector<int>& Array);

















DWORD Game::Game_ModuleHandl = (DWORD)GetModuleHandle(_T("Game.exe"));	//��ȡģ����
DWORD Game::UI_ModuleHandl = (DWORD)GetModuleHandle(_T("UI_CEGUI.dll"));	//��ȡui_cegui.dllģ����
DWORD Game::Game_Mian_Window = UI_ModuleHandl + 0x55CC8;	//��Ϸ�����ھ����ַ
DWORD Game::InquireNPC = UI_ModuleHandl + 0x55D00;	//NPC�Ի���ַ
HWND Game::Game_hGameWnd = *(HWND*)Game::Game_Mian_Window;	//��Ϸ�����ھ����ַ
DWORD Game::LuaPlusHandl = (DWORD)GetModuleHandle(_T("luaplus.dll"));	//��ȡluaplus.dllģ����
DWORD Game::Game_LuaHandl = UI_ModuleHandl + 0x55CD0;	//Lua��ַ
DWORD Game::Game_LuaDoString = LuaPlusHandl + 0xE230;	//Luaģ���ַ	
DWORD Game::Game_Player_ModuleHandl = UI_ModuleHandl + 0x55CE4;	//�����ַ
DWORD Game::Game_Map_ModuleHandl = Game_Player_ModuleHandl + 0x4;	//��ͼ��ַ	���� �����ַ+4	--���ø�
//DWORD Game::Game_Pet_Backpack = Game_ModuleHandl + 0x37F7F4;	//���ﱳ����ַ


Game::Game()
{
	
}

Game::~Game()
{

}

Player::Player()
{
	Map = (char*)(*(int*)(*(int*)Game_Map_ModuleHandl + 0x63ac) + 0x58);	//��ǰ��ͼ
	X = *(float*)(*(int*)(*(int*)Game_Player_ModuleHandl + 0x58) + 0x54)  ;	//x����
	Y = *(float*)(*(int*)(*(int*)Game_Player_ModuleHandl + 0x58) + 0x44);	//y����
	Model = (bool*)(*(int*)Game_Player_ModuleHandl + 0x29);	//��ɫģ��	---  1��ʾ 0����
	Player_Base = *(int*)(*(int*)(*(int*)Game_Player_ModuleHandl + 0x58) + 0x144) + 0x4;	//�������Խṹ��ַ
	Name = (char*)(*(int*)Player_Base + 0x2C);	//��ɫ����
	Hp = *(int*)(*(int*)Player_Base + 0x237c);	//Ѫ
	Hp_Max = *(int*)(*(int*)Player_Base + 0x23e8);	//Ѫ����
	Mp = *(int*)(*(int*)Player_Base + 0x2380);	//��
	Mp_Max = *(int*)(*(int*)Player_Base + 0x23ec);	//������
	Rage = *(int*)(*(int*)Player_Base + 0x5c);	//ŭ��
	Level = *(int*)(*(int*)Player_Base + 0x58);	//�ȼ�
	Exp = *(int*)(*(int*)Player_Base + 0x2384);	//����ֵ
	YB_Bind = *(int*)(*(int*)Player_Base + 0x24c4);	//��Ԫ��
	GangID = *(int*)(*(int*)Player_Base + 0xa8);	//����ID
	GangName = (char*)(*(int*)Player_Base + 0x221c);	//��������
	Pet_State = *(int*)(*(int*)Player_Base + 0x23bc);	//��ǰ��ս�����id
}

Player::~Player()
{

}



using namespace std;

#define MEMORYSIZE 20480 //ÿ�ζ�ȡ�ڴ������С

//1.����id  2.ģ������  3.���� ģ����ʼ��ַ 4.���� ģ���С
bool GetModuleInformation(DWORD Pid, char* ModuleName, DWORD& ModuleBaseAddr, DWORD& ModuleBaseSize)
{

	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Pid); //  ��ȡ���̿����а�����th32ProcessID��ָ���Ľ��̵����е�ģ��

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
		if (strcoll(lpme.szModule, ModuleName) == 0)	//�Ƚ�ģ������	��ͬ����0
		{
			/*
			std::cout << "MODULE NAME   " << lpme.szModule << endl;
			std::cout << "executable    " << lpme.szExePath << endl;
			std::cout << "process ID    " << lpme.th32ProcessID << endl;
			std::cout << "base address  " << (DWORD)lpme.modBaseAddr << endl;
			std::cout << "base size     " << lpme.modBaseSize << endl;
			*/

			/*
			//_tprintf(TEXT("\n         %s"), lpme.szModule);	//ģ�����ơ�
			//_tprintf(TEXT("\n       = %s"), lpme.szExePath);	//ģ��·����
			//_tprintf(TEXT("\n       = 0x%08X"), lpme.th32ProcessID);	//���̵ı�ʶ����
			//_tprintf(TEXT("\n       =     0x%04X"), lpme.GlblcntUsage);	//ģ��ļ��ش�����һ�������壬ͨ������0xFFFF��
			//_tprintf(TEXT("\n       =     0x%04X"), lpme.ProccntUsage);	//ģ��ļ��ؼ�������GlblcntUsage��ͬ����ͨ��û�����壬ͨ������ 0xFFFF��
			//_tprintf(TEXT("\n       = 0x%08X"), (DWORD)lpme.modBaseAddr);	//ӵ�н�����������ģ��Ļ���ַ��
			//_tprintf(TEXT("\n       = %d"), lpme.modBaseSize);	//ģ��Ĵ�С�����ֽ�Ϊ��λ��
			*/

			ModuleBaseAddr = (DWORD)lpme.modBaseAddr;
			ModuleBaseSize = lpme.modBaseSize;

			CloseHandle(hModuleSnap);	//����
			return(TRUE);
			//break;	//����whileѭ��
		}

		if (!Module32Next(hModuleSnap, &lpme))	//���Ϊ��..˵��û��ģ����Ϣ��
		{
			CloseHandle(hModuleSnap);
			return FALSE;	//��������ѭ��  ˵��û���ҵ�
		}

	} while (TRUE);	//һֱѭ��

	return(TRUE);
}

//ȥ��������Ŀո�
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

//ת���ֽ����� 1.�ַ��� 2.���ص��ֽ�����ָ��
bool tobyte(char* str, byte* bstr)
{

	for (unsigned int i = 0; i < (strlen(str) / 2); i++) {

		char c[] = { str[i * 2], str[i * 2 + 1], '\0' };

		if (*c != *"??")
		{
			bstr[i * 2] = (BYTE)::strtol(c, NULL, 16);	//���ַ���תΪ����
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

//�����ַ��ַ��� 1.�ַ������� 2.�ַ����ĳ��� 3.���ݴ� 4.���ݴ����� 4.���õĶ�̬����
int FindString(byte* StrArray, int len, byte* dataStr, int dataLen, vector<int>& Array)
{
	vector<int>Arr;	//��̬����

	for (int i = 0; i <= (dataLen - len); i++)	// i <= ���ݳ��� - �Ӵ�����
	{
		int k = i;

		for (int j = 0; StrArray[j * 2 + 1] == 1 || StrArray[j * 2] == dataStr[k]; j++, k++)	//�ж�ƥ�䲻ƥ��
		{

			if (j + 1 >= len)	//���滹�費��Ҫƥ��
			{
				Array.push_back(i);	//��¼λ��
				Arr.push_back(i);
			}

		}

	}

	return Arr.size();	//�����ҵ�������
}

//����ģ���ڴ��ַ���	1.����id 2.ģ���� 3.������	--���ض�ȡ��������
int FindModuleStr(DWORD ProcessId, char* ModuleName, char* Signa, vector<int>& Array)
{

	char* Signature = RemoveSpaces(Signa);

	byte* StrArray = (byte*)malloc(strlen(Signature));	//����һ���ѿռ�

	tobyte(Signature, StrArray);	//ת���ֽ�����

	int len = strlen(Signature) / 2;	//ģʽ������

	free(Signature);

	DWORD ModuleAddr = NULL;	//ģ���ַ
	DWORD ModuleSize = NULL;	//ģ���С

	if (!GetModuleInformation(ProcessId, ModuleName, ModuleAddr, ModuleSize))	//��ȡģ����Ϣ
	{
		//std::cout << "��ȡģ����Ϣʧ��/n" << endl;
		OutputDebugStringW(L"MSG:��ȡģ����Ϣʧ��");//���͵�����Ϣ
		free(StrArray);	//�ͷŵ���������ֽ�����
		return false;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessId);//ͨ������ID��ȡ���̾��

	if (!hProcess)
	{
		//std::cout << "�򿪽��̾��ʧ��/n" << endl;
		OutputDebugStringW(L"MSG:�򿪽��̾��ʧ��");//���͵�����Ϣ
		//CloseHandle(hProcess);	//��ʱ�ر�
		free(StrArray);	//�ͷŵ���������ֽ�����
		return false;
	}

	vector<int> Arr;	//�����ַ�Ķ�̬����

	int BlockSize = ModuleSize;		//��ȡ���ڴ��С
	DWORD BaseAddr = ModuleAddr;	//��ȡ���ڴ��ַ


	int Page = 0;	//������¼��ȡ��ҳ��

	int memorySize = MEMORYSIZE;

	//std::cout << "ģ���ַ" << hex << ModuleAddr << endl;
	//std::cout << "ģ���С" << hex << ModuleSize << endl;

	int ModuleEnd = ModuleAddr + ModuleSize - 1;	//ģ�������ַ

	while (BaseAddr + memorySize != ModuleEnd)
	{

		if (memorySize >= BlockSize)
		{
			memorySize = BlockSize - 1;
		}

		byte* MemoryData = (byte*)malloc(memorySize);	//ÿ�ζ�ȡ���ڴ��С	������ȡ�ڴ��ַ�Ŀ�����

		if (MemoryData)
		{
			if (!ReadProcessMemory(hProcess, (LPCVOID)BaseAddr, MemoryData, memorySize, NULL))	//��ȡ�ڴ�
			{
				//std::cout << "��ȡ�ڴ��ַʧ��/n" << endl;
				OutputDebugStringW(L"MSG:��ȡ�ڴ��ַʧ��");//���͵�����Ϣ
				free(StrArray);	//�ͷŵ���������ֽ�����
				free(MemoryData);	//�ͷ��ڴ�ռ�
				return false;
			}
		}

		if (FindString(StrArray, len, MemoryData, memorySize, Arr)) //�����ַ���
		{
			for (size_t i = 0; i < Arr.size(); i++)	//ѭ����ӡ
			{
				//std::cout << "��" << Page << "ҳ�ҵ��� �ڴ��ַ :" << hex << (ModuleAddr + Page * (MEMORYSIZE - len + 1) + Arr[i]) << endl;
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
			BaseAddr = BaseAddr + (memorySize - len + 1);	//���¶�ȡ�ĵ�ַ
			BlockSize = BlockSize - (memorySize - len + 1); //���¶�ȡʣ�������
		}

		free(MemoryData);	//�����ͷŶ�ȡ���ڴ�

	}
	free(StrArray);	//�ͷŵ���������ֽ�����
	CloseHandle(hProcess);	//�رմ򿪵Ľ��̾������
	return true;
}

//��ȡ���ھ��
int GetGameWindowHandle()
{
	char ModuleName[] = "Game.exe";	//�����ĵ�ģ����
	char Signa[] = ���ھ����ַ;	//8D 45 F8 50 8B F1 FF 15 ?? ?? ?? ?? 8D 45 F8 50 FF 35
	vector<int> Array;	//�������շ��صĵ�ַ
	FindModuleStr(Pid, ModuleName, Signa, Array);
	if (Array.size() != 1)
	{
		MessageBox(0, "��ʼ�����ھ��ʧ��", "", 0);
		return 0;
	}
	GameWindowHandle = *(int*)(*(int*)(Array[0] + ���ھ��ƫ��));
	return GameWindowHandle;
}

//��ȡLua��ַ
int GetGameLuaBase()
{
	char ModuleName[] = "UI_CEGUI.dll";	//�����ĵ�ģ����
	char Signa[] = ���ھ����ַ;	//8D 45 F8 50 8B F1 FF 15 ?? ?? ?? ?? 8D 45 F8 50 FF 35
	vector<int> Array;	//�������շ��صĵ�ַ
	FindModuleStr(Pid, ModuleName, Signa, Array);
	if (Array.size() != 1)
	{
		MessageBox(0, "��ʼ�����ھ��ʧ��", "", 0);
		return 0;
	}
	GameWindowHandle = *(int*)(*(int*)(Array[0] + ���ھ��ƫ��));
	return GameWindowHandle;
}