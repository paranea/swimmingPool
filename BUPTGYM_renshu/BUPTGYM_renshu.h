
// BUPTGYM_renshu.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBUPTGYM_renshuApp:
// �йش����ʵ�֣������ BUPTGYM_renshu.cpp
//

class CBUPTGYM_renshuApp : public CWinApp
{
public:
	CBUPTGYM_renshuApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBUPTGYM_renshuApp theApp;