#pragma once
#include "afxwin.h"
#include "NewSocket.h"
#include "resource.h"
//#include "FRIEND.h"


// ChatDlg 对话框

class ChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChatDlg)

public:
	ChatDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChatDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ChatListBox;
	CString my_ChatSendData;
	afx_msg void OnBnClickedButton1();

	//CNewSocket m_Socket;
	int FriendNum;
	virtual void OnCancel();
	//FRIEND *Friend;
};
