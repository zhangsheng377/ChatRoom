#include "stdafx.h"
#include "ListenSocket.h"

/*
UINT ListenThread(LPVOID lpParam)
{
	//AfxMessageBox(L"进入线程!");
	//std::vector<ListenSocket*> *pListenSockets = (std::vector<ListenSocket*>*)lpParam;
	ListenSocket *ptemp = (ListenSocket*)lpParam;

	NewSocket *pSocket = new NewSocket();
	while (!ptemp->Accept(*pSocket))
	{
	}
	pSocket->AsyncSelect(FD_READ);
	ptemp->m_pNewSockets.push_back(pSocket);
	//AfxMessageBox(L"Socket成功监听到一个!");
	//delete pSocket;

	return 0;
}*/


ListenSocket::ListenSocket()
{
	//Accepted = FALSE;
}


ListenSocket::~ListenSocket()
{
}



void ListenSocket::OnAccept(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	//CWinThread *pThread = AfxBeginThread(ListenThread, this);
	NewSocket *pSocket = new NewSocket();
	if (Accept(*pSocket))
	{
		pSocket->AsyncSelect(FD_READ);
		
		//pSocket->GetPeerName(pSocket->my_IP, pSocket->my_Port);
		
		m_pNewSockets.push_back(pSocket);
	}
	else
	{
		delete pSocket;
	}

	CAsyncSocket::OnAccept(nErrorCode);
}
