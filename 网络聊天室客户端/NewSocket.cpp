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
	// TODO:  �ڴ����ר�ô����/����û���
	if (nErrorCode == 0)
	{
		my_Connected = TRUE;
		AsyncSelect(FD_READ);
	}

	CAsyncSocket::OnConnect(nErrorCode);
}
