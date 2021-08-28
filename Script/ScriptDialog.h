#pragma once
//#include "HookGame.h"

// ScriptDialog 对话框
class ScriptDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ScriptDialog)

public:
	//void LuaCall(char* LuaString);
	ScriptDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ScriptDialog();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ScriptDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CString My_Text;
	CEdit My_Edit;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
//	virtual void PostNcDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	CString LuaString;
	afx_msg void OnBnClickedButton3();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedButton4();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};



