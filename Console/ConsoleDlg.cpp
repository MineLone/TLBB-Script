#include "pch.h"
#include "resource.h"		// 主符号
#include "Message.h"
#include "Console.h"
#include "ConsoleDlg.h"
#include <TlHelp32.h>
/*
struct pModule
{
	DWORD mAdd;			//模块地址
	//HMODULE mHandle;	//模块句柄	--暂时用不上
	CString mName;		//模块名字
};



typedef struct _ProcessData
{
	DWORD pPid;		//进程ID
	CString pName;	//进程名字
	pModule Module;	//模块信息
	struct _ProcessData* Next;

}ProcessData,*pProcessData;


//ProcessData aaaaa;

pProcessData CreateListForHead()
{
	pProcessData head = NULL;

	pProcessData Data = (pProcessData)malloc(sizeof(ProcessData));	//创建堆空间
	if (Data)
	{
		memset(Data, 0, sizeof(ProcessData));	//初始化0
		if (head == NULL)	//是否是第一个节点
		{
			head = Data;	//将创建的节点给这个头部
		}
		else
		{
			Data->Next = head;	//将创建的新节点的尾部指向已存在节点的头部
			head = Data;	//将头部节点设置为已创建的节点
		}

	}
	else
	{
		return NULL;	//创建堆内存失败
	}
	return head;
}

*/



CConsoleDlg::CConsoleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONSOLE_DIALOG, pParent)
	, Text_Str_Pid(_T(""))
	, Text_Str_Path(_T(""))
	, My_Debug_Text(_T(""))
	, My_NPC_Ask(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Str_Pid, Text_Str_Pid);
	DDX_Text(pDX, IDC_Str_Path, Text_Str_Path);
	DDX_Control(pDX, IDC_LIST_PROCESS, My_List_Control);
	DDX_Text(pDX, IDC_EDIT1, My_Debug_Text);
	DDX_Text(pDX, IDC_EDIT2, My_NPC_Ask);
}

BEGIN_MESSAGE_MAP(CConsoleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_INJECT, &CConsoleDlg::OnBnClickedBtInject)
	ON_BN_CLICKED(IDC_BT_Uninstall, &CConsoleDlg::OnBnClickedBtUninstall)
	//ON_BN_CLICKED(IDC_BUTTON2, &CConsoleDlg::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON3, &CConsoleDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CConsoleDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CConsoleDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BT_INJECT2, &CConsoleDlg::OnBnClickedBtInject2)
	ON_BN_CLICKED(IDC_BUTTON7, &CConsoleDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CConsoleDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON6, &CConsoleDlg::OnBnClickedButton6)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON9, &CConsoleDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON2, &CConsoleDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CConsoleDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CConsoleDlg 消息处理程序

BOOL CConsoleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();





	// 设置此对话框的图标。
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	My_List_Control.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	My_List_Control.InsertColumn(0, "进程ID", LVCFMT_LEFT, 70);
	My_List_Control.InsertColumn(1, "进程名字", LVCFMT_LEFT, 100);
	My_List_Control.InsertColumn(2, "窗口句柄", LVCFMT_LEFT, 100);
	My_List_Control.InsertColumn(3, "是否加载", LVCFMT_LEFT, 80);

	//My_List_Control.InsertItem(0, "1");
	//My_List_Control.SetItemText(0, 1, "1");
	//My_List_Control.InsertItem(1, "2");
	//My_List_Control.SetItemText(1, 1, "1");


	//CRect rect;
	//My_List_Control.GetClientRect(&rect);
	//CString itemArray[] = { CString("进程ID"),CString("文件名"),CString("标题"),CString("路径") };
	//// 为进程列表视图控件添加列 
	//int arrayLen = sizeof(itemArray) / sizeof(CString);
	//for (int index = 0; index < arrayLen; index++) {
	//	if (index == 0) {
	//		My_List_Control.InsertColumn(index, itemArray[index], LVCFMT_LEFT, (rect.Width() / arrayLen) * 0.5, index);
	//	}
	//	else if (index == 3) {
	//		My_List_Control.InsertColumn(index, itemArray[index], LVCFMT_LEFT, (rect.Width() / arrayLen) * 1.5, index);
	//	}
	//	else {
	//		My_List_Control.InsertColumn(index, itemArray[index], LVCFMT_LEFT, (rect.Width() / arrayLen), index);
	//	}
	//}



	TCHAR exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = (CString)exeFullPath;
	int position = strPath.ReverseFind('\\');
	strPath = strPath.Left(position + 1);
	strPath = strPath + "Console.ini";
	::GetPrivateProfileString("Console", "路径", "", Text_Str_Path.GetBuffer(MAX_PATH), MAX_PATH, strPath.GetBuffer());
	//::GetPrivateProfileString("Console", "路径", "", Text_Str_Path.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\Console.ini"));
	UpdateData(false);


	//::GetPrivateProfileString("Console", "路径", "", Text_Str_Path.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\Console.ini"));

	//UpdateData(false);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CConsoleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CConsoleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString strDllPath, strProcessID;


