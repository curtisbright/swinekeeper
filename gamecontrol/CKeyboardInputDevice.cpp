// file      : CKeyboardInputDevice.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CKeyboardInputDevice.h"


CKeyboardInputDevice::CKeyboardInputDevice() : m_pView(NULL) {}

void CKeyboardInputDevice::setView(CGameView *pView)
{
   m_pView = pView; 
}

bool CKeyboardInputDevice::getCurFieldPos(CFieldPos &p) const
{
   p = m_curState.m_fieldPos; 
   return true; 
}



CGameView::MouseButton CKeyboardInputDevice::getCurMouseButton() const
{
   bool bRightButton = m_curState.m_bRightButton; 
   bool bLeftButton = m_curState.m_bLeftButton; 

   if (!bRightButton && !bLeftButton) 
      return CGameView::BUTTON_NONE; 
   else if (bRightButton && !bLeftButton)       
      return CGameView::BUTTON_RIGHT; 
   else if (!bRightButton && bLeftButton)       
      return CGameView::BUTTON_LEFT; 
   else if (bRightButton && bLeftButton)       
      return CGameView::BUTTON_MIDDLE; 
   else 
      return CGameView::BUTTON_NONE; 
}

void CKeyboardInputDevice::draw(CUIDrawContextBase *pCtx, bool /*bForceUpdate*/)
{
   if (!m_pView) return; 

   CUIRect r1 = m_pView->layout().getFieldRect(m_curState.m_fieldPos.sum(1,1)); 
   CUIRect r2 = m_pView->layout().getFieldRect(m_curState.m_fieldPos.sum(-1,-1)); 
   CUIRect r = r1.getUnionBBox(r2); 
   pCtx->drawOuterFrame(
      r.deflated(1), 
      CUIDrawContextBase::RED, 
      CUIDrawContextBase::RED, 
      1); 
}

void CKeyboardInputDevice::getUpdateViewInfo(CGameView::CUpdateViewInfo &viewInfo) const
{
   viewInfo.setFullUpdate(); 
}

void CKeyboardInputDevice::getViewDeviceStateInfo(CGameView::CDeviceStateInfo &/*state*/) const
{

}

/** 
 * Called by the client when the user pushes a key of the numeric keypad. 
 * 
 * @param nKeyX x-coordinate of a button on the numeric keypad (-1, 0, 1) 
 * @param nKeyY x-coordinate of a button on the numeric keypad (-1, 0, 1) (e.g. numpad 6 == (1,0) 
 * @param bLeftButton true, iff a key is pressed that is used to emulate the left mouse button 
 * @param bRightButton The same for the right mouse button 
 */ 
void CKeyboardInputDevice::onKeyPressed(int nKeyX, int nKeyY, bool bLeftButton, bool bRightButton)
{
   if (!m_pView) return; 

   assert(nKeyX >=-1 && nKeyX <= 1 && nKeyY >=-1 && nKeyY <= 1); 
   
   m_curState.m_bRightButton = bRightButton; 
   m_curState.m_bLeftButton = bLeftButton; 


   if (!bRightButton && !bLeftButton) 
   {
      CFieldPos shiftedField = m_curState.m_fieldPos.sum(nKeyX*3, nKeyY*3); 
      m_curState.m_fieldPos = shiftedField; 
      m_curState.m_fieldPos = restrictedToArray(m_curState.m_fieldPos); 
   }

   if (bRightButton || bLeftButton) 
   {
      CFieldPos shiftedField = m_curState.m_fieldPos.sum(nKeyX, nKeyY); 
      m_pView->onPushField(shiftedField, getCurMouseButton()); 
      m_curState.m_pushedField = shiftedField; 
   }
}

/** 
 * Called by the client if the user releases a key. 
 */ 
void CKeyboardInputDevice::onKeyReleased()
{
   if (!m_pView) return; 

   if (m_curState.m_bRightButton || m_curState.m_bLeftButton) 
   {
      m_pView->onReleaseField(m_curState.m_pushedField, getCurMouseButton()); 
   }

   m_curState.m_bRightButton = false; 
   m_curState.m_bLeftButton = false; 
}

CFieldPos CKeyboardInputDevice::restrictedToArray(const CFieldPos &fp_arg) const
{
   CFieldPos fp(fp_arg); 
   int nFX = m_pView->layout().fieldsX(); 
   int nFY = m_pView->layout().fieldsY(); 
   int nX = fp.x(), nY = fp.y(); 
   if (fp.x() <= 1) nX = 1; 
   if (fp.x() > nFX-1) nX = nFX-2; 
   if (fp.y() <= 1) nY = 1; 
   if (fp.y() > nFY-1) nY = nFY-2; 
   return CFieldPos(nX, nY);  
}

