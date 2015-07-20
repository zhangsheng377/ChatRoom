// 网络聊天室客户端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "网络聊天室客户端.h"
#include "网络聊天室客户端Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C网络聊天室客户端Dlg 对话框



C网络聊天室客户端Dlg::C网络聊天室客户端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C网络聊天室客户端Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C网络聊天室客户端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C网络聊天室客户端Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()


// C网络聊天室客户端Dlg 消息处理程序

BOOL C网络聊天室客户端Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
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
		//创建Connection对象
		hr = m_ClientDB.CreateInstance("ADODB.Connection");
		if (SUCCEEDED(hr))
		{
			hr = m_ClientDB->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=res/ClientDB.mdb", "", "", adModeUnknown);
			//连接数据库
		}
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"连接数据库失败!\r\n错误信息:%s", e.ErrorMessage());
		AfxMessageBox(errormessage);
	}
	try
	{
		_variant_t RecordsAffected;
		m_ClientDB->Execute("CREATE TABLE 好友表(账号 INT,姓名 TEXT,在线 INT)", &RecordsAffected, adCmdText);	//创建表
	}
	catch (_com_error e)
	{
		//CString errormessage;
		//errormessage.Format(L"数据库中已有表!\r\n错误信息:%s", e.ErrorMessage());
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C网络聊天室客户端Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C网络聊天室客户端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C网络聊天室客户端Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		if (m_Socket.m_hSocket == INVALID_SOCKET)
		{
			BOOL bFlag = m_Socket.Create(0, SOCK_STREAM, FD_CONNECT);
			if (!bFlag)
			{
				AfxMessageBox(L"服务器连接创建错误!");
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
				AfxMessageBox(L"服务器连接超时!");
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


void C网络聊天室客户端Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO:  在此处添加消息处理程序代码
	//ShowWindow(SW_HIDE);
}


void C网络聊天室客户端Dlg::OnNcPaint()
{
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnNcPaint()
	static int i = 1;
	if (i > 0)
	{
		i--;
		ShowWindow(SW_HIDE);
	}
	else
		CDialogEx::OnNcPaint();
}
