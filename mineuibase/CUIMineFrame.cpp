// file      : CUIMineFrame.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 

#include "CUIMineFrame.h" 
#include "UIDrawContext.h"
#include <cassert>


void CUIMineFrame::attachBelow(const CUIMineFrame &f) {
   assert(f.m_nDepth == m_nDepth); 
   CUIPoint b = f.getBase(); 
   CUIPoint newUpperLeft = b + CUISize(0, f.getSize().y() - m_nDepth); 
   moveTo(newUpperLeft);
}

CUISize CUIMineFrame::getAttachDiffBelow(const CUIMineFrame &f) const {
   assert(f.m_nDepth == m_nDepth); 
   CUIPoint targetPos = f.getBase() + CUISize(0, f.getSize().y() - m_nDepth); 
   return targetPos - getBase(); 
}



bool CUIMineFrame::drawFrame(CUIDrawContextBase *pCtx) const
{
   CUIDrawContextBase::Color upperLeftCol = CUIDrawContextBase::LIGHT; 
   CUIDrawContextBase::Color lowerRightCol = CUIDrawContextBase::LIGHT; 

   switch (m_nFrameType) {
      case RAISED: 
         upperLeftCol = CUIDrawContextBase::LIGHT; 
         lowerRightCol = CUIDrawContextBase::DARK; 
         break; 
      case SUNKEN: 
         upperLeftCol = CUIDrawContextBase::DARK; 
         lowerRightCol = CUIDrawContextBase::LIGHT; 
         break; 
      default: 
         upperLeftCol = CUIDrawContextBase::MEDIUM; 
         lowerRightCol = CUIDrawContextBase::MEDIUM; 
         break; 
   }      

   pCtx->drawOuterFrame(getInteriorRect(), upperLeftCol, lowerRightCol, m_nDepth); 
   return true; 
}

bool CUIMineFrame::drawInterior(CUIDrawContextBase *pCtx) const
{
   pCtx->fillRect(getInteriorRect(), CUIDrawContextBase::MEDIUM);    
   return true; 
}
