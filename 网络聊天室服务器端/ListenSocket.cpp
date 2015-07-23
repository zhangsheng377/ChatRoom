#include "stdafx.h"
#include "ListenSocket.h"


ListenSocket::ListenSocket()
{
}


ListenSocket::~ListenSocket()
{
}


void ListenSocket::OnAccept(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	NewSocket *m_pSocket = new NewSocket();
	if (Accept(*m_pSocket))
	{
		m_pSocket->AsyncSelect(FD_READ);
		m_pSockets.push_back(m_pSocket);
	}
	else
	{
		delete m_pSocket;
	}

	CAsyncSocket::OnAccept(nErrorCode);
}
