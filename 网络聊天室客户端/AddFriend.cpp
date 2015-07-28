// AddFriend.cpp : 实现文件
//

#include "stdafx.h"
#include "网络聊天室客户端.h"
#include "AddFriend.h"
#include "afxdialogex.h"


// AddFriend 对话框

IMPLEMENT_DYNAMIC(AddFriend, CDialogEx)

AddFriend::AddFriend(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddFriend::IDD, pParent)
	, my_FriendName(_T(""))
{

}

AddFriend::~AddFriend()
{
}

void AddFriend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, my_FriendName);
}


BEGIN_MESSAGE_MAP(AddFriend, CDialogEx)
END_MESSAGE_MAP()


// AddFriend 消息处理程序
