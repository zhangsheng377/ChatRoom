#pragma once
#include "afxsock.h"
class CNewSocket :
	public CAsyncSocket
{
public:
	CNewSocket();
	~CNewSocket();

	UINT my_Length;
	char my_Buffer[4096];
	BOOL my_Connected;
	UINT my_Port;
	CString my_IP;
	int my_TryCount;
	int my_TryMax;
	virtual void OnConnect(int nErrorCode);
	BOOL my_Received;
	virtual void OnReceive(int nErrorCode);
	CString my_SendData;
	virtual void OnAccept(int nErrorCode);
};

