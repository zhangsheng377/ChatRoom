// ���������ҿͻ���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������ҿͻ���.h"
#include "���������ҿͻ���Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C���������ҿͻ���Dlg �Ի���



C���������ҿͻ���Dlg::C���������ҿͻ���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C���������ҿͻ���Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C���������ҿͻ���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_FriendList);
	DDX_Control(pDX, IDC_LIST1, m_FriendList);
}

BEGIN_MESSAGE_MAP(C���������ҿͻ���Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()


// C���������ҿͻ���Dlg ��Ϣ�������

BOOL C���������ҿͻ���Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CRect rect;
	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_FriendList.GetClientRect(&rect);
	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_FriendList.SetExtendedStyle(m_FriendList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// Ϊ�б���ͼ�ؼ��������   
	m_FriendList.InsertColumn(0, _T("Online"), LVCFMT_CENTER, rect.Width() / 3, 0);
	m_FriendList.InsertColumn(1, _T("��������"), LVCFMT_CENTER, rect.Width() / 3 * 2, 1);
	
	m_ShowWaitDlg = new ShowWaitDlg(this);
	if (m_ShowWaitDlg != NULL)
	{
		m_ShowWaitDlg->Create(IDD_DIALOG1, this);
	}
	m_ShowWaitDlg->ShowWindow(SW_SHOW);			//�������ӷ�����

	m_Socket.my_Port = 32137;
	m_Socket.my_IP = "zhangsheng377.wicp.net";
	m_Socket.ShutDown(2);
	m_Socket.m_hSocket = INVALID_SOCKET;
	m_Socket.my_Connected = FALSE;
	m_Socket.my_TryCount = 0;
	SetTimer(1, 1000, NULL);
	/*
	thread m_thread;
	m_thread.m_Socket = &m_Socket;
	m_thread.m_ShowWaitDlg = m_ShowWaitDlg;
	m_thread.m_Wind = this;
	CWinThread* mythread = AfxBeginThread(
		(AFX_THREADPROC)WaitToConnectServer,
		&m_thread,
		THREAD_PRIORITY_NORMAL,
		0,
		0,
		NULL
		);
	*/

	//�������ݿ�
	HRESULT hr;
	try
	{
		//����Connection����
		hr = m_pClientDB.CreateInstance("ADODB.Connection");
		if (SUCCEEDED(hr))
		{
			hr = m_pClientDB->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=res/ClientDB.mdb", "", "", adModeUnknown);
			//�������ݿ�
		}
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"�������ݿ�ʧ��!\r\n������Ϣ:%s", e.ErrorMessage());
		AfxMessageBox(errormessage);
		m_Socket.Close();
		PostQuitMessage(0);
	}
	_variant_t RecordsAffected;
	m_pRecordSet = m_pClientDB->Execute("SELECT COUNT(*) FROM ���ѱ�", &RecordsAffected, adCmdText);
	_variant_t vIndex = (long)0;
	_variant_t vCount = m_pRecordSet->GetCollect(vIndex);
	int count = vCount.lVal;
	m_pRecordSet->Close();
	if (count == 0)
	{
		AfxMessageBox(L"���ݱ��ƻ�!");
		m_Socket.Close();
		PostQuitMessage(0);
	}
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordSet->Open("SELECT * FROM ���ѱ�", m_pClientDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"�����ݱ�ʧ��!\r\n������Ϣ:%s", e.ErrorMessage());
		AfxMessageBox(errormessage);
		m_Socket.Close();
		PostQuitMessage(0);
	}
	



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C���������ҿͻ���Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C���������ҿͻ���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C���������ҿͻ���Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		if (m_Socket.m_hSocket == INVALID_SOCKET)
		{
			BOOL bFlag = m_Socket.Create(0, SOCK_STREAM, FD_CONNECT);
			if (!bFlag)
			{
				AfxMessageBox(L"���������Ӵ�������!");
				m_Socket.Close();
				PostQuitMessage(0);
				return;
			}
		}
		m_Socket.Connect(m_Socket.my_IP, m_Socket.my_Port);
		m_Socket.my_TryCount++;
		if (m_Socket.my_TryCount >= m_Socket.my_TryMax || m_Socket.my_Connected)
		{
			KillTimer(1);
			if (m_Socket.my_TryCount >= m_Socket.my_TryMax)
			{
				AfxMessageBox(L"���������ӳ�ʱ!");
				m_Socket.Close();
				PostQuitMessage(0);
				return;
			}
			else
			{
				m_Socket.Send("AmIConnected", sizeof("AmIConnected") - 1);	//����1�ͻ�෢һ��.��
				m_Socket.my_TryCount = 0;
				SetTimer(2, 1000, NULL);
				m_Socket.AsyncSelect(FD_READ);
			}
			return;
		}
		break;
	case 2:
		m_Socket.my_TryCount++;
		if (m_Socket.my_TryCount >= m_Socket.my_TryMax || m_Socket.my_Received)
		{
			KillTimer(2);
			if (m_Socket.my_TryCount >= m_Socket.my_TryMax)
			{
				m_Socket.my_Connected = FALSE;
				AfxMessageBox(L"��������Ӧ��!");
				m_Socket.Close();
				PostQuitMessage(0);
				return;
			}
			else
			{
				BOOL cmp = !memcmp(m_Socket.my_Buffer, "YouAreConnected", sizeof("YouAreConnected"));	//���Ϊ0
				if (cmp)
				{
					//AfxMessageBox(L"������������!");
					m_ShowWaitDlg->SetWindowTextW(L"���ڸ��º�����Ϣ!�������!");
					ShowWindow(SW_SHOW);
					FreshFriendList();
				}
				else
				{
					AfxMessageBox(L"������Ӧ�����!���ܲ�����ȷ�ķ��������������и���!");
					m_Socket.Close();
					PostQuitMessage(0);
					return;
				}
			}	
		}
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void C���������ҿͻ���Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO:  �ڴ˴������Ϣ����������
}


void C���������ҿͻ���Dlg::OnNcPaint()
{
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnNcPaint()
	static int i = 1;
	if (i > 0)
	{
		i--;
		ShowWindow(SW_HIDE);
	}
	else
		CDialogEx::OnNcPaint();
}


UINT C���������ҿͻ���Dlg::WaitToConnectServer(LPVOID pParam)
{
	lpthread temp = (lpthread)pParam;

	return 0;
}


void C���������ҿͻ���Dlg::FreshFriendList()
{
	m_FriendList.DeleteAllItems();
	m_pRecordSet->MoveFirst();
	FRIEND temp;
	while(!m_pRecordSet->adoEOF)
	{
		temp.account = (int)m_pRecordSet->GetCollect("�˺�");
		temp.name = (CString)m_pRecordSet->GetCollect("����");
		friends.push_back(temp);
		m_pRecordSet->MoveNext();
	} 

	m_ShowWaitDlg->DestroyWindow();
}
