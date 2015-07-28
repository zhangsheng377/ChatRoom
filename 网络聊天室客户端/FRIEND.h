#include "ChatDlg.h"
#pragma once
class FRIEND
{
public:
	FRIEND();
	~FRIEND();
	
	CString account;
	CString name;
	int isonline;
	BOOL IsChatting;	
	ChatDlg *m_ChatDlg;
};

