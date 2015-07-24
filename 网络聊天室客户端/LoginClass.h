#pragma once


// LoginClass 对话框

class LoginClass : public CDialogEx
{
	DECLARE_DYNAMIC(LoginClass)

public:
	LoginClass(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LoginClass();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString my_Name;
	CString my_Password;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
};
