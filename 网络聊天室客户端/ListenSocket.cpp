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
	AfxMessageBox(L"������һ����������!");

	CAsyncSocket::OnAccept(nErrorCode);
}
