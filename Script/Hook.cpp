
#include "pch.h"
#include "MyDll.h"
#include "Hook.h"
#include "Package.h"
#include "Thread.h"


//消息处理函数
LRESULT CALLBACK GameWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CWPSTRUCT* lpArg = (CWPSTRUCT*)lParam;

	if (nCode == HC_ACTION)//判断是否是进程的消息
	{

		if ((lpArg->message == WM_COPYDATA) || lpArg->wParam == Msg_wParam)	//是否是发送的消息	-- 同时进行验证
		{
			//lpArg->wParam;	//自定定义的	准备当做种类	-- 后续可以通过wParam设置值进行验证

			COPYDATASTRUCT* pCopyData = (COPYDATASTRUCT*)(lpArg->lParam);

			//pCopyData->dwData;	//自定定义的	消息的种类
			//pCopyData->cbData;	//发送包的长度
			char* buff = (char*)pCopyData->lpData;	//数据包内容
			CString strbuff;	//数据包内容
			//strbuff.Format("%d", pCopyData->dwData);
			strbuff = buff;

			switch (pCopyData->dwData)
			{

			case Msg_Debug:
				//MessageBox(NULL, "收到debug消息", "", 0);
				DebugMessage(strbuff);
				break;
			case Msg_LuaCall:



				//MessageBox(NULL, "收到debug消息", "", 0);
				//DebugMessage(strbuff);
				break;
			case Msg_领取活跃:

				_beginthreadex(NULL, NULL, Pack_Get_Active_Award, NULL, NULL, NULL);
				//MessageBox(NULL, "收到debug消息", "", 0);
				//DebugMessage(strbuff);
				break;

			case Msg_NPC对话:

				InquireNPC(0xC);
				break;


			case Msg_退出:
				//MessageBox(NULL, "恢复线程", "", 0);
				ResumeThread(Dll_Thread);
				break;
			default:
				break;
			}
		}

	}

	return CallNextHookEx(Game_Hook, nCode, wParam, lParam);

}