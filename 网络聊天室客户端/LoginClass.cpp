// LoginClass.cpp : 实现文件
//

#include "stdafx.h"
#include "网络聊天室客户端.h"
#include "LoginClass.h"
#include "afxdialogex.h"


// LoginClass 对话框

IMPLEMENT_DYNAMIC(LoginClass, CDialogEx)

LoginClass::LoginClass(CWnd* pParent /*=NULL*/)
	: CDialogEx(LoginClass::IDD, pParent)
	, my_Name(_T(""))
	, my_Password(_T(""))
{

}

LoginClass::~LoginClass()
{
}

void LoginClass::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, my_Name);
	DDX_Text(pDX, IDC_EDIT2, my_Password);
}


BEGIN_MESSAGE_MAP(LoginClass, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &LoginClass::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &LoginClass::OnEnChangeEdit2)
END_MESSAGE_MAP()


// LoginClass 消息处理程序


void LoginClass::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
}


void LoginClass::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
}
