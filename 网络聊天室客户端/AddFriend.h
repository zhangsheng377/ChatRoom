#pragma once


// AddFriend 对话框

class AddFriend : public CDialogEx
{
	DECLARE_DYNAMIC(AddFriend)

public:
	AddFriend(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddFriend();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString my_FriendName;
};
