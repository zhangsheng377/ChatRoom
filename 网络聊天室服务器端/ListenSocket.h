#pragma once
#include "afxsock.h"
#include "NewSocket.h"
#include <vector>
class ListenSocket :
	public CAsyncSocket
{
public:
	ListenSocket();
	~ListenSocket();

	//NewSocket* m_pSocket;
	std::vector<NewSocket*> m_pNewSockets;
	//BOOL Accepted;
	virtual void OnAccept(int nErrorCode);
};

