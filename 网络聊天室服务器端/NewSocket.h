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
	virtual void OnReceive(int nErrorCode);
};

