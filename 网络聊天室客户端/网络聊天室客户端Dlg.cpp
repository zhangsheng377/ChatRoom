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
	//ShowWindow(SW_HIDE);

	ShowWaitDlg *m_ShowWaitDlg;
	m_ShowWaitDlg = new ShowWaitDlg(this);
	if (m_ShowWaitDlg != NULL)
	{
		m_ShowWaitDlg->Create(IDD_DIALOG1, this);
	}
	m_ShowWaitDlg->ShowWindow(SW_SHOW);

	HRESULT hr;
	try
	{
		//����Connection����
		hr = m_ClientDB.CreateInstance("ADODB.Connection");
		if (SUCCEEDED(hr))
		{
			hr = m_ClientDB->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=res/ClientDB.mdb", "", "", adModeUnknown);
			//�������ݿ�
		}
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"�������ݿ�ʧ��!\r\n������Ϣ:%s", e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
	try
	{
		_variant_t RecordsAffected;
		m_ClientDB->Execute("CREATE TABLE ���ѱ�(�˺� INT,���� TEXT,���� INT)", &RecordsAffected, adCmdText);	//������
	}
	catch (_com_error e)
	{
		//CString errormessage;
		//errormessage.Format(L"���ݿ������б�!\r\n������Ϣ:%s", e.ErrorMessage());
		//AfxMessageBox(errormessage);
	}

	m_Socket.my_Port = 32137;
	m_Socket.my_IP = "zhangsheng377.wicp.net";
	m_Socket.ShutDown(2);
	m_Socket.m_hSocket = INVALID_SOCKET;
	m_Socket.my_Connected = FALSE;
	m_Socket.my_TryCount = 0;
	SetTimer(1, 1000, NULL);

	//m_ShowWaitDlg->ShowWindow(SW_HIDE);
	m_ShowWaitDlg->DestroyWindow();
	//ShowWindow(SW_SHOW);

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
			}
			else
			{
				
			}
			return;
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
	//ShowWindow(SW_HIDE);
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