int injectDll(DWORD processID, char* dll) //注入Dll
{	
	if (processID != 0 && dll != NULL) {
		// Get handle of process
		HANDLE procHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, processID);

		// Get address of LoadLibraryA
		HANDLE loadLibraryAddress = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
		int cb = (lstrlenA(dll) + 1) * sizeof(char);
		// Allocate memory on target process
		HANDLE allocateMemoryAdress = VirtualAllocEx(procHandle, NULL, cb, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		// Write name of dll in process
		SIZE_T bytesWritten;
		WriteProcessMemory(procHandle, allocateMemoryAdress, (PVOID)dll, cb, &bytesWritten);

		// Create thread to call LoadLibraryA
		CreateRemoteThread(procHandle, NULL, 0, (PTHREAD_START_ROUTINE)loadLibraryAddress, allocateMemoryAdress, 0, NULL);
		return 1;
	}
	return 0;
}



void CConsoleDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UINT nCount;
	TCHAR szPath[MAX_PATH];
	CString dropFile;
	nCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	if (nCount)
	{
		for (UINT nIndex = 0; nIndex < nCount; ++nIndex)
		{
			DragQueryFile(hDropInfo, nIndex, szPath, _countof(szPath));
			dropFile = szPath;
			if (dropFile.Find(".dll") > 0) {
				UpdateData(TRUE);
				Text_Str_Path = dropFile;
				UpdateData(FALSE);

				//m_edit_dll_path.SetWindowTextA(dropFile);
			}
			else {
				MessageBox("只支持DLL后缀,请拖入需要注入的DLL文件!", _T("WM_DROPFILES"));
			}
		}
	}

	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}

/// <summary>
/// 注入按钮
/// </summary>
void CConsoleDlg::OnBnClickedBtInject()
{
	// TODO: 在此添加控件通知处理程序代码

		// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);	//传递 false
	strDllPath = Text_Str_Path;
	strProcessID = Text_Str_Pid;

	DWORD processID = _ttoi(strProcessID);

	if (strProcessID == "" || processID <= 0) {
		MessageBox("请选择要注入的进程!", _T("温馨提示"));
		return;
	}
	if (strDllPath != "") {

		if (injectDll(processID, strDllPath.GetBuffer())) {
			MessageBox(strDllPath + "注入成功!");
		}
	}
	else {
		MessageBox("请拖入需要注入的DLL文件!", _T("温馨提示"));
	}




}

/// <summary>
/// 卸载dll `	未实现
/// </summary>
void CConsoleDlg::OnBnClickedBtUninstall()
{

}





void CConsoleDlg::OnBnClickedButton4()
{
	UpdateData(true);
	char* buff;
	buff = Text_Str_Path.GetBuffer();
	::WritePrivateProfileString("Console","路径", buff, _T(".\\Console.ini"));

	UpdateData(false);
}


