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
	// TODO:  �ڴ����ר�ô����/����û���
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
