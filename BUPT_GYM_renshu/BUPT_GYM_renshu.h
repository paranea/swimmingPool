
// BUPT_GYM_renshu.h : BUPT_GYM_renshu Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CBUPT_GYM_renshuApp:
// �йش����ʵ�֣������ BUPT_GYM_renshu.cpp
//

class CBUPT_GYM_renshuApp : public CWinAppEx
{
public:
	CBUPT_GYM_renshuApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBUPT_GYM_renshuApp theApp;
