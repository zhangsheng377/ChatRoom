#include "stdafx.h"
#include "NewSocket.h"
#include "���������ҿͻ���.h"
#include "���������ҿͻ���Dlg.h"


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
	// TODO:  �ڴ����ר�ô����/����û���
	if (nErrorCode == 0)
	{
		my_Connected = TRUE;
		AsyncSelect(FD_READ);
	}

	CAsyncSocket::OnConnect(nErrorCode);
}


void CNewSocket::OnReceive(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	memset(my_Buffer, 0, sizeof(my_Buffer));
	my_Length = Receive(my_Buffer, sizeof(my_Buffer), 0);
	if (my_Length > 0) my_Received = TRUE;

	C���������ҿͻ���App *pApp = (C���������ҿͻ���App*)AfxGetApp();
	C���������ҿͻ���Dlg *pDlg = (C���������ҿͻ���Dlg*)pApp->m_pMainWnd;
	if (memcmp(my_Buffer, "FriendIsOnline", sizeof("FriendIsOnline") - 1) == 0)
	{
		CString Account(&my_Buffer[sizeof("FriendIsOnline") - 1]);
		pDlg->m_pRecordSet.CreateInstance(__uuidof(Recordset));
		try
		{
			CString command1 = L"SELECT * FROM ���ѱ� WHERE �˺� = '";command1 += Account;command1 += L"'";
			pDlg->m_pRecordSet->Open(_variant_t(command1), pDlg->m_pClientDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		}
		catch (_com_error e)
		{
			CString errormessage;
			errormessage.Format(L"�����ݱ�ʧ��!\r\n������Ϣ:%s", e.ErrorMessage());
			AfxMessageBox(errormessage);
			//�����˳�������ͻ���
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
					pDlg->friends[i].isonline = 0;			//0��ʾ����
				}
				pDlg->m_FriendList.InsertItem(i, pDlg->friends[i].name, pDlg->friends[i].isonline);
			}
		}

		AsyncSelect(FD_READ);
	}
	else
	{
		if (memcmp(my_Buffer, "FriendIsOffline", sizeof("FriendIsOffline") - 1) == 0)
		{
			CString Account(&my_Buffer[sizeof("FriendIsOffline") - 1]);
			pDlg->m_pRecordSet.CreateInstance(__uuidof(Recordset));
			try
			{
				CString command1 = L"SELECT * FROM ���ѱ� WHERE �˺� = '";command1 += Account;command1 += L"'";
				pDlg->m_pRecordSet->Open(_variant_t(command1), pDlg->m_pClientDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			}
			catch (_com_error e)
			{
				CString errormessage;
				errormessage.Format(L"�����ݱ�ʧ��!\r\n������Ϣ:%s", e.ErrorMessage());
				AfxMessageBox(errormessage);
				//�����˳�������ͻ���
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
						pDlg->friends[i].isonline = 1;			//1��ʾ����
					}
					pDlg->m_FriendList.InsertItem(i, pDlg->friends[i].name, pDlg->friends[i].isonline);
				}
			}
		}

		AsyncSelect(FD_READ);
	}


	CAsyncSocket::OnReceive(nErrorCode);
}


