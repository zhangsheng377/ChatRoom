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
	DDX_Control(pDX, IDC_LIST1, m_FriendList);
	DDX_Control(pDX, IDC_LIST1, m_FriendList);
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
	CRect rect;
	// 获取编程语言列表视图控件的位置和大小   
	m_FriendList.GetClientRect(&rect);
	// 为列表视图控件添加全行选中和栅格风格   
	m_FriendList.SetExtendedStyle(m_FriendList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加三列   
	m_FriendList.InsertColumn(0, _T("Online"), LVCFMT_CENTER, rect.Width() / 3, 0);
	m_FriendList.InsertColumn(1, _T("好友姓名"), LVCFMT_CENTER, rect.Width() / 3 * 2, 1);
	
	m_ShowWaitDlg = new ShowWaitDlg(this);
	if (m_ShowWaitDlg != NULL)
	{
		m_ShowWaitDlg->Create(IDD_DIALOG1, this);
	}
	m_ShowWaitDlg->ShowWindow(SW_SHOW);			//正在连接服务器

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

	//连接数据库
	HRESULT hr;
	try
	{
		//创建Connection对象
		hr = m_pClientDB.CreateInstance("ADODB.Connection");
		if (SUCCEEDED(hr))
		{
			hr = m_pClientDB->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=res/ClientDB.mdb", "", "", adModeUnknown);
			//连接数据库
		}
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"连接数据库失败!\r\n错误信息:%s", e.ErrorMessage());
		AfxMessageBox(errormessage);
		m_Socket.Close();
		PostQuitMessage(0);
	}
	_variant_t RecordsAffected;
	m_pRecordSet = m_pClientDB->Execute("SELECT COUNT(*) FROM 好友表", &RecordsAffected, adCmdText);
	_variant_t vIndex = (long)0;
	_variant_t vCount = m_pRecordSet->GetCollect(vIndex);
	int count = vCount.lVal;
	m_pRecordSet->Close();
	if (count == 0)
	{
		AfxMessageBox(L"数据表被破坏!");
		m_Socket.Close();
		PostQuitMessage(0);
	}
	m_pRecordSet.CreateInstance(__uuidof(Recordset));
	try
	{
		m_pRecordSet->Open("SELECT * FROM 好友表", m_pClientDB.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format(L"打开数据表失败!\r\n错误信息:%s", e.ErrorMessage());
		AfxMessageBox(errormessage);
		m_Socket.Close();
		PostQuitMessage(0);
	}
	



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
				m_Socket.Close();
				PostQuitMessage(0);
				return;
			}
			else
			{
				m_Socket.Send("AmIConnected", sizeof("AmIConnected") - 1);	//不减1就会多发一个.点
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
				AfxMessageBox(L"服务器无应答!");
				m_Socket.Close();
				PostQuitMessage(0);
				return;
			}
			else
			{
				BOOL cmp = !memcmp(m_Socket.my_Buffer, "YouAreConnected", sizeof("YouAreConnected"));	//相等为0
				if (cmp)
				{
					//AfxMessageBox(L"服务器已连接!");
					m_ShowWaitDlg->SetWindowTextW(L"正在更新好友信息!请勿操作!");
					ShowWindow(SW_SHOW);
					FreshFriendList();
				}
				else
				{
					AfxMessageBox(L"服务器应答错误!可能不是正确的服务器或是网络有干扰!");
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


void C网络聊天室客户端Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO:  在此处添加消息处理程序代码
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


UINT C网络聊天室客户端Dlg::WaitToConnectServer(LPVOID pParam)
{
	lpthread temp = (lpthread)pParam;

	return 0;
}


void C网络聊天室客户端Dlg::FreshFriendList()
{
	m_FriendList.DeleteAllItems();
	m_pRecordSet->MoveFirst();
	FRIEND temp;
	while(!m_pRecordSet->adoEOF)
	{
		temp.account = (int)m_pRecordSet->GetCollect("账号");
		temp.name = (CString)m_pRecordSet->GetCollect("姓名");
		friends.push_back(temp);
		m_pRecordSet->MoveNext();
	} 

	m_ShowWaitDlg->DestroyWindow();
}
