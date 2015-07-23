#include "stdafx.h"
#include "NewSocket.h"


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
	if (memcmp(m_Buffer, "AmIConnected", m_Length) == 0)
	{
		my_SendData = L"YouAreConnected";
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
		Buffer[Length + 1] = '/0';
		Send(Buffer, Length, 0);
	}
	
	AsyncSelect(FD_READ);

	CAsyncSocket::OnSend(nErrorCode);
}
