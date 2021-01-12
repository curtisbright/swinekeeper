// file      : CMineUIView.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CMineUIView.h"
#include <mineui_common/CPersistentState.h>
#include "CScoreNameDlg.h"
#include "CHallOfFameDlg.h" 

using namespace std; 

CMineUIView::CMineUIView()
{
}

CMineUIView::~CMineUIView()
{
}

void CMineUIView::init(CLevelMgr *pLevelMgr) 
{

   m_bFullUpdate = true; 
   m_pLevelMgr = pLevelMgr;  

   m_gameMgr.init(&m_mouse); 

    // create a tool tip
    m_tip.Create(m_hWnd);
    ATLASSERT(m_tip.IsWindow());
    m_tip.Activate(FALSE);
    m_tip.AddTool(m_hWnd, "");
}

void CMineUIView::resize(const CGameDim &gameDim) {
   m_gameMgr.resize(gameDim); 
}

CGameDim CMineUIView::getGameDim()
{
   return m_gameMgr.getGameDim(); 
}


CSize CMineUIView::getClientSize() {
   return toWTL(m_gameMgr.getClientWindowSize()); 
}

void CMineUIView::enableQMMarkers(bool bActive) 
{
   m_gameMgr.enableQMMarkers(bActive); 
}


LRESULT CMineUIView::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{      
    CPaintDC dc(m_hWnd);
   // paintDoubleBuff(dc); 
   paint(dc); 

    return 0;
}

void CMineUIView::paintDoubleBuff(HDC hdc) 
{
    CDC dc(hdc);
   CSize size, bbSize; 
   size = getClientSize(); 
   if (m_backBuffer!=NULL && m_backBuffer.GetSize(bbSize) && size != bbSize) 
   {
      m_backBuffer.DeleteObject(); 
   }
   if (!m_backBuffer) 
   {
      m_backBuffer.CreateCompatibleBitmap(dc, size.cx, size.cy); 
   }
      
   CDC backDC; 
   backDC.CreateCompatibleDC(dc); 
   HBITMAP hOld = backDC.SelectBitmap(m_backBuffer);
   
   paint(backDC); 

   dc.BitBlt(
      0, 0, 
      size.cx, size.cy, 
      backDC, 
      0, 0, 
      SRCCOPY); 

   backDC.SelectBitmap(hOld); 
}

void CMineUIView::paint(HDC hdc) 
{
   // dbgoutDPrintf("FullUpdate : %s\n", m_bFullUpdate ? "TRUE" : "FALSE"); 

   CIUDrawContextWTL wtlCtx(hdc); 
   m_gameMgr.draw(&wtlCtx, m_bFullUpdate); 
   m_bFullUpdate = true; 
}

void CMineUIView::selectiveUpdate() 
{
   m_bFullUpdate = false; 
   Invalidate(FALSE); 
}

CMouseInputDevice::MouseButton CMineUIView::convToMouseState(WPARAM wParam) 
{
   bool bLeft = (wParam & MK_LBUTTON)!=0; 
   bool bMiddle = (wParam & MK_MBUTTON)!=0; 
   bool bRight = (wParam & MK_RBUTTON)!=0; 
   
   CMouseInputDevice::MouseButton nActiveMouseButton = CMouseInputDevice::BUTTON_NONE;
   if (bLeft && bRight) 
      nActiveMouseButton = CMouseInputDevice::BUTTON_MIDDLE; 
   else if (bLeft) 
      nActiveMouseButton = CMouseInputDevice::BUTTON_LEFT; 
   else if (bMiddle) 
      nActiveMouseButton = CMouseInputDevice::BUTTON_MIDDLE; 
   else if (bRight) 
      nActiveMouseButton = CMouseInputDevice::BUTTON_RIGHT;  

   return nActiveMouseButton; 
} 

void CMineUIView::stopTimer() 
{     
   KillTimer(1); 
}
void CMineUIView::startTimer()
{
   KillTimer(1); 
   UINT nSuc = SetTimer(1, 250); 
   nSuc; 
   ATLASSERT(nSuc); 
}

