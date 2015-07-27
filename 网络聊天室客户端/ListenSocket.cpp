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
	// TODO:  在此添加专用代码和/或调用基类
	AfxMessageBox(L"监听到一个连接请求!");

	CAsyncSocket::OnAccept(nErrorCode);
}
