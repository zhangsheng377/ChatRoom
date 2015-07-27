#pragma once
#include "afxsock.h"
class ListenSocket :
	public CAsyncSocket
{
public:
	ListenSocket();
	~ListenSocket();
	virtual void OnAccept(int nErrorCode);
};

