
// collector.h: hlavní soubor hlaviček pro aplikaci PROJECT_NAME
//

#ifndef COLECT_H
#define COLECT_H
 // !COLECT_H

#pragma once

#ifndef __AFXWIN_H__
	#error "zahrnout soubor pch.h před zahrnutím tohoto souboru pro soubor PCH"
#endif

#include "resource.h"		// hlavní symboly

// colectApp:
// Implementaci této třídy najdete v collector.cpp.
//

class colectApp : public CWinApp
{
public:
	colectApp();

// Přepsání
public:
	virtual BOOL InitInstance();

// Implementace

	DECLARE_MESSAGE_MAP()
};

extern colectApp theApp;
#endif