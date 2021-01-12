// file      : stdafx.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__D96F56D7_26BE_11D4_BE74_000000000000__INCLUDED_)
#define AFX_STDAFX_H__D96F56D7_26BE_11D4_BE74_000000000000__INCLUDED_

// Change these values to use different versions
#define WINVER      0x0400
#define _WIN32_IE   0x0400
#define _RICHEDIT_VER   0x0100

// #define NOMINMAX

#include <minebase/ConfigAll.h>

#include <atlbase.h>
// if the preprocessor does not find the header below, you have to add the 
// path to the WTL library to the project settings
// see doc/SourceDoc.txt 
#include <atlapp.h>

extern CAppModule _Module;

#include <atlwin.h>
#include <atlmisc.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D96F56D7_26BE_11D4_BE74_000000000000__INCLUDED_)
