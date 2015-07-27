#include "stdafx.h"
#include "NewSocket.h"
#include "网络聊天室服务器端Dlg.h"
#include "网络聊天室服务器端.h"


UINT BroadcastOnline(LPVOID lpParam)
{
	C网络聊天室服务器端Dlg *pDlg = (C网络聊天室服务器端Dlg*)lpParam;
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
			WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
			Buffer[Length + 1] = '\0';
			(*pVectorNewSocket)[i]->Send(Buffer, Length, 0);

			CString tmp(Buffer), temp = L"向";temp += (*pVectorNewSocket)[i]->my_Account;temp += L"发出:";temp += tmp;
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
				WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
				Buffer[Length + 1] = '\0';
				(*e)->Send(Buffer, Length, 0);

				CString port;port.Format(L"%d", (*e)->my_Port);
				CString tmp(Buffer), temp = L"向";temp += (*e)->my_Account;temp += L":";temp += port;temp += L"发出:";temp += tmp;
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
	C网络聊天室服务器端Dlg *pDlg = (C网络聊天室服务器端Dlg*)lpParam;
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
			WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
			Buffer[Length + 1] = '\0';
			(*pVectorNewSocket)[i]->Send(Buffer, Length, 0);

			CString tmp(Buffer), temp = L"向";temp += (*pVectorNewSocket)[i]->my_Account;temp += L"发出:";temp += tmp;
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
				WideCharToMultiByte(CP_ACP, 0, SendData, SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
				Buffer[Length + 1] = '\0';
				(*e)->Send(Buffer, Length, 0);

				CString port;port.Format(L"%d", (*e)->my_Port);
				CString tmp(Buffer), temp = L"向";temp += (*e)->my_Account;temp += L":";temp += port;temp += L"发出:";temp += tmp;
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
	// TODO:  在此添加专用代码和/或调用基类
	memset(m_Buffer, 0, sizeof(m_Buffer));
	m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);

	C网络聊天室服务器端App *pApp = (C网络聊天室服务器端App*)AfxGetApp();
	C网络聊天室服务器端Dlg *pDlg = (C网络聊天室服务器端Dlg*)pApp->m_pMainWnd;
	CString tmp(m_Buffer), temp = L"接收到:";temp += tmp;
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
					CString command1 = L"SELECT * FROM 用户表 WHERE 姓名 = '";command1 += tmp1;command1 += L"'";
					pDlg->m_pRecordSet->Open(_variant_t(command1), pDlg->m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
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
					//pDlg->m_ListBox.InsertString(0, (CString)pDlg->m_pRecordSet->GetCollect("账号"));
					my_SendData = L"HereYouAre";
					if (my_SendData != "")
					{
						int Length = 0;
						char Buffer[4096];
						memset(Buffer, 0, sizeof(Buffer));
						Length = WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength(), NULL, 0, NULL, NULL);
						WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
						Buffer[Length + 1] = '\0';
						Send(Buffer, Length, 0);
						CString tmp(Buffer), temp = L"发送出:";temp += tmp;
						pDlg->m_ListBox.InsertString(0, temp);
					}

					memset(m_Buffer, 0, sizeof(m_Buffer));
					do
					{
						m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);
					} while (m_Buffer[0] == '\0');
					CString tmp(m_Buffer), temp = L"接收到:";temp += tmp;
					pDlg->m_ListBox.InsertString(0, temp);
					if (memcmp(m_Buffer, "LoginMyPassword", sizeof("LoginMyPassword") - 1) == 0)
					{
						CString tmp6(&m_Buffer[sizeof("LoginMyPassword") - 1]);
						if ((CString)pDlg->m_pRecordSet->GetCollect("密码") == tmp6)
						{
							my_SendData = L"YourPasswordIsRight";
							pDlg->m_pRecordSet->PutCollect("在线", _variant_t(L"Online"));
							pDlg->m_pRecordSet->Update();
							my_Name = tmp1;
							my_Account = (CString)pDlg->m_pRecordSet->GetCollect("账号");

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
									AfxMessageBox(L"服务器连接创建错误!");
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
							pDlg->m_pRecordSet->PutCollect("在线", _variant_t(L"Offline"));
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
					CString command2 = L"SELECT * FROM 用户表 WHERE 账号 = '";command2 += tmp2;command2 += L"'";
					pDlg->m_pRecordSet->Open(_variant_t(command2), pDlg->m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
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
					if ((CString)pDlg->m_pRecordSet->GetCollect("在线") == L"Online")
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
					//向客户端发送,查无此人
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
							CString command4 = L"SELECT * FROM 用户表 WHERE 姓名 = '";command4 += tmp4;command4 += L"'";
							pDlg->m_pRecordSet->Open(_variant_t(command4), pDlg->m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
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
								WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
								Buffer[Length + 1] = '\0';
								Send(Buffer, Length, 0);
								CString tmp(Buffer), temp = L"发送出:";temp += tmp;
								pDlg->m_ListBox.InsertString(0, temp);
							}

							memset(m_Buffer, 0, sizeof(m_Buffer));
							do
							{
								m_Length = Receive(m_Buffer, sizeof(m_Buffer), 0);
							} while (m_Buffer[0] == '\0');
							CString tmp(m_Buffer), temp = L"接收到:";temp += tmp;
							pDlg->m_ListBox.InsertString(0, temp);
							if (memcmp(m_Buffer, "EnrollMyPassword", sizeof("EnrollMyPassword") - 1) == 0)
							{
								CString password(&m_Buffer[sizeof("EnrollMyPassword") - 1]);
								if (password!=L"")
								{
									pDlg->m_pRecordSet->AddNew();
									pDlg->my_MaxAccount++;
									CString MaxAccount;MaxAccount.Format(L"%d", pDlg->my_MaxAccount);
									pDlg->m_pRecordSet->PutCollect("账号", _variant_t(MaxAccount));
									pDlg->m_pRecordSet->PutCollect("姓名", _variant_t(name));
									pDlg->m_pRecordSet->PutCollect("密码", _variant_t(password));
									pDlg->m_pRecordSet->PutCollect("在线", _variant_t(L"Online"));
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
								//注册过程未完成
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
							CString command4 = L"SELECT * FROM 用户表 WHERE 姓名 = '";command4 += my_Name;command4 += L"'";
							pDlg->m_pRecordSet->Open(_variant_t(command4), pDlg->m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
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
							pDlg->m_pRecordSet->PutCollect("在线", _variant_t(L"Offline"));
							pDlg->m_pRecordSet->Update();
							//AfxMessageBox(L"已断开连接!");
							pDlg->m_ListenSocket.my_NowAccount = (CString)pDlg->m_pRecordSet->GetCollect("账号");
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
	// TODO:  在此添加专用代码和/或调用基类
	if (my_SendData != "")
	{
		int Length = 0;
		char Buffer[4096];
		memset(Buffer, 0, sizeof(Buffer));
		Length = WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength(), NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, my_SendData, my_SendData.GetLength() + 1, Buffer, Length + 1, NULL, NULL);	//转换为字节为单位
		Buffer[Length + 1] = '\0';
		Send(Buffer, Length, 0);

		C网络聊天室服务器端App *pApp = (C网络聊天室服务器端App*)AfxGetApp();
		C网络聊天室服务器端Dlg *pDlg = (C网络聊天室服务器端Dlg*)pApp->m_pMainWnd;
		CString tmp(Buffer), temp = L"发送出:";temp += tmp;
		pDlg->m_ListBox.InsertString(0, temp);
	}
	
	AsyncSelect(FD_READ);

	CAsyncSocket::OnSend(nErrorCode);
}


void NewSocket::OnClose(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	//AfxMessageBox(L"已断开连接!");
	

	CAsyncSocket::OnClose(nErrorCode);
}
