
// ���������ҷ�������Dlg.h : ͷ�ļ�
//
#include "ListenSocket.h"

#pragma once


// C���������ҷ�������Dlg �Ի���
class C���������ҷ�������Dlg : public CDialogEx
{
// ����
public:
	C���������ҷ�������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

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
	_ConnectionPtr m_pServerDB;				//����ADO���ݿ�,�����ɵ�.tlh���Ƶ���Ŀ�ļ�����
	_RecordsetPtr m_pRecordSet;

	ListenSocket m_ListenSocket;
};
