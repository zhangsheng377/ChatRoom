// ChatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������ҿͻ���.h"
#include "���������ҿͻ���Dlg.h"
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
	UpdateData(true);
	C���������ҿͻ���App *pApp = (C���������ҿͻ���App*)AfxGetApp();
	C���������ҿͻ���Dlg *pDlg = (C���������ҿͻ���Dlg*)pApp->m_pMainWnd;

	pDlg->m_Socket.my_SendData = L"SendTo";
	pDlg->m_Socket.my_SendData += pDlg->friends[FriendNum].account;
	pDlg->m_Socket.my_SendData += my_ChatSendData;

	pDlg->m_Socket.my_Length = 0;
	memset(pDlg->m_Socket.my_Buffer, 0, sizeof(pDlg->m_Socket.my_Buffer));
	pDlg->m_Socket.my_Length = WideCharToMultiByte(CP_ACP, 0, pDlg->m_Socket.my_SendData, pDlg->m_Socket.my_SendData.GetLength(), NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, pDlg->m_Socket.my_SendData, pDlg->m_Socket.my_SendData.GetLength() + 1, pDlg->m_Socket.my_Buffer, pDlg->m_Socket.my_Length + 1, NULL, NULL);	//ת��Ϊ�ֽ�Ϊ��λ
	pDlg->m_Socket.my_Buffer[pDlg->m_Socket.my_Length + 1] = '\0';
	pDlg->m_Socket.Send(pDlg->m_Socket.my_Buffer, pDlg->m_Socket.my_Length, 0);
	
	CString tmpstring = L"�� ˵:";tmpstring += my_ChatSendData;
	m_ChatListBox.InsertString(0, tmpstring);
	my_ChatSendData = L"";
	UpdateData(false);
}


void ChatDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	C���������ҿͻ���App *pApp = (C���������ҿͻ���App*)AfxGetApp();
	C���������ҿͻ���Dlg *pDlg = (C���������ҿͻ���Dlg*)pApp->m_pMainWnd;
	pDlg->friends[FriendNum].IsChatting = FALSE;

	CDialogEx::OnCancel();
}
