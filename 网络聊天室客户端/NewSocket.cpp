#include "stdafx.h"
#include "NewSocket.h"


CNewSocket::CNewSocket()
{
	my_Length = 0;
	memset(my_Buffer, 0, sizeof(my_Buffer));
	my_Connected = FALSE;
	my_TryCount = 0;
	my_TryMax = 10;
}


CNewSocket::~CNewSocket()
{
	if (m_hSocket != INVALID_SOCKET) Close();
}


void CNewSocket::OnConnect(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (nErrorCode == 0)
	{
		my_Connected = TRUE;
		AsyncSelect(FD_READ);
	}

	CAsyncSocket::OnConnect(nErrorCode);
}