void CConsoleDlg::OnBnClickedButton5()
{
	//::GetPrivateProfileString("Console", "路径", "", Text_Str_Path.GetBuffer(MAX_PATH), MAX_PATH, _T(".\\Console.ini"));

	TCHAR exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = (CString)exeFullPath;
	int position = strPath.ReverseFind('\\');
	strPath = strPath.Left(position + 1);
	//TCHAR FilePath[MAX_PATH];
	//GetModuleFileName(NULL, FilePath, MAX_PATH);
	//(_tcsrchr(FilePath, '\\'))[1] = 0;//// 删除文件名，只获得路径字串   // // C:\**\**\ 
	//lstrcat(FilePath,_T("MY.ini")); 
	strPath = strPath + "Console.ini";
	::GetPrivateProfileString("Console", "路径", "", Text_Str_Path.GetBuffer(MAX_PATH), MAX_PATH, strPath.GetBuffer());
	UpdateData(false);
}


int SendGameMessage(HWND hWnd, DWORD dwData, CString lpData)
{
	COPYDATASTRUCT cpd;
	cpd.dwData = dwData;//用户定义的数据类型,可以用来作为发送标志	最大32位
	cpd.cbData = lpData.GetLength() + 1;//数据大小，长度一定要满足，否则数据传输不全
	cpd.lpData = (void*)lpData.GetBuffer(cpd.cbData); //数据指针
	LRESULT copyDataResult = ::SendMessage( hWnd , WM_COPYDATA, Msg_wParam, (LPARAM)&cpd);//发送消息	会阻塞等待--处理结束返回
	return copyDataResult;
}

//HWND hGameWnd = ::FindWindow(NULL, "《新天龙八部》 0.02.2651");	//窗口句柄


void CConsoleDlg::OnBnClickedBtInject2()
{
	UpdateData(TRUE);

	for (int i = 0; i < My_List_Control.GetItemCount(); i++)
	{
		if (My_List_Control.GetCheck(i))	//判断是否是选中状态
		{
			CString buff, buff2;
			buff2 = My_List_Control.GetItemText(i, 2);	//窗口句柄

			SendGameMessage((HWND)_ttoi(buff2), Msg_Debug, My_Debug_Text);
			//My_List_Control.SetItemText(i, 3, "已卸载");	//显示窗口句柄
			//SendGameMessage(hGameWnd, Msg_Debug, Text_Str_Path);
		}

	}

	//My_List_Control.GetCurSel();
	//My_List_Control.GetCurrentGestureInfo();




	//发送消息
	//CWnd* serverWnd = FindWindow(NULL, "《新天龙八部》 0.02.3003 (怀旧一区:剑指苍穹)");

	//hGameWnd = _ttoi(str);

	//CString a;
	//a.Format("%d", serverWnd);
	//MessageBox(a);

	//if (hGameWnd)
	//{
	//	//COPYDATASTRUCT cpd;
	//	//cpd.dwData = 2;//用户定义的数据类型,可以用来作为发送标志	最大32位
	//	//cpd.cbData = Text_Str_Pid.GetLength() * sizeof(TCHAR);//数据大小，长度一定要满足，否则数据传输不全
	//	//cpd.lpData = (void*)Text_Str_Pid.GetBuffer(cpd.cbData); //数据指针
	//	//LRESULT copyDataResult = ::SendMessage(serverWnd->GetSafeHwnd(), WM_COPYDATA, NULL, (LPARAM)&cpd);//发送消息	会阻塞等待--处理结束返回
	//	//EditText.ReleaseBuffer();

	//	SendGameMessage(hGameWnd, Msg_Debug, Text_Str_Path);
	//	//SendGameMessage(hGameWnd, Msg_Exit, "");


	//	//if (copyDataResult)
	//	//{
	//	//	MessageBox("接受到消息");
	//	//}
	//	//else
	//	//{
	//	//	MessageBox("没有接受到消息");
	//	//}
	//}


}


void CConsoleDlg::OnBnClickedButton7()
{
	//SendGameMessage(hGameWnd, Msg_退出, "");

	UpdateData(TRUE);
	for (int i = 0; i < My_List_Control.GetItemCount(); i++)
	{
		if (My_List_Control.GetCheck(i))	//判断是否是选中状态
		{
			CString buff, buff2;
			//buff = My_List_Control.GetItemText(i, 0);	//进程ID
			buff2 = My_List_Control.GetItemText(i, 2);	//窗口句柄

			SendGameMessage((HWND)_ttoi(buff2), Msg_退出, "");
			My_List_Control.SetItemText(i, 3, "已卸载");	//显示窗口句柄

		}

	}

}