void CMineUIView::releaseMouse(WPARAM wParam, LPARAM lParam)
{
   bool bIsRunningOld = m_gameMgr.isGameRunning(); 
   m_mouse.onReleaseButton(toUI(CPoint(lParam))); 
   
   if (!bIsRunningOld && m_gameMgr.isGameRunning()) 
      startTimer(); 

   if (bIsRunningOld && m_gameMgr.isGameFinished()) 
   {
      stopTimer(); 

      m_gameMgr.activateRewind(); 
   
      if (m_gameMgr.isGameWon()) 
      {
         checkResult(); 
      } 
   }

   selectiveUpdate(); 
}   

void CMineUIView::pushMouse(WPARAM wParam, LPARAM lParam)
{
   bool bIsRunningOld = m_gameMgr.isGameRunning(); 
   m_mouse.onPushButton(toUI(CPoint(lParam)), convToMouseState(wParam));
   
   if (!bIsRunningOld && m_gameMgr.isGameRunning()) 
      startTimer(); 

   if (bIsRunningOld && !m_gameMgr.isGameRunning()) 
      stopTimer(); 

   selectiveUpdate(); 
}   
    
LRESULT CMineUIView::OnButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   pushMouse(wParam, lParam); 
    return 0;
}
LRESULT CMineUIView::OnButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   releaseMouse(wParam, lParam); 
    return 0;
}

LRESULT CMineUIView::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   m_mouse.onMoveMouse(toUI(CPoint(lParam))); 

   std::string str; 
   if (m_gameMgr.getToolTipMsg(str))
   {
        if(m_tip.IsWindow())
         m_tip.UpdateTipText(str.c_str(), m_hWnd); 
        m_tip.Activate(TRUE);
   }
   else 
   {  
        m_tip.Activate(FALSE);
   }
   selectiveUpdate(); 

   return 0;
}
LRESULT CMineUIView::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   UINT nSuc = SetTimer(1, 250); 
   ATLASSERT(nSuc); nSuc; 
    selectiveUpdate(); 

   return 0;
}

LRESULT CMineUIView::OnMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    MSG msg = { m_hWnd, uMsg, wParam, lParam };
    if(m_tip.IsWindow())
        m_tip.RelayEvent(&msg);

    bHandled = FALSE;
    return 1;
}

LRESULT CMineUIView::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
   m_bFullUpdate = true;     
   bHandled = TRUE;     
   return 1;
}

LRESULT CMineUIView::OnPlayNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    m_gameMgr.resetGame(); 
   Invalidate(FALSE); 

    return 0;
}

LRESULT CMineUIView::OnSolve(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

   CIUDrawContextWTL wtlCtx(GetDC( )); 
   m_gameMgr.draw(&wtlCtx, m_bFullUpdate, true); 

    m_gameMgr.showSolution(); 
   Invalidate(FALSE); 

    return 0;
}

LRESULT CMineUIView::OnResetSolve(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
   m_gameMgr.hideSolution(); 
   Invalidate(FALSE); 
    return 0;
}


LRESULT CMineUIView::OnHistoryPrev(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
   m_gameMgr.historyPrev();
   Invalidate(FALSE); 
   return 0; 
}

LRESULT CMineUIView::OnHistoryNext(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
   m_gameMgr.historyNext();
   Invalidate(FALSE); 
   return 0; 
}


/** 
 * Checks if the user has reached a new high score. 
 * If yes, it asks for the users name and puts it into the hall of fame. 
 * 
 * XXX Only because of this method I need a reference to CLevelMgr from 
 * this class. It would probably be better to move it to CMainFrame. XXX 
 * 
 */ 
void CMineUIView::checkResult()
{
   int nTime = m_gameMgr.getTime(); 

   if (m_pLevelMgr->hasReachedNewHighScore(nTime) && m_gameMgr.userMayEnterHallOfFame()) 
   {
      CScoreNameDlg nameDlg;
      if (nameDlg.DoModal() == IDOK) 
      {
         m_pLevelMgr->enterHallOfFame(nameDlg.m_userName, nTime); 

         CScoreTable scoreTable; 
         m_pLevelMgr->getScoreTable(scoreTable); 
         CHallOfFameDlg hallOfFameDlg(scoreTable); 
         hallOfFameDlg.DoModal(); 
      }

   }
}


