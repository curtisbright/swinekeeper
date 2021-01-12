// file      : CMainFrame.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__D96F56DB_26BE_11D4_BE74_000000000000__INCLUDED_)
#define AFX_MAINFRM_H__D96F56DB_26BE_11D4_BE74_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>
#include <atlwin.h>
#include "CMineUIView.h" 
#include <mineui_common/gameconstants.h>
#include <mineui_common/GameOptions.h> 

class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
      public CMessageFilter, public CIdleHandler
{
public:
   DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

   CMineUIView m_view;
   CLevelMgr m_levelMgr; 

   CCommandBarCtrl m_CmdBar;


   virtual BOOL PreTranslateMessage(MSG* pMsg);

   virtual BOOL OnIdle();

   bool ResizeView(const CSize &size);

   BEGIN_MSG_MAP(CMainFrame)
      MESSAGE_HANDLER(WM_CREATE, OnCreate)
      COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
      COMMAND_ID_HANDLER(ID_LEVEL_BEGINNER, OnLevelBeginner)
      COMMAND_ID_HANDLER(ID_LEVEL_ADVANCED, OnLevelAdvanced)
      COMMAND_ID_HANDLER(ID_LEVEL_PROFI, OnLevelProfi)
      COMMAND_ID_HANDLER(ID_LEVEL_USER_DEFINED, OnLevelUserDefined)
      COMMAND_ID_HANDLER(ID_MARKERS, OnMarkers)

      COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
      COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
      COMMAND_ID_HANDLER(ID_HALL_OF_FAME, OnHallOfFame)

      CHAIN_MSG_MAP_ALT_MEMBER(m_view, 1) 
      CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
      CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
   END_MSG_MAP()

   BEGIN_UPDATE_UI_MAP(CMainFrame)
      UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)

      UPDATE_ELEMENT(ID_LEVEL_BEGINNER, UPDUI_MENUPOPUP)
      UPDATE_ELEMENT(ID_LEVEL_ADVANCED, UPDUI_MENUPOPUP)
      UPDATE_ELEMENT(ID_LEVEL_PROFI, UPDUI_MENUPOPUP)
      UPDATE_ELEMENT(ID_LEVEL_USER_DEFINED, UPDUI_MENUPOPUP)
      UPDATE_ELEMENT(ID_MARKERS, UPDUI_MENUPOPUP)
   END_UPDATE_UI_MAP()

   LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
   LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
   LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
   LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
   LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

   void updateMenuState();  
   void resetGame(); 
   void setFieldSize(const CGameDim &gameDim);

   LRESULT OnLevelBeginner(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

   LRESULT OnLevelAdvanced(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
   LRESULT OnLevelProfi(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
   LRESULT OnLevelUserDefined(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
   LRESULT OnMarkers(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/); 
   LRESULT OnHallOfFame(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/); 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D96F56DB_26BE_11D4_BE74_000000000000__INCLUDED_)