void CConsoleDlg::OnBnClickedButton8()
{
	My_List_Control.DeleteAllItems();	//情况列表栏
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);	//创建一个进程快照	--第二参数遍历制定进程的时候才需要	--如果该函数成功，则返回指定快照的打开句柄。
	PROCESSENTRY32 processEntry = { sizeof(PROCESSENTRY32) };	//描述拍摄快照时驻留在系统地址空间中的进程列表中的条目。
	BOOL bSuccess = Process32First(hSnapshot, &processEntry);	//检索快照中遇到的第一个进程的信息。--参数二.指向 PROCESSENTRY32 结构的指针 --返回 成功 ture 失败 false

	CString pPid, pName, WinHandl;
	int i = 0;
	while (bSuccess)	//遍历进程信息
	{
		pName = processEntry.szExeFile;
		if ( pName == "Game.exe" )
		{
			pPid.Format("%d", processEntry.th32ProcessID);
			My_List_Control.InsertItem(i, pPid);
			My_List_Control.SetItemText(i, 1, pName);

			HANDLE hSnapshotM = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processEntry.th32ProcessID);		//包括快照中th32ProcessID中指定的进程的所有模块。
			//EnumProcessModules	//检索指定进程中每个模块的句柄。
			MODULEENTRY32 lpme = { sizeof(MODULEENTRY32) };		//描述属于指定进程的模块列表中的条目。
			BOOL mSuccess = Module32First(hSnapshotM, &lpme);	//获取指定进程的快照，以及这些进程使用的堆、模块和线程。

			DWORD Game_ModuleHandl;
			while (mSuccess)	//遍历模块信息
			{
				pName = lpme.szModule;

				if (pName == "UI_CEGUI.dll")
				{
					Game_ModuleHandl = (DWORD)lpme.modBaseAddr;
					//lpme.modBaseAddr;	//模块地址
					//lpme.hModule;		//模块句柄	--暂时用不上
					//lpme.szModule;		//模块名字
					break;
				}
				mSuccess = Module32Next(hSnapshotM, &lpme);
			}

			HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processEntry.th32ProcessID);    //打开进程句柄

			DWORD Game_WinHandl;

			ReadProcessMemory(pHandle, (DWORD*)(Game_ModuleHandl + 0x55CC8), &Game_WinHandl, sizeof(DWORD), 0);		//读内存地址

			CloseHandle(pHandle);	//关闭进程句柄

			WinHandl.Format("%d", Game_WinHandl);

			My_List_Control.SetItemText(i, 2, WinHandl);	//显示窗口句柄

			//My_List_Control.SetItemText(i, 3, "未加载");	//显示窗口句柄

			i++;
		}
		bSuccess = Process32Next(hSnapshot, &processEntry);
	}

}


