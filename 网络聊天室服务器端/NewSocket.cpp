#include "stdafx.h"
#include "NewSocket.h"
#include "���������ҷ�������Dlg.h"
#include "���������ҷ�������.h"


UINT BroadcastOnline(LPVOID lpParam)
{
	C���������ҷ�������Dlg *pDlg = (C���������ҷ�������Dlg*)lpParam;
	ListenSocket *pListenSocket = &pDlg->m_ListenSocket;
	std::vector<NewSocket*> *pVectorNewSocket = &pListenSocket->m_pNewSockets;
	int Length = 0;char Buffer[4096];CString SendData;
	/*
	for (int i = 0;i < pVectorNewSocket->size();i++)
	{
		if ((*pVectorNewSocket)[i]->my_Account != pListenSocket->my_NowAccount)
		{
			SendData = L"FriendIsOnline";SendData += pListenSocket->my_NowAccount;
			Length = 0;memset(Buffer, 0, sizeof(Buffer));
			Length = WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength(), NULL, 0, NULL, NULL);
			WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//ת��Ϊ�ֽ�Ϊ��λ
			Buffer[Length + 1] = '\0';
			(*pVectorNewSocket)[i]->Send(Buffer, Length, 0);

			CString tmp(Buffer), temp = L"��";temp += (*pVectorNewSocket)[i]->my_Account;temp += L"����:";temp += tmp;
			pDlg->m_ListBox.InsertString(0, temp);
		}
	}
	*/
	std::vector<NewSocket*>::iterator t;
	for (std::vector<NewSocket*>::iterator e = (*pVectorNewSocket).begin();e != (*pVectorNewSocket).end();e++)
	{
		if ((*e)->my_Account != pListenSocket->my_NowAccount)
		{
			if ((*e)->my_Account != L"")
			{
				SendData = L"FriendIsOnline";SendData += pListenSocket->my_NowAccount;
				Length = 0;memset(Buffer, 0, sizeof(Buffer));
				Length = WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength(), NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//ת��Ϊ�ֽ�Ϊ��λ
				Buffer[Length + 1] = '\0';
				(*e)->Send(Buffer, Length, 0);

				CString port;port.Format(L"%d", (*e)->my_Port);
				CString tmp(Buffer), temp = L"��";temp += (*e)->my_Account;temp += L":";temp += port;temp += L"����:";temp += tmp;
				pDlg->m_ListBox.InsertString(0, temp);
				
			}
			else
			{
				t = e - 1;
				(*pVectorNewSocket).erase(e);
				e = t;
			}
		}
	}
}

UINT BroadcastOffline(LPVOID lpParam)
{
	C���������ҷ�������Dlg *pDlg = (C���������ҷ�������Dlg*)lpParam;
	ListenSocket *pListenSocket = &pDlg->m_ListenSocket;
	std::vector<NewSocket*> *pVectorNewSocket = &pListenSocket->m_pNewSockets;
	int Length = 0;char Buffer[4096];CString SendData;
	//auto e = pVectorNewSocket->begin();
	/*
	for (int i = 0;i < pVectorNewSocket->size();i++)
	{
		if ((*pVectorNewSocket)[i]->my_Account != pListenSocket->my_NowAccount)
		{
			SendData = L"FriendIsOffline";SendData += pListenSocket->my_NowAccount;
			Length = 0;memset(Buffer, 0, sizeof(Buffer));
			Length = WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength(), NULL, 0, NULL, NULL);
			WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//ת��Ϊ�ֽ�Ϊ��λ
			Buffer[Length + 1] = '\0';
			(*pVectorNewSocket)[i]->Send(Buffer, Length, 0);

			CString tmp(Buffer), temp = L"��";temp += (*pVectorNewSocket)[i]->my_Account;temp += L"����:";temp += tmp;
			pDlg->m_ListBox.InsertString(0, temp);
		}
		if ((*e)->my_Account == pListenSocket->my_NowAccount)
		{
			pVectorNewSocket->erase(e);
			i--;
		}
		else
		{
			e++;
		}
	}
	*/
	std::vector<NewSocket*>::iterator t;
	for (std::vector<NewSocket*>::iterator e = (*pVectorNewSocket).begin();e != (*pVectorNewSocket).end();e++)
	{
		if ((*e)->my_Account != pListenSocket->my_NowAccount)
		{
			if ((*e)->my_Account != L"")
			{
				SendData = L"FriendIsOffline";SendData += pListenSocket->my_NowAccount;
				Length = 0;memset(Buffer, 0, sizeof(Buffer));
				Length = WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength(), NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//ת��Ϊ�ֽ�Ϊ��λ
				Buffer[Length + 1] = '\0';
				(*e)->Send(Buffer, Length, 0);

				CString port;port.Format(L"%d", (*e)->my_Port);
				CString tmp(Buffer), temp = L"��";temp += (*e)->my_Account;temp += L":";temp += port;temp += L"����:";temp += tmp;
				pDlg->m_ListBox.InsertString(0, temp);
			}
			else
			{
				t = e - 1;
				(*pVectorNewSocket).erase(e);
				e = t;
			}
		}
		else
		{
			t = e - 1;
			(*pVectorNewSocket).erase(e);
			e = t;
		}
	}
}


