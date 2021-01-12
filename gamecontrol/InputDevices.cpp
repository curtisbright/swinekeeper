// file      : InputDevices.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 

#include "InputDevices.h" 
#include "CGlobalResourceSet.h" 

#include <cassert>

bool CMouseInputDevice::getCurFieldPos(CFieldPos &p) const
{
   if (m_curState.m_bHasFieldPos) p = m_curState.m_fieldPos; 
   return m_curState.m_bHasFieldPos; 
}

CGameView::MouseButton CMouseInputDevice::getCurMouseButton() const
{
   return toGameView(m_curState.m_nButton); 
}  


bool CMouseInputDevice::isSmiliePushed() const
{
   return m_curState.n_bIsSmiliePushed; 
}

void CMouseInputDevice::draw(CUIDrawContextBase *pCtx, bool /* bForceUpdate */) 
{
   if (!m_pView) return; 

   // redraw always 
   redraw(pCtx); 

   m_lastState = m_curState; 
}

void CMouseInputDevice::redraw(
      CUIDrawContextBase *pCtx)
{
   if (m_curState.m_bHasFieldPos 
       && (m_curState.m_nButton==BUTTON_LEFT || m_curState.m_nButton==BUTTON_MIDDLE))  
   {
      int nSize = 0; 
      if (m_curState.m_nButton==BUTTON_MIDDLE) 
         nSize = 1; 
      for(int nX = -nSize; nX <=nSize; nX++) 
      {
         for(int nY = -nSize; nY <=nSize; nY++) 
         {
            CFieldPos fieldPos(m_curState.m_fieldPos.x() + nX, m_curState.m_fieldPos.y() + nY);
            if (m_pView->isRedrawable(fieldPos)) 
            {
               CUIPoint scrPos = m_pView->getFieldRect(fieldPos).minV(); 
               pCtx->drawIcon(
                  CGlobalResourceSet::instance()->m_pFieldIcons.get(),
                  IconType::FIELD_ON_CLICK, 0, 
                  scrPos); 
            } 
         }
      }
   }
}

bool CMouseInputDevice::hasStateChanged() const
{
   return !(m_curState==m_lastState); 
}

 
void CMouseInputDevice::onPushButton(const CUIPoint &mousePos, MouseButton nButton)
{
   if (!m_pView) return; 

   assert(nButton != BUTTON_NONE); 
   m_curState.n_bIsSmiliePushed = false; 
   m_curState.m_bHasFieldPos = false; 

   CFieldPos fieldPos; 

   if (m_pView->layout().isOverField(mousePos, fieldPos)) 
   {
      m_pView->onPushField(fieldPos, toGameView(nButton)); 
      m_curState.m_bHasFieldPos = true; 
      m_curState.m_fieldPos = fieldPos; 
   } 
   if (m_pView->layout().isOverSmilie(mousePos)) 
   {
      m_curState.n_bIsSmiliePushed = true; 
   }
   m_curState.m_nButton = nButton; 
}

void CMouseInputDevice::onReleaseButton(const CUIPoint &mousePos)
{
   if (!m_pView) return; 

   CFieldPos fieldPos; 
   if (m_pView->layout().isOverField(mousePos, fieldPos)) 
   {
      m_pView->onReleaseField(fieldPos, toGameView(m_curState.m_nButton)); 
   }

   if (m_pView->layout().isOverSmilie(mousePos) && m_curState.n_bIsSmiliePushed) 
   {
      m_pView->pushSmilie(); 
   }
   m_curState.n_bIsSmiliePushed = false; 
   m_curState.m_bHasFieldPos = false; 
   m_curState.m_nButton = BUTTON_NONE; 
}

void CMouseInputDevice::onMoveMouse(const CUIPoint &mousePos)
{
   if (!m_pView) return; 

   m_curState.m_bHasFieldPos = false; 

   CFieldPos fieldPos; 
   if (m_pView->layout().isOverField(mousePos, fieldPos)) 
   {
      m_curState.m_bHasFieldPos = true; 
      m_curState.m_fieldPos = fieldPos; 
   } 

   if (!m_pView->layout().isOverSmilie(mousePos)) 
      m_curState.n_bIsSmiliePushed = false; 
}

CGameView::MouseButton CMouseInputDevice::toGameView(MouseButton nButton)
{
   switch(nButton) {
      case BUTTON_LEFT: return CGameView::BUTTON_LEFT; 
      case BUTTON_MIDDLE: return CGameView::BUTTON_MIDDLE; 
      case BUTTON_RIGHT: return CGameView::BUTTON_RIGHT; 
      default: return CGameView::BUTTON_NONE; 
   }
}

void CMouseInputDevice::getUpdateViewInfo(CGameView::CUpdateViewInfo &viewInfo) const
{
   if (   !m_lastState.m_bHasFieldPos 
       ||  m_lastState == m_curState) 
       return;

   if (m_lastState.m_nButton==BUTTON_LEFT) 
   {
      viewInfo.setUpdateField(m_lastState.m_fieldPos); 
   }
   else if (m_lastState.m_nButton==BUTTON_MIDDLE)
   {
      viewInfo.setUpdateFieldTriple(m_lastState.m_fieldPos); 
   } 
}
 
void CMouseInputDevice::getViewDeviceStateInfo(CGameView::CDeviceStateInfo &state) const
{
   state.m_bIsButtonPushed = (m_curState.m_nButton != BUTTON_NONE); 
   state.m_bIsSmiliePushed = m_curState.n_bIsSmiliePushed; 
}



