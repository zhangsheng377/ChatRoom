
// ���������ҿͻ���Dlg.h : ͷ�ļ�
//

#include "ShowWaitDlg.h"
#include "NewSocket.h"
#include "FRIEND.h"
#include <vector>
#include "afxcmn.h"
#include "LoginClass.h"
#include "ChatDlg.h"

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
	
	CNewSocket m_Socket;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnNcPaint();
	ShowWaitDlg *m_ShowWaitDlg;
	/*
	typedef struct ThreadInfo{
		CNewSocket *m_Socket;
		ShowWaitDlg *m_ShowWaitDlg;
		C���������ҿͻ���Dlg *m_Wind;
	}thread,*lpthread;
	*/
	_ConnectionPtr m_pClientDB;				//����ADO���ݿ�,�����ɵ�.tlh���Ƶ���Ŀ�ļ�����
	_RecordsetPtr m_pRecordSet;
	void FreshFriendList();
	

	
	std::vector<FRIEND> friends;
	CListCtrl m_FriendList;
	CImageList *m_pImageList;

	// ��Ҫ������ŵ�my_SendData��
	CString SendReceiveCommand();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnCancel();

	CListBox m_CommandListBox;
};
