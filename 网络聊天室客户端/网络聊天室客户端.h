
// ���������ҿͻ���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C���������ҿͻ���App: 
// �йش����ʵ�֣������ ���������ҿͻ���.cpp
//

class C���������ҿͻ���App : public CWinApp
{
public:
	C���������ҿͻ���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C���������ҿͻ���App theApp;