NewSocket::NewSocket()
{
	m_Length = 0;
	memset(m_Buffer, 0, sizeof(m_Buffer));
}


NewSocket::~NewSocket()
{
	if (m_hSocket != INVALID_SOCKET) Close();
}


void NewSocket::OnReceive(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	memset(m_Buffer, 0, sizeof(m_Buffer));
	m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);

	C���������ҷ�������App *pApp = (C���������ҷ�������App*)AfxGetApp();
	C���������ҷ�������Dlg *pDlg = (C���������ҷ�������Dlg*)pApp->m_pMainWnd;
	CString tmp(m_Buffer), temp = L"���յ�:";temp += tmp;
	pDlg->m_ListBox.InsertString(0, temp);

	if (memcmp(m_Buffer, "AmIConnected", sizeof("AmIConnected")-1) == 0)
	{
		my_SendData = L"YouAreConnected";
	}
	else
	{
		if (memcmp(m_Buffer, "LoginMyName", sizeof("LoginMyName")-1) == 0)
		{
			CString tmp1(&m_Buffer[sizeof("LoginMyName") - 1]);
			//if (tmp1!=L"")
			//{
				pDlg->m_pRecordSet.CreateInstance(__uuidof(Recordset));
				try
				{
					CString command1 = L"SELECT * FROM �û��� WHERE ���� = '";command1 += tmp1;command1 += L"'";
					pDlg->m_pRecordSet->Open(_variant_t(command1), pDlg->m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
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
					//pDlg->m_ListBox.InsertString(0, (CString)pDlg->m_pRecordSet->GetCollect("�˺�"));
					my_SendData = L"HereYouAre";
					if (my_SendData != "")
					{
						int Length = 0;
						char Buffer[4096];
						memset(Buffer, 0, sizeof(Buffer));
						Length = WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength(), NULL, 0, NULL, NULL);
						WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//ת��Ϊ�ֽ�Ϊ��λ
						Buffer[Length + 1] = '\0';
						Send(Buffer, Length, 0);
						CString tmp(Buffer), temp = L"���ͳ�:";temp += tmp;
						pDlg->m_ListBox.InsertString(0, temp);
					}

					memset(m_Buffer, 0, sizeof(m_Buffer));
					do
					{
						m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);
					} while (m_Buffer[0] == '\0');
					CString tmp(m_Buffer), temp = L"���յ�:";temp += tmp;
					pDlg->m_ListBox.InsertString(0, temp);
					if (memcmp(m_Buffer, "LoginMyPassword", sizeof("LoginMyPassword") - 1) == 0)
					{
						CString tmp6(&m_Buffer[sizeof("LoginMyPassword") - 1]);
						if ((CString)pDlg->m_pRecordSet->GetCollect("����") == tmp6)
						{
							my_SendData = L"YourPasswordIsRight";
							pDlg->m_pRecordSet->PutCollect("����", _variant_t(L"Online"));
							pDlg->m_pRecordSet->Update();
							my_Name = tmp1;
							my_Account = (CString)pDlg->m_pRecordSet->GetCollect("�˺�");

							pDlg->m_ListenSocket.my_NowAccount = my_Account;
							CWinThread *pThread = AfxBeginThread(BroadcastOnline, pDlg);

							/*
							CSocket test;
							AfxMessageBox(L"1!");
							if (test.m_hSocket == INVALID_SOCKET)
							{
								AfxMessageBox(L"2!");
								BOOL bFlag = test.Create(0, SOCK_STREAM);
								AfxMessageBox(L"3!");
								if (!bFlag)
								{
									AfxMessageBox(L"���������Ӵ�������!");
									test.Close();
									//PostQuitMessage(0);
									//return;
								}
							}
							//for (size_t i = 0; i < 10; i++)
							{
								AfxMessageBox(L"4!");
								test.Connect(my_IP, my_Port);
								AfxMessageBox(L"5!");
							}
							//test.Close();
							*/
						}
						else
						{
							my_SendData = L"YourPasswordIsWrong";
							pDlg->m_pRecordSet->PutCollect("����", _variant_t(L"Offline"));
							pDlg->m_pRecordSet->Update();
						}
					}
				}
				else
				{
					my_SendData = L"YouAreNotHere";
				}

				pDlg->m_pRecordSet->Close();
			//}
			//else
			//{
				//my_SendData = L"YourNameIsNull";
			//}
		}
		else
		{
			if (memcmp(m_Buffer, "SearchFriendOnline", sizeof("SearchFriendOnline")-1) == 0)
			{
				CString tmp2(&m_Buffer[sizeof("SearchFriendOnline") - 1]);
				pDlg->m_pRecordSet.CreateInstance(__uuidof(Recordset));
				try
				{
					CString command2 = L"SELECT * FROM �û��� WHERE �˺� = '";command2 += tmp2;command2 += L"'";
					pDlg->m_pRecordSet->Open(_variant_t(command2), pDlg->m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
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
					if ((CString)pDlg->m_pRecordSet->GetCollect("����") == L"Online")
					{
						my_SendData = L"Online";
					}
					else
					{
						my_SendData = L"Offline";
					}
				}
				else
				{
					//��ͻ��˷���,���޴���
					//......
				}

				pDlg->m_pRecordSet->Close();
			}
			else
			{
				if (memcmp(m_Buffer, "EnrollMyName", sizeof("EnrollMyName") - 1) == 0)
				{
					CString tmp4(&m_Buffer[sizeof("EnrollMyName") - 1]);
					//if (tmp4!=L"")
					//{
						pDlg->m_pRecordSet.CreateInstance(__uuidof(Recordset));
						try
						{
							CString command4 = L"SELECT * FROM �û��� WHERE ���� = '";command4 += tmp4;command4 += L"'";
							pDlg->m_pRecordSet->Open(_variant_t(command4), pDlg->m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
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
							my_SendData = L"HereYouAre";
						}
						else
						{
							my_SendData = L"YouAreNotHere";
							CString name = tmp4;
							if (my_SendData != "")
							{
								int Length = 0;
								char Buffer[4096];
								memset(Buffer, 0, sizeof(Buffer));
								Length = WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength(), NULL, 0, NULL, NULL);
								WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//ת��Ϊ�ֽ�Ϊ��λ
								Buffer[Length + 1] = '\0';
								Send(Buffer, Length, 0);
								CString tmp(Buffer), temp = L"���ͳ�:";temp += tmp;
								pDlg->m_ListBox.InsertString(0, temp);
							}

							memset(m_Buffer, 0, sizeof(m_Buffer));
							do
							{
								m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);
							} while (m_Buffer[0] == '\0');
							CString tmp(m_Buffer), temp = L"���յ�:";temp += tmp;
							pDlg->m_ListBox.InsertString(0, temp);
							if (memcmp(m_Buffer, "EnrollMyPassword", sizeof("EnrollMyPassword") - 1) == 0)
							{
								CString password(&m_Buffer[sizeof("EnrollMyPassword") - 1]);
								if (password!=L"")
								{
									pDlg->m_pRecordSet->AddNew();
									pDlg->my_MaxAccount++;
									CString MaxAccount;MaxAccount.Format(L"%d", pDlg->my_MaxAccount);
									pDlg->m_pRecordSet->PutCollect("�˺�", _variant_t(MaxAccount));
									pDlg->m_pRecordSet->PutCollect("����", _variant_t(name));
									pDlg->m_pRecordSet->PutCollect("����", _variant_t(password));
									pDlg->m_pRecordSet->PutCollect("����", _variant_t(L"Online"));
									pDlg->m_pRecordSet->Update();

									my_SendData = L"NowYouAreEnrolled";
								}
								else
								{
									my_SendData = L"YourPasswordIsNull";
								}
							}
							else
							{
								//ע�����δ���
								//......
							}
						}

						pDlg->m_pRecordSet->Close();
					//}
					//else
					//{
						//my_SendData = L"YourNameIsNull";
					//}
				}
				else
				{
					if (memcmp(m_Buffer, "IAmQuit", sizeof("IAmQuit") - 1) == 0)
					{
						pDlg->m_pRecordSet.CreateInstance(__uuidof(Recordset));
						try
						{
							CString command4 = L"SELECT * FROM �û��� WHERE ���� = '";command4 += my_Name;command4 += L"'";
							pDlg->m_pRecordSet->Open(_variant_t(command4), pDlg->m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
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
							pDlg->m_pRecordSet->PutCollect("����", _variant_t(L"Offline"));
							pDlg->m_pRecordSet->Update();
							//AfxMessageBox(L"�ѶϿ�����!");
							pDlg->m_ListenSocket.my_NowAccount = (CString)pDlg->m_pRecordSet->GetCollect("�˺�");
							CWinThread *pThread = AfxBeginThread(BroadcastOffline, pDlg);
							//Close();
						}
						
						pDlg->m_pRecordSet->Close();
						my_SendData = L"";
					}
				}
			}
		}
	}


	AsyncSelect(FD_WRITE);

	CAsyncSocket::OnReceive(nErrorCode);
}


void NewSocket::OnSend(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (my_SendData != "")
	{
		int Length = 0;
		char Buffer[4096];
		memset(Buffer, 0, sizeof(Buffer));
		Length = WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength(), NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//ת��Ϊ�ֽ�Ϊ��λ
		Buffer[Length + 1] = '\0';
		Send(Buffer, Length, 0);

		C���������ҷ�������App *pApp = (C���������ҷ�������App*)AfxGetApp();
		C���������ҷ�������Dlg *pDlg = (C���������ҷ�������Dlg*)pApp->m_pMainWnd;
		CString tmp(Buffer), temp = L"���ͳ�:";temp += tmp;
		pDlg->m_ListBox.InsertString(0, temp);
	}
	
	AsyncSelect(FD_READ);

	CAsyncSocket::OnSend(nErrorCode);
}


void NewSocket::OnClose(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	//AfxMessageBox(L"�ѶϿ�����!");
	

	CAsyncSocket::OnClose(nErrorCode);
}
