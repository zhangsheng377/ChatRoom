// AddFriend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������ҿͻ���.h"
#include "AddFriend.h"
#include "afxdialogex.h"


// AddFriend �Ի���

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


// AddFriend ��Ϣ�������
