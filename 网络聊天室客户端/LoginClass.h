#pragma once


// LoginClass �Ի���

class LoginClass : public CDialogEx
{
	DECLARE_DYNAMIC(LoginClass)

public:
	LoginClass(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LoginClass();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString my_Name;
	CString my_Password;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
};
