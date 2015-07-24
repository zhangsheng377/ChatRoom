#include "stdafx.h"
#include "NewSocket.h"
#include "���������ҷ�������Dlg.h"
#include "���������ҷ�������.h"


NewSocket::NewSocket()
{
	m_Length = 0;
	memset(m_Buffer, 0, sizeof(m_Buffer));
}


NewSocket::~NewSocket()
{
	if (m_hSocket != INVALID_SOCKET) Close();
}


void NewSocket::OnReceive(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);

	C���������ҷ�������App *pApp = (C���������ҷ�������App*)AfxGetApp();
	C���������ҷ�������Dlg *pDlg = (C���������ҷ�������Dlg*)pApp->m_pMainWnd;
	CString tmp(m_Buffer), temp = L"���յ�:";temp += tmp;
	pDlg->m_ListBox.InsertString(0, temp);

	if (memcmp(m_Buffer, "AmIConnected", sizeof("AmIConnected")-1) == 0)
	{
		my_SendData = L"YouAreConnected";
	}
	else
	{
		if (memcmp(m_Buffer, "LoginMyName", sizeof("LoginMyName")-1) == 0)
		{
			my_SendData = L"HereYouAre";
			if (my_SendData != "")
			{
				int Length = 0;
				char Buffer[4096];
				memset(Buffer, 0, sizeof(Buffer));
				Length = WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength(), NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//ת��Ϊ�ֽ�Ϊ��λ
				Buffer[Length + 1] = '\0';
				Send(Buffer, Length, 0);
				CString tmp(Buffer), temp = L"���ͳ�:";temp += tmp;
				pDlg->m_ListBox.InsertString(0, temp);
			}

			memset(m_Buffer, 0, sizeof(m_Buffer));
			do
			{
				m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);
			} while (m_Buffer[0]=='\0');
			CString tmp(m_Buffer), temp = L"���յ�:";temp += tmp;
			pDlg->m_ListBox.InsertString(0, temp);
			if (memcmp(m_Buffer, "LoginMyPassword", sizeof("LoginMyPassword")-1) == 0)
			{
				my_SendData = L"YourPasswordIsRight";
			}
		}
		else
		{
			if (memcmp(m_Buffer, "SearchFriendOnline", sizeof("SearchFriendOnline")-1) == 0)
			{
				my_SendData = L"Online";
			}
		}
	}


	AsyncSelect(FD_WRITE);

	CAsyncSocket::OnReceive(nErrorCode);
}


void NewSocket::OnSend(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (my_SendData != "")
	{
		int Length = 0;
		char Buffer[4096];
		memset(Buffer, 0, sizeof(Buffer));
		Length = WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength(), NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//ת��Ϊ�ֽ�Ϊ��λ
		Buffer[Length + 1] = '\0';
		Send(Buffer, Length, 0);

		C���������ҷ�������App *pApp = (C���������ҷ�������App*)AfxGetApp();
		C���������ҷ�������Dlg *pDlg = (C���������ҷ�������Dlg*)pApp->m_pMainWnd;
		CString tmp(Buffer), temp = L"���ͳ�:";temp += tmp;
		pDlg->m_ListBox.InsertString(0, temp);
	}
	
	AsyncSelect(FD_READ);

	CAsyncSocket::OnSend(nErrorCode);
}
