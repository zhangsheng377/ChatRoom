
// ���������ҷ�������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C���������ҷ�������App: 
// �йش����ʵ�֣������ ���������ҷ�������.cpp
//

class C���������ҷ�������App : public CWinApp
{
public:
	C���������ҷ�������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C���������ҷ�������App theApp;