// file      : CSolutionFieldView.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CSolutionFieldView.h"

#include "CGlobalResourceSet.h" 
#include <minebase/PlayArray.h> 
#include "CGameDocument.h" 
#include <mineuibase/UIAux.h>
#include <cassert>
#include <cstdio>
#include <minesolver/SolutionEnumerator.h>
#include <minesolver/SolutionUtil.h>
#include "CTerminatorEsc.h"

//#include <iostream>

// #include <minetest/MinePropRegTest.h>
#include <storage/Document.h>
#include <minebase/MineBaseSerialize.h>
#include <cassert>

bool CSolutionFieldView::computeSolution()
{
   CMineArrayBase<CInputField> solverInputArray; 
   convertArray<CInputField, CPlayField>(
      solverInputArray, 
      m_pDoc->playArray(), 
      CInputField(), 
      SolUtil::cnvToInputField); 
   
   // createTest("array.xml", solverInputArray, m_pDoc->getTotalBombCount());
   
   /* 
   Storage::CDocument doc("test"); 
   Storage::CSection inputSection(doc.rootSection(true));
   int bombCount(m_pDoc->getGameDim().bombCount()); 
   inputSection.transferItem("bomb-count").transferInt(bombCount); 
   Storage::CSection arraySection; 
   inputSection.transferSection("array", arraySection); 
   transferDataCompact<CInputField>(arraySection, solverInputArray); 
   doc.saveDoc("test2.xml"); 
   */ 
   
   CTerminatorEsc terminator; 

   bool bSuc = compProbabilities(
   // compWinProp(
   // compGoodness(
   // compSolutionSets( 
   // compSolutionEnum(
      m_propArray, 
      solverInputArray,
      m_pDoc->getGameDim().bombCount(),
      &terminator);
      
   if (terminator.doTerminate()) 
   {
      m_bHasValidSolution = false;
      return false;    
   }
        
   assert(bSuc); 
   m_bHasValidSolution = bSuc;   
   return bSuc; 
}


void CSolutionFieldView::drawField( 
   CUIDrawContextBase *pCtx, 
   const CUIRect &scrRect, 
   const CFieldPos &fieldPos)
{
   CUIPoint scrPos(scrRect.minV()); 

   if (!m_bHasValidSolution) 
   {
      assert(0); 
      return;
   }

   CPlayField val = m_pDoc->field(fieldPos); 
   CResultField resVal;
   resVal = m_propArray[fieldPos]; 

   if ((val.isCovered() || val.isBomb()) && resVal.hasProp()) 
   {
      IconType::FieldInfo nInfoIcon(IconType::FIELDINFO_UNDECIDEABLE);
      if (resVal.isKnownBomb()) 
      {
         if (val.isMarkedAsBomb()) 
            nInfoIcon = IconType::FIELDINFO_KNOWN_FLAGBOMB; 
         else 
            nInfoIcon = IconType::FIELDINFO_KNOWN_BOMB;        
      }
      else if (resVal.isKnownNoBomb()) 
      {
         if (val.isMarkedAsBomb()) 
            nInfoIcon = IconType::FIELDINFO_KNOWN_FLAGNOBOMB; 
         else 
            nInfoIcon = IconType::FIELDINFO_KNOWN_NOBOMB;        
      } 
      else {
         nInfoIcon = IconType::FIELDINFO_UNDECIDEABLE; 
      }
      pCtx->drawIcon(
         CGlobalResourceSet::instance()->m_pFieldInfoIcons.get(),
         nInfoIcon, 0, 
         scrPos);

      if (resVal.hasVal()) {
         UIAux::drawRatioIcon(
            pCtx, 
            scrRect,
            CUIDrawContextBase::DARK_RED, 
            CUIDrawContextBase::RED, 
            resVal.getVal()
         ); 
      }

   }
   else 
   {
      m_runningFieldView.drawField(pCtx, scrRect, fieldPos); 
   }
} 

bool CSolutionFieldView::getFieldMessage(const CFieldPos &fieldPos, std::string &str) const
{
   if (!m_bHasValidSolution) 
   {
      return false;
   }

   CPlayField val = m_pDoc->field(fieldPos); 
   CResultField resVal = m_propArray[fieldPos]; 

   if (   val.isCovered() 
       && resVal.hasProp() 
       && resVal.isUndecideable())
   {
      str = resVal.desc(); 
      return true;  
   }
   else 
   {
      return false; 
   }
}

// solution enum field

void CSolutionEnumFieldView::computeSolution()
{
   CMineArrayBase<CInputField> solverInputArray; 
   convertArray<CInputField, CPlayField>(
      solverInputArray, 
      m_pDoc->playArray(), 
      CInputField(), 
      SolUtil::cnvToInputField); 
   compSolutionEnum(
      m_propArray, 
      solverInputArray,
      m_pDoc->getGameDim().bombCount(),
      &m_enumArray);  
   m_bHasValidSolution = true;   
}


void CSolutionEnumFieldView::drawField( 
   CUIDrawContextBase *pCtx, 
   const CUIRect &scrRect, 
   const CFieldPos &fieldPos)
{
   CUIPoint scrPos(scrRect.minV()); 

   if (!m_bHasValidSolution) 
   {
      assert(0); 
      return;
   }

   CPlayField val = m_pDoc->field(fieldPos); 
   CSolEnumField resVal = m_enumArray[fieldPos]; 

   if (val.isCovered() && resVal.isResolved() || resVal.hasSolutionSet()) 
   {
      IconType::FieldInfo nInfoIcon(IconType::FIELDINFO_UNDECIDEABLE);
      if (resVal.isBomb()) {
         if (val.isMarkedAsBomb()) 
            nInfoIcon = IconType::FIELDINFO_KNOWN_FLAGBOMB; 
         else 
            nInfoIcon = IconType::FIELDINFO_KNOWN_BOMB;        
      }
      else {
         if (val.isMarkedAsBomb()) 
            nInfoIcon = IconType::FIELDINFO_KNOWN_FLAGNOBOMB; 
         else 
            nInfoIcon = IconType::FIELDINFO_KNOWN_NOBOMB;        
      } 
      pCtx->drawIcon(
         CGlobalResourceSet::instance()->m_pFieldInfoIcons.get(),
         nInfoIcon, 0, 
         scrPos);
   }
   else 
   {
      m_runningFieldView.drawField(pCtx, scrRect, fieldPos); 
   }
} 

bool CSolutionEnumFieldView::getFieldMessage(const CFieldPos &fieldPos, std::string &str) const
{
   int nSet = m_enumArray[fieldPos].setIndex(); 
   if (nSet >= 0) 
   {
      int nCount = m_enumArray.getSolutionCount(nSet); 
      char szTmp[1000]; 
      sprintf(szTmp, "%d: #%d (P=%5.3f)", nSet, nCount, m_propArray[fieldPos].getVal()); 
      str = std::string(szTmp); 
      return true; 
   }
   else if (m_enumArray[fieldPos].isResolved()) 
   {
      str = std::string("resolved"); 
      return true; 
   }
   return false; 
}

bool CSolutionEnumFieldView::onPushField(const CFieldPos &fieldPos, int nMouseButton)
{
   if (nMouseButton==0) 
   {
      int nSet = m_enumArray[fieldPos].setIndex(); 
      if (nSet >= 0) 
      {
         m_enumArray.nextSolution(nSet); 
      }
      return true; 
   }
   else 
   {
      return false; 
   }
}



