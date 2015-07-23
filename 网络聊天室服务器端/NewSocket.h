#pragma once
#include "afxsock.h"
class NewSocket :
	public CAsyncSocket
{
public:
	NewSocket();
	~NewSocket();

	UINT m_Length;
	char m_Buffer[4096];
	CString my_SendData;
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};

