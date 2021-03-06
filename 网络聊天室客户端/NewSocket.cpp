#include "stdafx.h"
#include "NewSocket.h"
#include "网络聊天室客户端.h"
#include "网络聊天室客户端Dlg.h"


CNewSocket::CNewSocket()
{
	my_Length = 0;
	memset(my_Buffer, 0, sizeof(my_Buffer));
	my_Connected = FALSE;
	my_TryCount = 0;
	my_TryMax = 10;
	my_Received = FALSE;
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
		//AsyncSelect(FD_READ);
	}

	CAsyncSocket::OnConnect(nErrorCode);
}


void CNewSocket::OnReceive(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	memset(my_Buffer, 0, sizeof(my_Buffer));
	my_Length = Receive(my_Buffer, sizeof(my_Buffer), 0);
	if (my_Length > 0) my_Received = TRUE;

	C网络聊天室客户端App *pApp = (C网络聊天室客户端App*)AfxGetApp();
	C网络聊天室客户端Dlg *pDlg = (C网络聊天室客户端Dlg*)pApp->m_pMainWnd;
	CString tempcommand(my_Buffer);
	pDlg->m_CommandListBox.InsertString(0, tempcommand);
	
	if (memcmp(my_Buffer, "FriendIsOnline", sizeof("FriendIsOnline") - 1) == 0)
	{
		CString Account(&my_Buffer[sizeof("FriendIsOnline") - 1]);
		pDlg->m_pRecordSet.CreateInstance(__uuidof(Recordset));
		try
		{
			CString command1 = L"SELECT * FROM 好友表 WHERE 账号 = '";command1 += Account;command1 += L"'";
			pDlg->m_pRecordSet->Open(_variant_t(command1), pDlg->m_pClientDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		}
		catch (_com_error e)
		{
			CString errormessage;
			errormessage.Format(L"打开数据表失败!\r\n错误信息:%s", e.ErrorMessage());
			AfxMessageBox(errormessage);
			//发出退出命令给客户端
			//......
			PostQuitMessage(0);
		}
		if (!pDlg->m_pRecordSet->adoEOF)
		{
			pDlg->m_FriendList.DeleteAllItems();

			for (UINT i = 0;i < pDlg->friends.size();i++)
			{
				if (pDlg->friends[i].account == Account)
				{
					pDlg->friends[i].isonline = 0;			//0表示在线
				}
				pDlg->m_FriendList.InsertItem(i, pDlg->friends[i].name, pDlg->friends[i].isonline);
			}
		}

		//AsyncSelect(FD_READ);
	}
	else
	{
		if (memcmp(my_Buffer, "FriendIsOffline", sizeof("FriendIsOffline") - 1) == 0)
		{
			CString Account(&my_Buffer[sizeof("FriendIsOffline") - 1]);
			pDlg->m_pRecordSet.CreateInstance(__uuidof(Recordset));
			try
			{
				CString command1 = L"SELECT * FROM 好友表 WHERE 账号 = '";command1 += Account;command1 += L"'";
				pDlg->m_pRecordSet->Open(_variant_t(command1), pDlg->m_pClientDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			}
			catch (_com_error e)
			{
				CString errormessage;
				errormessage.Format(L"打开数据表失败!\r\n错误信息:%s", e.ErrorMessage());
				AfxMessageBox(errormessage);
				//发出退出命令给客户端
				//......
				PostQuitMessage(0);
			}
			if (!pDlg->m_pRecordSet->adoEOF)
			{
				pDlg->m_FriendList.DeleteAllItems();

				for (UINT i = 0;i < pDlg->friends.size();i++)
				{
					if (pDlg->friends[i].account == Account)
					{
						pDlg->friends[i].isonline = 1;			//1表示离线
					}
					pDlg->m_FriendList.InsertItem(i, pDlg->friends[i].name, pDlg->friends[i].isonline);
				}
			}

			//AsyncSelect(FD_READ);
		}
		else
		{
			if (memcmp(my_Buffer, "ReceiveFrom", sizeof("ReceiveFrom") - 1) == 0)
			{
				char tempaccount[20];memset(tempaccount, 0, sizeof(tempaccount));
				memcpy(tempaccount, &my_Buffer[sizeof("ReceiveFrom") - 1], 5);
				CString account(tempaccount);
				CString data(&my_Buffer[sizeof("ReceiveFrom12345") - 1]);

				for (UINT i = 0;i < pDlg->friends.size();i++)
				{
					if (pDlg->friends[i].account == account)
					{
						if (pDlg->friends[i].IsChatting == TRUE)
						{
							CString tmpstring = pDlg->friends[i].name;tmpstring += L" 说:";tmpstring += data;
							pDlg->friends[i].m_ChatDlg->m_ChatListBox.InsertString(0, tmpstring);
						}
						else
						{
							pDlg->m_FriendList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
							pDlg->OnNMDblclkList1(NULL,0);
							CString tmpstring = pDlg->friends[i].name;tmpstring += L" 说:";tmpstring += data;
							pDlg->friends[i].m_ChatDlg->m_ChatListBox.InsertString(0, tmpstring);
						}
						break;
					}
				}

			}
		}
	}

	AsyncSelect(FD_READ);

	CAsyncSocket::OnReceive(nErrorCode);
}




void CNewSocket::OnAccept(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	/*
	AfxMessageBox(L"已侦听到一个连接!");
	CNewSocket *test = new CNewSocket();
	if (Accept(*test))
	{
		
	}
	else
	{
		delete test;
	}
	*/
	CAsyncSocket::OnAccept(nErrorCode);
}
