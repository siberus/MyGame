
// MyGame.h : main header file for the MyGame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMyGameApp:
// See MyGame.cpp for the implementation of this class
//

class CMyGameApp : public CWinApp
{
public:
	CMyGameApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyGameApp theApp;
