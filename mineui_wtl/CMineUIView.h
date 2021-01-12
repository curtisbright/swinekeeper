// file      : CMineUIView.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// MineUI_WTLView.h : interface of the CMineUI_WTLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MINEUI_WTLVIEW_H__D96F56DE_26BE_11D4_BE74_000000000000__INCLUDED_)
#define AFX_MINEUI_WTLVIEW_H__D96F56DE_26BE_11D4_BE74_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <AtlCtrls.h>

#include <vector>
#include <string>
#include <strstream>

#include <gamecontrol/CGameManager.h>
#include <gamecontrol/CGlobalResourceSet.h>
#include <gamecontrol/InputDevices.h>
#include "UIDrawContextWTL.h" 
#include "resource.h" 
#include <mineui_common/CLevelMgr.h>

class CMineUIView : public CWindowImpl<CMineUIView>
{

public:
   DECLARE_WND_CLASS(NULL)

   CMineUIView(); 
   ~CMineUIView(); 

   BOOL PreTranslateMessage(MSG*)
   {
      return FALSE;
   }

   BEGIN_MSG_MAP(CMineUIView)
      MESSAGE_HANDLER(WM_PAINT, OnPaint)
      MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseMessage)
      MESSAGE_HANDLER(WM_LBUTTONDOWN, OnButtonDown)
      MESSAGE_HANDLER(WM_MBUTTONDOWN, OnButtonDown)
      MESSAGE_HANDLER(WM_RBUTTONDOWN, OnButtonDown)
      MESSAGE_HANDLER(WM_LBUTTONUP, OnButtonUp)
      MESSAGE_HANDLER(WM_MBUTTONUP, OnButtonUp)
      MESSAGE_HANDLER(WM_RBUTTONUP, OnButtonUp)
      MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
      MESSAGE_HANDLER(WM_TIMER, OnTimer)
      MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
      // menu commands 
      ALT_MSG_MAP(1) 
      COMMAND_ID_HANDLER(ID_PLAY_NEW, OnPlayNew)
      COMMAND_ID_HANDLER(ID_SOLVE, OnSolve)
      COMMAND_ID_HANDLER(ID_RESET_SOLVE, OnResetSolve)     
      COMMAND_ID_HANDLER(ID_VIEW_PREV, OnHistoryPrev)
      COMMAND_ID_HANDLER(ID_VIEW_NEXT, OnHistoryNext)
   END_MSG_MAP()


   void init(CLevelMgr *pLevelMgr); 

   void resize(const CGameDim &gameDim); 
   CGameDim getGameDim(); 
   CSize getClientSize();
   void enableQMMarkers(bool bActive);
   

private: 
   CGameManager m_gameMgr; 
   CMouseInputDevice m_mouse; 
   CBitmap m_backBuffer; 
   CToolTipCtrl m_tip;
   bool m_bFullUpdate; 

   CLevelMgr *m_pLevelMgr; 

   static CMouseInputDevice::MouseButton convToMouseState(WPARAM wParam);

   void stopTimer();
   void startTimer();

   LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/); 
   void paintDoubleBuff(HDC hdc); 
   void paint(HDC hdc);  
   void selectiveUpdate();

   void releaseMouse(WPARAM wParam, LPARAM lParam);
   void pushMouse(WPARAM wParam, LPARAM lParam);
       
   LRESULT OnButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
   LRESULT OnPlayNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
   LRESULT OnSolve(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);   
   LRESULT OnResetSolve(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);   

   LRESULT OnHistoryPrev(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);   
   LRESULT OnHistoryNext(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);   


   void checkResult(); 

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINEUI_WTLVIEW_H__D96F56DE_26BE_11D4_BE74_000000000000__INCLUDED_)
