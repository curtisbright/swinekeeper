// file      : CGameManager.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CGameManager.h" 

#include "CGameView.h" 
#include "CGameDocument.h"
#include "CSolutionFieldView.h"
#include "InputDevices.h" 
#include "CDocHistory.h" 
#include "CObserveableGameDocument.h" 
#include "CHistoryDocument.h" 

#include <time.h>
#include <cassert>
#include <memory>

class CViewListenerMgr : public CGameView::CGameViewListener {
public: 
   CViewListenerMgr() : m_pGameMgr(NULL) {}
   void init(CGameManager *pGameMgr) {m_pGameMgr = pGameMgr;}
   virtual void onPushSmilie() {
      if (m_pGameMgr) m_pGameMgr->resetGame(); 
   }

private: 
   CGameManager *m_pGameMgr; 
}; 

class CGameManagerImpl {
public: 
   CGameManagerImpl() : 
      m_pInputDevice(NULL), 
      m_pCurDoc(NULL),
      m_bUserMayEnterHallOfFame(true)
     {} 

   CInputDeviceBase *m_pInputDevice; 
   std::auto_ptr<CObserveableGameDocument> m_pDoc; 
   std::auto_ptr<CHistoryDocument> m_pHistDoc;  
   CGameDocumentBase *m_pCurDoc; 

   std::auto_ptr<CGameView> m_pView; 
   CViewListenerMgr m_viewListener; 

  bool m_bUserMayEnterHallOfFame; 
}; 

CGameManager::CGameManager() : 
   m_pImpl(new CGameManagerImpl)
{}



CGameManager::~CGameManager() {
   delete m_pImpl; 
}

void CGameManager::init(CInputDeviceBase *pInputDevice) {
   m_pImpl->m_pInputDevice = pInputDevice; 
   m_pImpl->m_viewListener.init(this); 
   // initialize random number generator 
   srand(time(NULL)); 
}

CGameDim CGameManager::getGameDim() const {
   if (m_pImpl->m_pDoc.get() == NULL) {return CGameDim();}

   return m_pImpl->m_pDoc->getGameDim();    
}

void CGameManager::resize(const CGameDim &newGameDim) {

   std::auto_ptr<CObserveableGameDocument> obsDoc(new CObserveableGameDocument(newGameDim)); 
   std::auto_ptr<CHistoryDocument> histDoc(new CHistoryDocument(obsDoc.get())); 
   
   m_pImpl->m_pHistDoc = histDoc; 
   m_pImpl->m_pDoc = obsDoc;

   m_pImpl->m_pCurDoc = m_pImpl->m_pDoc.get(); 

   m_pImpl->m_bUserMayEnterHallOfFame = true; 

   showDoc(m_pImpl->m_pDoc.get()); 
}

void CGameManager::resetGame() {
   resize(getGameDim()); 
}

bool CGameManager::userMayEnterHallOfFame() const {
  return m_pImpl->m_bUserMayEnterHallOfFame; 
} 

CUISize CGameManager::getClientWindowSize() const {
   return m_pImpl->m_pView->getClientSize(); 
}

void CGameManager::enableQMMarkers(bool bActive) {
   m_pImpl->m_pDoc->enableQMMarkers(bActive); 
}

bool CGameManager::areQMMarkersEnabled() const {
   return m_pImpl->m_pDoc->areQMMarkersEnabled(); 
}


int CGameManager::getTime() const {
   return m_pImpl->m_pDoc->getTime(); 
}

bool CGameManager::isGameRunning() const {
   return m_pImpl->m_pDoc->getPlayState() == CGameDocument::PLAY_RUNNING; 
}

bool CGameManager::isGameWon() const {
   return m_pImpl->m_pDoc->getPlayState() == CGameDocument::PLAY_WON; 
}

bool CGameManager::isGameFinished() const {
   return m_pImpl->m_pDoc->getPlayState() == CGameDocument::PLAY_WON 
       || m_pImpl->m_pDoc->getPlayState() == CGameDocument::PLAY_LOST; 
}
   

void CGameManager::showSolution() {
   if (   m_pImpl->m_pCurDoc->getPlayState() != CGameDocument::PLAY_RUNNING
       && m_pImpl->m_pCurDoc->getPlayState() != CGameDocument::PLAY_LOST)
      return; 

   m_pImpl->m_pView->setFieldView(new CSolutionFieldView()); 

   m_pImpl->m_bUserMayEnterHallOfFame = false; 
}

void CGameManager::hideSolution()
{
   m_pImpl->m_pView->setFieldView(NULL); 
}


void CGameManager::draw(CUIDrawContextBase *pCtx, bool bFullUpdate, bool bIsProcessing)
{
   CGameView::CUpdateViewInfo updateInfo; 
   CGameView::CDeviceStateInfo deviceInfo; 

   if (bFullUpdate) updateInfo.setFullUpdate(); 

   m_pImpl->m_pInputDevice->getUpdateViewInfo(updateInfo); 
   m_pImpl->m_pInputDevice->getViewDeviceStateInfo(deviceInfo); 

   deviceInfo.m_bIsSolverProcessing = bIsProcessing; 

   m_pImpl->m_pView->draw(
      pCtx, 
      deviceInfo,
      updateInfo); 

   m_pImpl->m_pInputDevice->draw(pCtx, bFullUpdate); 
}

bool CGameManager::getToolTipMsg(std::string& str) const {
   CFieldPos fieldPos; 
   if (!m_pImpl->m_pInputDevice->getCurFieldPos(fieldPos)) 
      return false; 
   return m_pImpl->m_pView->getToolTipMsg(fieldPos, str); 
}

void CGameManager::activateRewind() {
   m_pImpl->m_pHistDoc->activateRewind(); 
   showDoc(m_pImpl->m_pHistDoc.get()); 
   m_pImpl->m_pCurDoc = m_pImpl->m_pHistDoc.get(); 
}

void CGameManager::historyPrev() {
   m_pImpl->m_pHistDoc->prev(); 
   m_pImpl->m_pView->resetFieldView(); 
}

void CGameManager::historyNext() {
   m_pImpl->m_pHistDoc->next(); 
   m_pImpl->m_pView->resetFieldView(); 
}

void CGameManager::showDoc(CGameDocumentBase *pDoc) {

   std::auto_ptr<CGameView> gameView(new CGameView(pDoc)); 
   m_pImpl->m_pView = gameView; 

   m_pImpl->m_pInputDevice->setView(m_pImpl->m_pView.get());       
   m_pImpl->m_pView->setListener(&m_pImpl->m_viewListener); 
}

