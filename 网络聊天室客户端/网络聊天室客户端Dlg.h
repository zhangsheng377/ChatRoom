
// ���������ҿͻ���Dlg.h : ͷ�ļ�
//

#include "ShowWaitDlg.h"
#include "NewSocket.h"

#pragma once


// C���������ҿͻ���Dlg �Ի���
class C���������ҿͻ���Dlg : public CDialogEx
{
// ����
public:
	C���������ҿͻ���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	_ConnectionPtr m_ClientDB;				//����ADO���ݿ�,�����ɵ�.tlh���Ƶ���Ŀ�ļ�����
	CNewSocket m_Socket;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnNcPaint();
};
