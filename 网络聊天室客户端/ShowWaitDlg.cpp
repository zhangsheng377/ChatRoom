// ShowWaitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "网络聊天室客户端.h"
#include "ShowWaitDlg.h"
#include "afxdialogex.h"


// ShowWaitDlg 对话框

IMPLEMENT_DYNAMIC(ShowWaitDlg, CDialogEx)

ShowWaitDlg::ShowWaitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ShowWaitDlg::IDD, pParent)
{
	//ASSERT(pParent);
	//m_pParent = pParent;
}

ShowWaitDlg::~ShowWaitDlg()
{
}

void ShowWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ShowWaitDlg, CDialogEx)
END_MESSAGE_MAP()


// ShowWaitDlg 消息处理程序
