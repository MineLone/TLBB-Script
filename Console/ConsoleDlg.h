#pragma once

// CConsoleDlg 对话框
class CConsoleDlg : public CDialogEx
{
// 构造
public:
	CConsoleDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSOLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString Text_Str_Pid;
	CString Text_Str_Path;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg	void OnBnClickedBtInject();

	afx_msg void OnBnClickedBtUninstall();
	//afx_msg void OnBnClickedButton2();
	//afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedBtInject2();
	afx_msg void OnBnClickedButton7();
	CListCtrl My_List_Control;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton9();
	CString My_Debug_Text;
	afx_msg void OnBnClickedButton2();
	CString My_NPC_Ask;
	afx_msg void OnBnClickedButton3();
};
