#pragma once


// AddFriend �Ի���

class AddFriend : public CDialogEx
{
	DECLARE_DYNAMIC(AddFriend)

public:
	AddFriend(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddFriend();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString my_FriendName;
};
