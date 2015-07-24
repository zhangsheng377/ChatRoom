#include "stdafx.h"
#include "NewSocket.h"
#include "网络聊天室服务器端Dlg.h"
#include "网络聊天室服务器端.h"


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
	// TODO:  在此添加专用代码和/或调用基类
	m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);

	C网络聊天室服务器端App *pApp = (C网络聊天室服务器端App*)AfxGetApp();
	C网络聊天室服务器端Dlg *pDlg = (C网络聊天室服务器端Dlg*)pApp->m_pMainWnd;
	CString tmp(m_Buffer), temp = L"接收到:";temp += tmp;
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
				WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
				Buffer[Length + 1] = '\0';
				Send(Buffer, Length, 0);
				CString tmp(Buffer), temp = L"发送出:";temp += tmp;
				pDlg->m_ListBox.InsertString(0, temp);
			}

			memset(m_Buffer, 0, sizeof(m_Buffer));
			do
			{
				m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);
			} while (m_Buffer[0]=='\0');
			CString tmp(m_Buffer), temp = L"接收到:";temp += tmp;
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
	// TODO:  在此添加专用代码和/或调用基类
	if (my_SendData != "")
	{
		int Length = 0;
		char Buffer[4096];
		memset(Buffer, 0, sizeof(Buffer));
		Length = WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength(), NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
		Buffer[Length + 1] = '\0';
		Send(Buffer, Length, 0);

		C网络聊天室服务器端App *pApp = (C网络聊天室服务器端App*)AfxGetApp();
		C网络聊天室服务器端Dlg *pDlg = (C网络聊天室服务器端Dlg*)pApp->m_pMainWnd;
		CString tmp(Buffer), temp = L"发送出:";temp += tmp;
		pDlg->m_ListBox.InsertString(0, temp);
	}
	
	AsyncSelect(FD_READ);

	CAsyncSocket::OnSend(nErrorCode);
}
