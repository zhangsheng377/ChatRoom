#pragma once


// ShowWaitDlg 对话框

class ShowWaitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShowWaitDlg)

public:
	ShowWaitDlg(CWnd* pParent = NULL);   // 标准构造函数
	
	virtual ~ShowWaitDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
