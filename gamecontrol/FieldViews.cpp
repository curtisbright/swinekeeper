// file      : FieldViews.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "FieldViews.h" 

#include "CGlobalResourceSet.h" 
#include <minebase/PlayArray.h> 
#include "CGameDocument.h" 

void CRunningFieldView::drawField( 
   CUIDrawContextBase *pCtx, 
   const CUIRect &scrRect, 
   const CFieldPos &fieldPos)
{
   int nIcon(0);  
   CUIPoint scrPos(scrRect.minV()); 

   const CPlayField &val = m_pDoc->field(fieldPos); 

   if (val.isCovered())
   {
      if (val.isMarkedAsBomb()) 
         nIcon = IconType::FIELD_COVERED_BOMBFLAG; 
      else if (val.isMarkedAsQuestionMark())
         nIcon = IconType::FIELD_COVERED_QUESTIONMARK; 
      else  
         nIcon = IconType::FIELD_COVERED; 
   }
   else 
   {
      if (val.isBomb()) 
         nIcon = IconType::FIELD_UNCOVERED_CLICKED_BOMB; 
      else 
         nIcon = val.getCount(); 
   }

   pCtx->drawIcon(
      CGlobalResourceSet::instance()->m_pFieldIcons.get(),
      nIcon, 0, 
      scrPos); 
} 

bool CRunningFieldView::isRedrawable(const CFieldPos &fieldPos) const
{
   const CPlayField &val = m_pDoc->field(fieldPos); 
   return val.isCovered() && !val.isMarkedAsBomb(); 
}

void CLostFieldView::drawField( 
   CUIDrawContextBase *pCtx, 
   const CUIRect &scrRect, 
   const CFieldPos &fieldPos)
{
   CUIPoint scrPos(scrRect.minV()); 
   int nIcon(0);  
   const CPlayField &val = m_pDoc->field(fieldPos); 
   
   if (val.isCovered())
   {
      if (val.isBomb()) 
      {            
         nIcon = IconType::FIELD_UNCOVERED_BOMB; 
      }
      else 
      {
         if (val.isMarkedAsBomb()) 
            nIcon = IconType::FIELD_UNCOVERED_MARKED_NOBOMB; 
         else 
            nIcon = IconType::FIELD_COVERED; 
      }  
   }
   else 
   {
      if (val.isBomb()) 
         nIcon = IconType::FIELD_UNCOVERED_CLICKED_BOMB; 
      else 
         nIcon = val.getCount(); 
   }
   pCtx->drawIcon(
      CGlobalResourceSet::instance()->m_pFieldIcons.get(),
      nIcon, 0, 
      scrPos); 
} 

