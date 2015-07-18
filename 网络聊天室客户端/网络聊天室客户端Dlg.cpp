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

