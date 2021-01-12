// file      : CKeyboardInputDevice2.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CKeyboardInputDevice2.h"


CKeyboardInputDevice2::CKeyboardInputDevice2() : m_pView(NULL) {}

void CKeyboardInputDevice2::setView(CGameView *pView)
{
   m_pView = pView; 
}

bool CKeyboardInputDevice2::getCurFieldPos(CFieldPos &p) const
{
   p = m_curState.m_fieldPos; 
   return true; 
}



CGameView::MouseButton CKeyboardInputDevice2::getCurMouseButton() const
{
   return m_curState.m_nButton; 
}

void CKeyboardInputDevice2::draw(CUIDrawContextBase *pCtx, bool /*bForceUpdate*/)
{
   if (!m_pView) return; 

   CUIRect r = m_pView->layout().getFieldRect(m_curState.m_fieldPos); 
   pCtx->drawOuterFrame(
      r.deflated(1), 
      CUIDrawContextBase::RED, 
      CUIDrawContextBase::RED, 
      1); 
}

void CKeyboardInputDevice2::getUpdateViewInfo(CGameView::CUpdateViewInfo &viewInfo) const
{
   viewInfo.setFullUpdate(); 
}

void CKeyboardInputDevice2::getViewDeviceStateInfo(CGameView::CDeviceStateInfo &/*state*/) const
{

}

void CKeyboardInputDevice2::onMoveKeyPressed(int nKeyX, int nKeyY)
{
   if (!m_pView) return; 
   assert(nKeyX >=-1 && nKeyX <= 1 && nKeyY >=-1 && nKeyY <= 1); 
   
   CFieldPos shiftedField = m_curState.m_fieldPos.sum(nKeyX, nKeyY); 
   m_curState.m_fieldPos = restrictedToArray(shiftedField); 
   m_curState.m_nButton = CGameView::BUTTON_NONE; 
}

void CKeyboardInputDevice2::onClickKeyPressed(CGameView::MouseButton nButton)
{
   m_curState.m_nButton = nButton; 
   if (m_curState.m_nButton != CGameView::BUTTON_NONE) 
   {
     m_pView->onPushField(m_curState.m_fieldPos, getCurMouseButton()); 
   }
}

void CKeyboardInputDevice2::onClickKeyReleased()
{
   if (!m_pView) return; 

   if (m_curState.m_nButton != CGameView::BUTTON_NONE) 
   {
      m_pView->onReleaseField(m_curState.m_fieldPos, getCurMouseButton()); 
   }

   m_curState.m_nButton = CGameView::BUTTON_NONE;   
}

CFieldPos CKeyboardInputDevice2::restrictedToArray(const CFieldPos &fp_arg) const
{
   CFieldPos fp(fp_arg); 
   int nFX = m_pView->layout().fieldsX(); 
   int nFY = m_pView->layout().fieldsY(); 
   int nX = fp.x(), nY = fp.y(); 
   if (fp.x() <= 0) nX = 0; 
   if (fp.x() > nFX) nX = nFX-1; 
   if (fp.y() <= 0) nY = 0; 
   if (fp.y() > nFY) nY = nFY-1; 
   return CFieldPos(nX, nY); 
}

