// ChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������ҿͻ���.h"
#include "ChatDlg.h"
#include "afxdialogex.h"


// ChatDlg �Ի���

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


// ChatDlg ��Ϣ�������


void ChatDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void ChatDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	Friend->IsChatting = FALSE;

	CDialogEx::OnCancel();
}
