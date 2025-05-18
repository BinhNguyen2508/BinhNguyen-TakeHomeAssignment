
// Task_2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTask2App:
// See Task_2.cpp for the implementation of this class
//

class CTask2App : public CWinApp
{
public:
	CTask2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTask2App theApp;
