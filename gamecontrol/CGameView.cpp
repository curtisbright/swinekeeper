// file      : CGameView.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CGameView.h" 

#include "CGameDocumentBase.h" 
#include "CGlobalResourceSet.h" 
#include <mineuibase/UIAux.h>

CGameView::CGameView(CGameDocumentBase *pDoc) : 
   m_pDoc(pDoc),
   m_changeObserver(pDoc),
   m_pCurFieldView(NULL),  
   m_pListener(NULL) 
{
   recomputeLayout(); 
   computeFieldViewFromDocState(); 
}   

CGameView::~CGameView() {
   delete m_pCurFieldView; 
}


/** 
 * Uses the current dimensions of the game document to resize the view. 
 * Must be called after the size of the game document changed. 
 * 
 * XXX probably CGameView should get a resize method that resizes the document too XXX 
 */ 
void CGameView::recomputeLayout() {
   
   m_LayoutMgr.init(
      CGlobalResourceSet::instance()->m_pSmilies->getSize(),   
      CGlobalResourceSet::instance()->m_pDigits->getSize(),   
      CGlobalResourceSet::instance()->m_pFieldIcons->getSize()); 

   m_LayoutMgr.resize(m_pDoc->getGameDim().sizeX(), m_pDoc->getGameDim().sizeY()); 
   m_changeObserver.forceFullUpdate(); 
}


/** 
 * Draws the client area of the minesweeper window. 
 * 
 * @param pCtx Drawing context 
 * @param deviceState State of input device, used to determine state of smilie button 
 * @param updateInfo Describes which parts of the window need to be redrawn 
 */ 
void CGameView::draw(CUIDrawContextBase *pCtx, 
          const CDeviceStateInfo &deviceState,
          const CUpdateViewInfo &updateInfo) 
{
   bool bFullUpdate = 
         m_changeObserver.isFullUpdateRequired() 
      || updateInfo.doFullUpdate(); 
   
   // draw the frames 
   if (bFullUpdate) 
   {
      m_LayoutMgr.draw(pCtx);    
   }
   
   // draw the number of remaining bombs 
   UIAux::drawNumber(
      pCtx, 
      CGlobalResourceSet::instance()->m_pDigits.get(), 3, 
      m_LayoutMgr.getLeftDigitsRect().minV(), 
      m_pDoc->getRemainingBombs()); 

   // draw the current time 
   UIAux::drawNumber(
      pCtx, 
      CGlobalResourceSet::instance()->m_pDigits.get(), 3, 
      m_LayoutMgr.getRightDigitsRect().minV(), 
      m_pDoc->getTime()); 
      
   // compute the smilie state 
   CGameDocumentBase::PlayState nPlayState = m_pDoc->getPlayState(); 
   IconType::Smilie nSmilie; 
   if ( nPlayState == CGameDocumentBase::PLAY_WON) 
      nSmilie = IconType::SMILIE_WON; 
   else if ( nPlayState == CGameDocumentBase::PLAY_LOST) 
      nSmilie = IconType::SMILIE_LOST; 
   else 
   {
      nSmilie = IconType::SMILIE_STANDARD;   
      // actually a responsibility of the InputDevice
      if (deviceState.m_bIsSmiliePushed)      
         nSmilie = IconType::SMILIE_PUSHED; 
      else if (deviceState.m_bIsSolverProcessing) 
         nSmilie = IconType::SMILIE_SOLVING; 
      else if (deviceState.m_bIsButtonPushed) 
         nSmilie = IconType::SMILIE_ONCLICK; 
   }
   // draw smilie 
   pCtx->drawIcon(
      CGlobalResourceSet::instance()->m_pSmilies.get(),
      nSmilie, 0, 
      m_LayoutMgr.getSmilieRect().minV()
   ); 

   // draw the array 
   int nSizeX = m_pDoc->getGameDim().sizeX(), nSizeY = m_pDoc->getGameDim().sizeY(); 
   int nX, nY; 

   for(nX = 0; nX < nSizeX; nX++) 
   {
      for(nY = 0; nY < nSizeY; nY++) 
      {  
         CFieldPos pos(nX, nY); 

         if (   bFullUpdate 
             || m_changeObserver.hasFieldChanged(pos) 
             || updateInfo.doUpdateField(pos)) {
            CUIRect rect = m_LayoutMgr.getFieldRect(pos); 
            m_pCurFieldView->drawField(pCtx, rect, pos); 
         }
      }
   }
   m_changeObserver.storeState(); 
}

