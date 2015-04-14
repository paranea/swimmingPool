
// BUPT_GYM_renshu.h : BUPT_GYM_renshu 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CBUPT_GYM_renshuApp:
// 有关此类的实现，请参阅 BUPT_GYM_renshu.cpp
//

class CBUPT_GYM_renshuApp : public CWinAppEx
{
public:
	CBUPT_GYM_renshuApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBUPT_GYM_renshuApp theApp;
