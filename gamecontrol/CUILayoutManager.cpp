// file      : CUILayoutManager.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 

#include "CUILayoutManager.h"

#include <algorithm>
#include <minebase/MineStd.h>

CUILayoutManager::CUILayoutManager() : 
   m_clientFrame(CUIMineFrame::RAISED, 3), 
   m_arrayFrameI(CUIMineFrame::SUNKEN, 2), 
   m_arrayFrameO(CUIMineFrame::PLANAR, 6), 
   m_ToolbarFrameI(CUIMineFrame::PLANAR, 6), 
   m_ToolbarFrameO(CUIMineFrame::SUNKEN, 2), 
   m_ToolbarFrameO2(CUIMineFrame::PLANAR, 6), 
   m_MineCounterFrame(CUIMineFrame::SUNKEN, 1), 
   m_TimeFrame(CUIMineFrame::SUNKEN, 1), 
   m_SmilieFrame(CUIMineFrame::PLANAR,0) 
{

}

bool CUILayoutManager::isOverField(
   const CUIPoint &p, 
   CFieldPos &fieldPos,  
   double *pdRelX, double *pdRelY) const
{
   if (!m_arrayFrameI.isInInterior(p)) 
      return false; 

   CUISize relP(p - m_arrayFrameI.getInteriorBase()); 
   int nFieldX = relP.x()/m_FieldSize.x(); 
   double dRelX = double(relP.x() - nFieldX*m_FieldSize.x())/m_FieldSize.x(); 
   int nFieldY = relP.y()/m_FieldSize.y(); 
   double dRelY = double(relP.y() - nFieldY*m_FieldSize.y())/m_FieldSize.y(); 

   assert(nFieldX >= 0 && nFieldX < m_nFieldCountX); 
   assert(nFieldY >= 0 && nFieldY < m_nFieldCountY); 

   fieldPos = CFieldPos(nFieldX, nFieldY); 
   if (pdRelX != NULL) *pdRelX = dRelX; 
   if (pdRelY != NULL) *pdRelY = dRelY;
   return true;  
}

bool CUILayoutManager::isOverSmilie(const CUIPoint &p) const
{
   return m_SmilieFrame.isInInterior(p); 
}

bool CUILayoutManager::isOverClientArea(const CUIPoint &p) const
{
   return m_clientFrame.isInInterior(p); 
}


void CUILayoutManager::init(const CUISize &smilieSize, const CUISize &digitSize, const CUISize &fieldSize)
{
   m_SmilieSize = smilieSize; 
   m_DigitSize = digitSize; 
   m_FieldSize = fieldSize; 
}

void CUILayoutManager::resize(int nX, int nY)
{
   m_nFieldCountX = nX; m_nFieldCountY = nY; 

   CUISize arraySize(m_nFieldCountX * m_FieldSize.x(), m_nFieldCountY * m_FieldSize.y()); 
   int nToolbarHeight = MineStd::auxMax(m_SmilieSize.y(), m_DigitSize.y() + m_TimeFrame.getDepth()); 

   m_arrayFrameI.setInteriorSize(arraySize);      
   m_arrayFrameO.setInteriorRect(m_arrayFrameI.getRect()); 

   m_ToolbarFrameO.setSize(CUISize(m_arrayFrameI.getSize().x(), 20)); 
   m_ToolbarFrameI.setSize(m_ToolbarFrameO.getInteriorSize()); 
   m_ToolbarFrameI.setInteriorSize(CUISize(
      m_ToolbarFrameI.getInteriorSize().x(), 
      nToolbarHeight
   )); 
   m_ToolbarFrameO.setInteriorRect(m_ToolbarFrameI.getRect()); 
   m_ToolbarFrameO2.setInteriorRect(m_ToolbarFrameO.getRect()); 

   CUISize arrayDiff = m_arrayFrameO.getAttachDiffBelow(m_ToolbarFrameO2); 
   m_arrayFrameO.moveRel(arrayDiff); 
   m_arrayFrameI.moveRel(arrayDiff); 

   m_clientFrame.setInteriorRect(CUIRect(m_ToolbarFrameO2.getTopLeft(), m_arrayFrameO.getBottomRight())); 

   CUISize baseDiff = CUIPoint(0,0)-m_clientFrame.getBase(); 
   
   m_arrayFrameI.moveRel(baseDiff); 
   m_arrayFrameO.moveRel(baseDiff); 
   m_ToolbarFrameO.moveRel(baseDiff); 
   m_ToolbarFrameO2.moveRel(baseDiff); 
   m_ToolbarFrameI.moveRel(baseDiff); 
   m_clientFrame.moveRel(baseDiff); 

   m_MineCounterFrame.setInteriorSize(CUISize(m_DigitSize.x()*3, m_DigitSize.y())); 
   m_MineCounterFrame.moveTo(m_ToolbarFrameI.getInteriorTopLeft()); 
   m_TimeFrame.setInteriorSize(CUISize(m_DigitSize.x()*3, m_DigitSize.y())); 
   m_TimeFrame.moveTopRightTo(m_ToolbarFrameI.getInteriorTopRight()); 
   m_SmilieFrame.setInteriorSize(m_SmilieSize); 
   m_SmilieFrame.moveMiddleTo(m_ToolbarFrameI.getMiddle()); 

}

void CUILayoutManager::draw(CUIDrawContextBase *pCtx)
{
   m_arrayFrameI.drawFrame(pCtx); 
   m_arrayFrameO.drawFrame(pCtx); 
   m_ToolbarFrameO.drawFrame(pCtx); 
   m_ToolbarFrameO2.drawFrame(pCtx); 
   m_ToolbarFrameI.drawFrame(pCtx); 
   m_clientFrame.drawFrame(pCtx); 

   m_ToolbarFrameI.drawInterior(pCtx);
   m_MineCounterFrame.drawFrame(pCtx); 
   m_TimeFrame.drawFrame(pCtx); 
}

CUIRect CUILayoutManager::getFieldsRect(
   const CFieldPos &fieldBegin, 
   const CFieldPos &fieldEnd) const
{
   return getFieldRect(fieldBegin).getUnionBBox(
      getFieldRect(CFieldPos(fieldEnd.x()-1, fieldEnd.y()-1))
   ); 
} 

bool CUILayoutManager::doesTouchFrames(const CUIRect &r) const
{
   return m_clientFrame.getRect().touches(r) 
          && !m_arrayFrameI.getInteriorRect().contains(r); 
}

