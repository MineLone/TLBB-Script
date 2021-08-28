
#include "pch.h"
#include "MyDll.h"
#include "Hook.h"
#include "Package.h"
#include "Thread.h"


//��Ϣ������
LRESULT CALLBACK GameWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	CWPSTRUCT* lpArg = (CWPSTRUCT*)lParam;

	if (nCode == HC_ACTION)//�ж��Ƿ��ǽ��̵���Ϣ
	{

		if ((lpArg->message == WM_COPYDATA) || lpArg->wParam == Msg_wParam)	//�Ƿ��Ƿ��͵���Ϣ	-- ͬʱ������֤
		{
			//lpArg->wParam;	//�Զ������	׼����������	-- ��������ͨ��wParam����ֵ������֤

			COPYDATASTRUCT* pCopyData = (COPYDATASTRUCT*)(lpArg->lParam);

			//pCopyData->dwData;	//�Զ������	��Ϣ������
			//pCopyData->cbData;	//���Ͱ��ĳ���
			char* buff = (char*)pCopyData->lpData;	//���ݰ�����
			CString strbuff;	//���ݰ�����
			//strbuff.Format("%d", pCopyData->dwData);
			strbuff = buff;

			switch (pCopyData->dwData)
			{

			case Msg_Debug:
				//MessageBox(NULL, "�յ�debug��Ϣ", "", 0);
				DebugMessage(strbuff);
				break;
			case Msg_LuaCall:



				//MessageBox(NULL, "�յ�debug��Ϣ", "", 0);
				//DebugMessage(strbuff);
				break;
			case Msg_��ȡ��Ծ:

				_beginthreadex(NULL, NULL, Pack_Get_Active_Award, NULL, NULL, NULL);
				//MessageBox(NULL, "�յ�debug��Ϣ", "", 0);
				//DebugMessage(strbuff);
				break;

			case Msg_NPC�Ի�:

				InquireNPC(0xC);
				break;


			case Msg_�˳�:
				//MessageBox(NULL, "�ָ��߳�", "", 0);
				ResumeThread(Dll_Thread);
				break;
			default:
				break;
			}
		}

	}

	return CallNextHookEx(Game_Hook, nCode, wParam, lParam);

}