/** 
 * Returns a string describing somehow the field at position 'fieldPos'. 
 * 
 * The kind of strings returned depends on the current field view. 
 * Usually, only field views that show a result of an algorithm will return descriptions. 
 * 
 * @return true iff this field has a description string (otherwise, 'str' is undefined) 
 * @param fieldPos Position of the field from which a description is requested 
 * @param str Contains the description if the function returns with true as return value. 
 */ 
bool CGameView::getToolTipMsg(const CFieldPos &fieldPos, std::string& str) const
{
   return m_pCurFieldView->getFieldMessage(fieldPos, str);       
}

/** 
 * Returns true if the field at position 'fieldPos' does not display something important. 
 * 
 * Currently, it only returns true if the field is a covered field without a marker. 
 * The function should be used by input devices to determine if they may 
 * redraw the area occupied by the field to display their own state. 
 * 
 * The function is used to implement a behaviour of the original minesweeper: 
 * if the user left-/middle-clicks on a field, but does not release the button, 
 * the clicked field is shown in a depressed state. 
 */ 
bool CGameView::isRedrawable(const CFieldPos &fieldPos) const
{
   if (!fieldPos.inRange(m_pDoc->getGameDim().sizeX(), m_pDoc->getGameDim().sizeY())) 
      return false; 

   return m_pCurFieldView->isRedrawable(fieldPos);       
}

/** 
 * This method returns the size of the client area the view needs to display itself. 
 * The method @ref CGameView::draw expects that the drawing area has 
 * the size returned by this function. 
 * Call after resizing the view using @ref CGameView::recomputeLayout. 
 */ 
CUIRect CGameView::getFieldRect(const CFieldPos &fieldPos) const
{
   return m_LayoutMgr.getFieldRect(fieldPos); 
} 

/** 
 * Called by the client if the mouse button is depressed on the field. 
 * 
 * Note that this minesweeper implementation supports other input devices beside 
 * mouses. However, these other devices are simply used to emulate a mouse. 
 */    
void CGameView::onPushField(const CFieldPos &fieldPos, MouseButton nButton)
{
   if (m_pCurFieldView->isRunningGameView() && nButton == BUTTON_RIGHT) 
      m_pDoc->toggleMarker(fieldPos); 
}

/** 
 * Called by the client if a mouse button is released on the field. 
 */ 
void CGameView::onReleaseField(const CFieldPos &fieldPos, MouseButton nButton)
{
   if (m_pCurFieldView->isRunningGameView())
   {
      if (nButton == BUTTON_LEFT) 
         m_pDoc->uncover(fieldPos); 

      if (nButton == BUTTON_MIDDLE) 
         m_pDoc->uncoverNeighborsIfSat(fieldPos);
   }

   if (!m_pCurFieldView->onPushField(fieldPos, (int)nButton)) 
   {
      computeFieldViewFromDocState(); 
   }
}

/** 
 * Called by the client if the smilie is pushed & released. 
 */ 
void CGameView::pushSmilie()
{
   if (m_pListener) 
      m_pListener->onPushSmilie(); 
}

void CGameView::computeFieldViewFromDocState()
{
   CFieldViewBase *pNewView = NULL; 

   if (m_pDoc->getPlayState() == CGameDocumentBase::PLAY_LOST) 
   {
      pNewView = new CLostFieldView; 
   }
   else 
   {
      pNewView = new CRunningFieldView; 
   }

   setFieldView(pNewView); 
}


/** 
 * Set the current field view 
 * The callee acquires ownership of the object *pFieldView
 */ 
bool CGameView::setFieldView(CFieldViewBase *pFieldView) 
{
   if (pFieldView == NULL) 
   {
      computeFieldViewFromDocState(); 
      return true; 
   }

   if (!pFieldView->initDoc(m_pDoc)) 
   {
      delete pFieldView; 
      return false; 
   }
   bool bUpdateNeeded = (    
            m_pCurFieldView==NULL 
       ||  !m_pCurFieldView->isRunningGameView() 
       ||  !pFieldView->isRunningGameView()
   ); 

   delete m_pCurFieldView; 

   m_pCurFieldView = pFieldView; 

   if (bUpdateNeeded) 
      m_changeObserver.forceFullUpdate();

   return true; 
}