void CConsoleDlg::OnBnClickedButton6()
{
	//int aaa;
	//aaa = My_List_Control.GetItemCount();	//获取数量
	//BOOL state = My_List_Control.GetCheck(i);	//是否选中
	UpdateData(TRUE);
	for (int i = 0; i < My_List_Control.GetItemCount(); i++)
	{
		if (My_List_Control.GetCheck(i))	//判断是否是选中状态
		{
			CString buff, buff2;
			buff = My_List_Control.GetItemText(i, 0);	//进程ID
			//buff2 = My_List_Control.GetItemText(i, 2);	//窗口句柄
			//_ttoi(buff);//进程ID

			if (Text_Str_Path != "")
			{
				injectDll(_ttoi(buff), Text_Str_Path.GetBuffer());
				My_List_Control.SetItemText(i, 3, "已加载");	//显示窗口句柄
			}
			else
			{
				MessageBox("请填写Dll的路径", _T("温馨提示"));
			}

			//injectDll(_ttoi(buff), Text_Str_Path.GetBuffer())
			//
			//strDllPath = Text_Str_Path;
			//strProcessID = Text_Str_Pid;

			////DWORD processID = _ttoi(strProcessID);

			////if (strProcessID == "" || processID <= 0) {
			////	MessageBox("请选择要注入的进程!", _T("温馨提示"));
			////	return;
			////}
			//if (strDllPath != "") {

			//	if (injectDll(processID, strDllPath.GetBuffer())) {
			//		MessageBox(strDllPath + "注入成功!");
			//	}
			//}
			//else {
			//	MessageBox("请拖入需要注入的DLL文件!", _T("温馨提示"));
			//}


			//BOOL aaaa;
			//aaaa = 1;
			//	ADDDlg dlg;
			//	dlg.DoModal();
			//	m_List.SetItemText(i, 0, dlg.sbh);
			//	m_List.SetItemText(i, 1, dlg.szl);
			//	m_List.SetItemText(i, 2, dlg.smc);
			//	m_List.SetItemText(i, 3, dlg.srq);
			//	m_List.SetItemText(i, 4, dlg.sbf);
			//	m_List.SetItemText(i, 5, dlg.sbrq);
		}

	}

}

//退出触发
void CConsoleDlg::OnDestroy()
{
	UpdateData(true);


	TCHAR exeFullPath[MAX_PATH];
	CString strPath;
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = (CString)exeFullPath;
	int position = strPath.ReverseFind('\\');
	strPath = strPath.Left(position + 1);
	//TCHAR FilePath[MAX_PATH];
	//GetModuleFileName(NULL, FilePath, MAX_PATH);
	//(_tcsrchr(FilePath, '\\'))[1] = 0;//// 删除文件名，只获得路径字串   // C:\**\**\
    //lstrcat(FilePath,_T("MY.ini")); 
	strPath = strPath + "Console.ini";
	//::GetPrivateProfileString("Console", "路径", "", Text_Str_Path.GetBuffer(MAX_PATH), MAX_PATH, strPath.GetBuffer());
	//::GetPrivateProfileString("Console", "路径", "", Text_Str_Path.GetBuffer(MAX_PATH), MAX_PATH,strPath.GetBuffer());

	char* buff;
	buff = Text_Str_Path.GetBuffer();
	::WritePrivateProfileString("Console", "路径", buff, strPath.GetBuffer());	//写配置项

	CDialogEx::OnDestroy();
}


void CConsoleDlg::OnBnClickedButton9()
{

	UpdateData(TRUE);

	for (int i = 0; i < My_List_Control.GetItemCount(); i++)
	{
		if (My_List_Control.GetCheck(i))	//判断是否是选中状态
		{
			CString buff, buff2;
			buff2 = My_List_Control.GetItemText(i, 2);	//窗口句柄
			SendGameMessage((HWND)_ttoi(buff2), Msg_领取活跃, "");

		}

	}





	//My_List_Control.SetSelectionMark(0);

	//if (My_List_Control.GetCheck(0))
	//{
	//	My_List_Control.SetCheck(0, 0);
	//}
	//else
	//{
	//	My_List_Control.SetCheck(0, 1);
	//}

}


void CConsoleDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	for (int i = 0; i < My_List_Control.GetItemCount(); i++)
	{
		if (My_List_Control.GetCheck(i))	//判断是否是选中状态
		{
			CString buff, buff2;
			buff2 = My_List_Control.GetItemText(i, 2);	//窗口句柄
			SendGameMessage((HWND)_ttoi(buff2), Msg_NPC对话, My_NPC_Ask);
		}
	}
	//CString aaa;

	//aaa = "0xC";



	//INT16 NPC_ID;
	//NPC_ID = strtol(aaa, NULL, 16);	//转化为16进制

	//NPC_ID;


}


void CConsoleDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码



	//HWND hWnd = (HWND)0x000908FA;
	//int lenl = GetWindowTextLength(hWnd);
	//char* buff = new char[lenl];
	//::GetWindowText(hWnd, buff, lenl);
	//delete buff;

}
