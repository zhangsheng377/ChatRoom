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

	CAsyncSocket::OnAccept(nErrorCode);
}
