// LoginClass.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������ҿͻ���.h"
#include "LoginClass.h"
#include "afxdialogex.h"


// LoginClass �Ի���

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
END_MESSAGE_MAP()


// LoginClass ��Ϣ�������
