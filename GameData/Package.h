#pragma once

//�ַ���ת��
extern CString to_cStr(BYTE Bool);
extern CString to_cStr(INT Int);
extern CString to_cStr(FLOAT Float);
extern CString to_cStr(DWORD Dword);
extern CString to_cStr(CString cStr);

//����lua
extern void __stdcall LuaCall(char* LuaString);//����LuaCall
extern void DebugMessage(CString str);//���͹���
 
 //�Զ�Ѱ·
extern void GoTo(int x, int y);//����ͼѰ·
extern void GoTo(int x, int y, int city);//���ͼѰ·	-- ���ж�Ӧ����ֵ
 
 //��Ծ
extern void Get_Active(int value); //��ȡ��Ծֵ
extern void Get_Active_Award(); //��ȡ��Ծ����
//extern void Pack_Get_Active_Award();//һ����ȡ

extern void __stdcall InquireNPC(int NPC_ID);	//NPC�Ի�--�����