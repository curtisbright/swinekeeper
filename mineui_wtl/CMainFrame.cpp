// file      : CMainFrame.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CMainFrame.h" 

#include "CAboutDlg.h"
#include "CArrayDimDlg.h"
#include <mineui_common/GameConstants.h>
#include "CHallOfFameDlg.h" 
#include <mineui_common/CPersistentState.h> 
#include "CPersistentDictWin.h" 

using namespace GameConstant; 

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
    if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
        return TRUE;

    return m_view.PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
    UIUpdateToolBar();
    return FALSE;
}

bool CMainFrame::ResizeView(const CSize &size)
{
   // this code tries to resize the main window so that 
   // the client window has exactly the size given in the parameters 
   ResizeClient(200, 200); 
   CRect clientRect; 
   m_view.GetClientRect(&clientRect); 
   CSize FrameSize = size + CSize(200, 200) - clientRect.Size(); 
   BOOL bSuc = ResizeClient(FrameSize.cx, FrameSize.cy); 
   if (!bSuc) return false; 

   CRect newViewRect; 
   m_view.GetClientRect(&newViewRect); 

   if (newViewRect.Size() != size) 
      return false; 

   return true; 
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    // create command bar window
    HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
    // atach menu
    m_CmdBar.AttachMenu(GetMenu());
    // load command bar images
    m_CmdBar.LoadImages(IDR_MAINFRAME);
    // remove old menu
    SetMenu(NULL);

    CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
    AddSimpleReBarBand(hWndCmdBar);

   CreateSimpleStatusBar();
   ::ShowWindow(m_hWndStatusBar, SW_HIDE);
    UISetCheck(ID_VIEW_STATUS_BAR, 0);

    m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, 
      WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE & 0);

   // do a first initialization 
   m_levelMgr.init(new CPersistentDictWin("SwineKeeper.ini", "game")); 
   m_view.init(&m_levelMgr); 

   updateMenuState(); 
   resetGame(); 

    CMessageLoop* pLoop = _Module.GetMessageLoop();
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);

    return 0;
}

/** 
 * Recomputes the state of the menue so that it is in sync 
 * with the level manager. 
 */ 
void CMainFrame::updateMenuState() 
{
   GameConstant::GameLevel nLevel = m_levelMgr.getLevel(); 
    UISetCheck(ID_LEVEL_BEGINNER, nLevel==LEVEL_BEGINNER);
    UISetCheck(ID_LEVEL_ADVANCED, nLevel==LEVEL_INTERMEDIATE);
    UISetCheck(ID_LEVEL_PROFI, nLevel==LEVEL_EXPERT);
    UISetCheck(ID_LEVEL_USER_DEFINED, nLevel==LEVEL_USER_DEFINED);
    UISetCheck(ID_MARKERS, m_levelMgr.getQMMarkers());
    UpdateLayout();
}

/** 
 * Applies all properties of the level manager to the 
 * the view and resets the game. 
 */ 
void CMainFrame::resetGame() 
{
    setFieldSize(m_levelMgr.getGameDim());   
   m_view.enableQMMarkers(m_levelMgr.getQMMarkers()); 
}


LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    PostMessage(WM_CLOSE);
    return 0;
}

LRESULT CMainFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    BOOL bNew = !::IsWindowVisible(m_hWndStatusBar);
    ::ShowWindow(m_hWndStatusBar, bNew ? SW_SHOWNOACTIVATE : SW_HIDE);
    UISetCheck(ID_VIEW_STATUS_BAR, bNew);
    UpdateLayout();
    return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    CAboutDlg dlg;
    dlg.DoModal();
    return 0;
}


LRESULT CMainFrame::OnLevelBeginner(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
   m_levelMgr.setLevel(LEVEL_BEGINNER); 
   updateMenuState(); 
   resetGame(); 
    return 0;
}

LRESULT CMainFrame::OnLevelAdvanced(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
   m_levelMgr.setLevel(LEVEL_INTERMEDIATE); 
   updateMenuState(); 
   resetGame(); 
    return 0;
}
LRESULT CMainFrame::OnLevelProfi(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
   m_levelMgr.setLevel(LEVEL_EXPERT); 
   updateMenuState(); 
   resetGame(); 
    return 0;
}
LRESULT CMainFrame::OnLevelUserDefined(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    CArrayDimDlg dlg;
   dlg.m_gameDim = m_levelMgr.getGameDim(); 
   if (dlg.DoModal() == IDOK) 
   {
      if (dlg.areValuesValid()) 
      {
         m_levelMgr.setUserDefinedLevel(dlg.m_gameDim); 
      }
      else 
      {
         CString msgText; 
         BOOL bSuc = msgText.LoadString(IDS_ERR_ARRAY_DIM_INVALID); 
         ATLASSERT(bSuc); 
         bSuc; 
         MessageBox(msgText, "", MB_ICONERROR); 
      }
   }
   updateMenuState(); 
   resetGame(); 

    return 0;
}

LRESULT CMainFrame::OnMarkers(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
   m_levelMgr.setQMMarkers(!m_levelMgr.getQMMarkers()); 
   updateMenuState(); 
   m_view.enableQMMarkers(m_levelMgr.getQMMarkers()); 
   return 0; 
}

LRESULT CMainFrame::OnHallOfFame(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
   CScoreTable scoreTable; 
   m_levelMgr.getScoreTable(scoreTable); 
   CHallOfFameDlg hallOfFameDlg(scoreTable); 
   hallOfFameDlg.DoModal(); 
   return 0; 
}

// only call from resetGame
void CMainFrame::setFieldSize(const CGameDim &newGameDim)
{
   CGameDim oldGameDim = m_view.getGameDim();       

   m_view.resize(newGameDim); 
   bool bSuc = ResizeView(m_view.getClientSize()); 
   
   if (!bSuc) {
      m_view.resize(oldGameDim); 
      ResizeView(m_view.getClientSize());

      CString msgText; 
      BOOL bSuc2 = msgText.LoadString(IDS_ERR_ARRAY_DIM_INVALID); 
      ATLASSERT(bSuc2); 
      bSuc2;
      MessageBox(msgText, "", MB_ICONERROR); 
   }
}
