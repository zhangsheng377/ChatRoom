// ChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "网络聊天室客户端.h"
#include "网络聊天室客户端Dlg.h"
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
	UpdateData(true);
	C网络聊天室客户端App *pApp = (C网络聊天室客户端App*)AfxGetApp();
	C网络聊天室客户端Dlg *pDlg = (C网络聊天室客户端Dlg*)pApp->m_pMainWnd;

	pDlg->m_Socket.my_SendData = L"SendTo";
	pDlg->m_Socket.my_SendData += pDlg->friends[FriendNum].account;
	pDlg->m_Socket.my_SendData += my_ChatSendData;

	pDlg->m_Socket.my_Length = 0;
	memset(pDlg->m_Socket.my_Buffer, 0, sizeof(pDlg->m_Socket.my_Buffer));
	pDlg->m_Socket.my_Length = WideCharToMultiByte(CP_ACP, 0, pDlg->m_Socket.my_SendData, pDlg->m_Socket.my_SendData.GetLength(), NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, pDlg->m_Socket.my_SendData, pDlg->m_Socket.my_SendData.GetLength() + 1, pDlg->m_Socket.my_Buffer, pDlg->m_Socket.my_Length + 1, NULL, NULL);	//转换为字节为单位
	pDlg->m_Socket.my_Buffer[pDlg->m_Socket.my_Length + 1] = '\0';
	pDlg->m_Socket.Send(pDlg->m_Socket.my_Buffer, pDlg->m_Socket.my_Length, 0);
	
	CString tmpstring = L"我 说:";tmpstring += my_ChatSendData;
	m_ChatListBox.InsertString(0, tmpstring);
	my_ChatSendData = L"";
	UpdateData(false);
}


void ChatDlg::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	C网络聊天室客户端App *pApp = (C网络聊天室客户端App*)AfxGetApp();
	C网络聊天室客户端Dlg *pDlg = (C网络聊天室客户端Dlg*)pApp->m_pMainWnd;
	pDlg->friends[FriendNum].IsChatting = FALSE;

	CDialogEx::OnCancel();
}
