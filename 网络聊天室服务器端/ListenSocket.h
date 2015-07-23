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

	std::vector<NewSocket> m_Sockets;
	virtual void OnAccept(int nErrorCode);
};

