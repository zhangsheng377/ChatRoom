// ShowWaitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������ҿͻ���.h"
#include "ShowWaitDlg.h"
#include "afxdialogex.h"


// ShowWaitDlg �Ի���

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


// ShowWaitDlg ��Ϣ�������
