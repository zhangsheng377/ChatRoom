#pragma once
#include "afxwin.h"
#include "NewSocket.h"
#include "resource.h"
//#include "FRIEND.h"


// ChatDlg �Ի���

class ChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChatDlg)

public:
	ChatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChatDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
