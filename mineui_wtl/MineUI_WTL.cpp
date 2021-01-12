// file      : MineUI_WTL.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// MineUI_WTL.cpp : main source file for MineUI_WTL.exe
//

#include "StdAfx.h" 

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>
#include <atlwin.h>

#include "resource.h"

#include "CMineUIView.h"
#include "CMainFrame.h"
#include <gamecontrol/CGlobalResourceSet.h>
#include <mineui_common/CPersistentState.h>
#include "CPersistentDictWin.h" 

// You need WTL and ATL from Microsoft to 
// compile this project
// WTL is available in the most recent Windows SDK, 
// ATL is usually distributed together with Visual C++

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
    CMessageLoop theLoop;
    _Module.AddMessageLoop(&theLoop);

   // initialize the singletons this program needs 
   if (CUISystemWTL::instance() == NULL) 
   {
      CUISystemWTL::setInstance(new CUISystemWTL); 
   }
   
   if (CGlobalResourceSet::instance() == NULL) 
   {
      CGlobalResourceSet *pRes = new CGlobalResourceSet; 
      CUISystemWTL *pWTLSys = CUISystemWTL::instanceWTL(); 
      pRes->m_pSmilies = std::auto_ptr<CIconSetBase>(
         pWTLSys->loadIconSet(IDB_SMILIES, IconType::SMILIE_COUNT, 1)); 
      pRes->m_pDigits = std::auto_ptr<CIconSetBase>(
         pWTLSys->loadIconSet(IDB_DIGITS, IconType::DIGIT_COUNT, 1)); 
      pRes->m_pFieldIcons = std::auto_ptr<CIconSetBase>(
         pWTLSys->loadIconSet(IDB_FIELD_ICONS, IconType::FIELD_COUNT, 1)); 
      pRes->m_pFieldInfoIcons = std::auto_ptr<CIconSetBase>(
         pWTLSys->loadIconSet(IDB_FIELD_INFOS, IconType::FIELDINFO_COUNT, 1)); 
      CGlobalResourceSet::setInstance(pRes); 
   }

    CMainFrame wndMain;

    if(wndMain.CreateEx(NULL, CWindow::rcDefault,  WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX) == NULL)
    {
        ATLTRACE(_T("Main window creation failed!\n"));
        return 0;
    }
   
    wndMain.ShowWindow(nCmdShow);
   
    int nRet = theLoop.Run();

    _Module.RemoveMessageLoop();
    return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
    HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//    HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
    ATLASSERT(SUCCEEDED(hRes));

#if (_WIN32_IE >= 0x0300)
    INITCOMMONCONTROLSEX iccx;
    iccx.dwSize = sizeof(iccx);
    iccx.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES;
    BOOL bRet = ::InitCommonControlsEx(&iccx);
    bRet;
    ATLASSERT(bRet);
#else
    ::InitCommonControls();
#endif

    hRes = _Module.Init(NULL, hInstance);
    ATLASSERT(SUCCEEDED(hRes));


    int nRet = Run(lpstrCmdLine, nCmdShow);

    _Module.Term();
    ::CoUninitialize();

    return nRet;
}
