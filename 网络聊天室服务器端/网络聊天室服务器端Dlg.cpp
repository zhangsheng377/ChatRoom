
// ���������ҷ�������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������ҷ�������.h"
#include "���������ҷ�������Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C���������ҷ�������Dlg �Ի���



C���������ҷ�������Dlg::C���������ҷ�������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C���������ҷ�������Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C���������ҷ�������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C���������ҷ�������Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// C���������ҷ�������Dlg ��Ϣ�������

BOOL C���������ҷ�������Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//�������ݿ�
	HRESULT hr;
	try
	{
		//����Connection����
		hr = m_pServerDB.CreateInstance("ADODB.Connection");
		if (SUCCEEDED(hr))
		{
			hr = m_pServerDB->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=res/ServerDB.mdb", "", "", adModeUnknown);
			//�������ݿ�
		}
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"�������ݿ�ʧ��!\r\n������Ϣ:%s", e.ErrorMessage());
		AfxMessageBox(errormessage);
		//AfxMessageBox("fasadf");
		PostQuitMessage(0);
	}
	
	_variant_t RecordsAffected;
	m_pServerDB->Execute("UPDATE �û��� SET ���� = '0'", &RecordsAffected, adCmdText);
	m_pRecordSet = m_pServerDB->Execute("SELECT COUNT(*) FROM �û���", &RecordsAffected, adCmdText);
	_variant_t vIndex = (long)0;
	_variant_t vCount = m_pRecordSet->GetCollect(vIndex);
	int count = vCount.lVal;
	m_pRecordSet->Close();
	if (count == 0)
	{
		AfxMessageBox(L"���ݱ��ƻ�!");
		PostQuitMessage(0);
	}

	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordSet->Open("SELECT * FROM �û���", m_pServerDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"�����ݱ�ʧ��!\r\n������Ϣ:%s", e.ErrorMessage());
		AfxMessageBox(errormessage);
		PostQuitMessage(0);
	}


	//����Socket
	if (m_ListenSocket.m_hSocket == INVALID_SOCKET)
	{
		BOOL bFlag = m_ListenSocket.Create(5088, SOCK_STREAM, FD_ACCEPT);
		if (!bFlag)
		{
			AfxMessageBox(L"Socket����ʧ��!");
			m_ListenSocket.Close();
			PostQuitMessage(0);
		}
	}
	if (!m_ListenSocket.Listen(1))
	{
		int nErrorCode = m_ListenSocket.GetLastError();
		if (nErrorCode != WSAEWOULDBLOCK)
		{
			AfxMessageBox(L"Socket����!");
			m_ListenSocket.Close();
			PostQuitMessage(0);
		}
	}


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C���������ҷ�������Dlg::OnPaint()
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
HCURSOR C���������ҷ�������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

