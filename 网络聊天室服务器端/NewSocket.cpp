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

	}

	CAsyncSocket::OnReceive(nErrorCode);
}
