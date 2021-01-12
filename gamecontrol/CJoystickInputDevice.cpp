// file      : CJoystickInputDevice.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CJoystickInputDevice.h"


CJoystickInputDevice::CJoystickInputDevice() : m_pView(NULL) {}

void CJoystickInputDevice::setView(CGameView *pView)
{
   m_pView = pView; 
}

bool CJoystickInputDevice::getCurFieldPos(CFieldPos &p) const
{
   p = m_curState.m_selectedField; 
   return true; 
}



CGameView::MouseButton CJoystickInputDevice::getCurMouseButton() const
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

void CJoystickInputDevice::draw(CUIDrawContextBase *pCtx, bool /*bForceUpdate*/)
{
   if (!m_pView) return; 

   CUIRect r1 = m_pView->layout().getFieldRect(m_curState.m_centerField.sum(AreaRadius, AreaRadius)); 
   CUIRect r2 = m_pView->layout().getFieldRect(m_curState.m_centerField.sum(-AreaRadius, -AreaRadius)); 
   CUIRect r = r1.getUnionBBox(r2); 
   pCtx->drawOuterFrame(
      r.deflated(1), 
      CUIDrawContextBase::RED, 
      CUIDrawContextBase::RED, 
      1); 

   CUIRect rsmall = m_pView->layout().getFieldRect(m_curState.m_selectedField); 
   pCtx->drawOuterFrame(
      rsmall.deflated(1), 
      CUIDrawContextBase::RED, 
      CUIDrawContextBase::RED, 
      1); 

}

void CJoystickInputDevice::getUpdateViewInfo(CGameView::CUpdateViewInfo &viewInfo) const
{
   viewInfo.setFullUpdate(); 
}

void CJoystickInputDevice::getViewDeviceStateInfo(CGameView::CDeviceStateInfo &/*state*/) const
{

}

void CJoystickInputDevice::onButtonPressed(bool bLeftButton, bool bRightButton)
{
   m_curState.m_bRightButton = bRightButton; 
   m_curState.m_bLeftButton = bLeftButton; 

   m_pView->onPushField(m_curState.m_selectedField, getCurMouseButton()); 
}

void CJoystickInputDevice::onFireReleased()
{
   m_curState.m_centerField = restrictedToArray(m_curState.m_selectedField); 
}

void CJoystickInputDevice::onMoved(double dX, double dY)
{
   int nFieldSize = 2*AreaRadius+1; 
   int nX = int(nFieldSize*((dX+1)/2)) - AreaRadius;
   int nY = int(nFieldSize*((dY+1)/2)) - AreaRadius;
   if (nX < -AreaRadius) nX = -AreaRadius; 
   if (nY < -AreaRadius) nY = -AreaRadius; 
   if (nX > AreaRadius) nX = AreaRadius; 
   if (nY > AreaRadius) nY = AreaRadius; 
   m_curState.m_selectedField = m_curState.m_centerField.sum(nX, nY); 
}

/** 
 * Called by the client if the user releases a key. 
 */ 
void CJoystickInputDevice::onButtonReleased()
{
   if (!m_pView) return; 

   if (m_curState.m_bRightButton || m_curState.m_bLeftButton) 
   {
      m_pView->onReleaseField(m_curState.m_selectedField, getCurMouseButton()); 
   }

   m_curState.m_bRightButton = false; 
   m_curState.m_bLeftButton = false; 
}

CFieldPos CJoystickInputDevice::restrictedToArray(const CFieldPos &fp_arg) const
{
   CFieldPos fp(fp_arg); 
   int nFX = m_pView->layout().fieldsX(); 
   int nFY = m_pView->layout().fieldsY(); 
   int nX = fp.x(), nY = fp.y(); 
   if (fp.x() <= AreaRadius) nX = AreaRadius; 
   if (fp.x() > nFX-AreaRadius) nX = nFX-AreaRadius-1; 
   if (fp.y() <= AreaRadius) nY = AreaRadius; 
   if (fp.y() > nFY-AreaRadius) nY = nFY-AreaRadius-1; 
   return CFieldPos(nX, nY);  
}

