#pragma once


// ShowWaitDlg �Ի���

class ShowWaitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShowWaitDlg)

public:
	ShowWaitDlg(CWnd* pParent = NULL);   // ��׼���캯��
	
	virtual ~ShowWaitDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
