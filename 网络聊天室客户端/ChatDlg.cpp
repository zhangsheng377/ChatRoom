// ChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "网络聊天室客户端.h"
#include "ChatDlg.h"
#include "afxdialogex.h"


// ChatDlg 对话框

IMPLEMENT_DYNAMIC(ChatDlg, CDialogEx)

ChatDlg::ChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChatDlg::IDD, pParent)
	, my_ChatSendData(_T(""))
{

}

ChatDlg::~ChatDlg()
{
}

void ChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ChatListBox);
	DDX_Text(pDX, IDC_EDIT1, my_ChatSendData);
}


BEGIN_MESSAGE_MAP(ChatDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChatDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// ChatDlg 消息处理程序


void ChatDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
}


void ChatDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	Friend->IsChatting = FALSE;

	CDialogEx::OnCancel();
}
