#include "StdAfx.h" 
#include "CObserveableGameDocument.h" 

#include "CGameDocumentBase.h" 
#include "CGameDocument.h" 
#include <cassert>


CObserveableGameDocument::CObserveableGameDocument(const CGameDim &gameDim) : 
   m_pDoc(new CGameDocument(gameDim)) 
{
}

CObserveableGameDocument::~CObserveableGameDocument()
{
   assert(m_observers.size()==0); 
   delete m_pDoc; 
}

void CObserveableGameDocument::addObserver(CGameDocumentObserver *pObs)
{
   bool bSuc = m_observers.insert(pObs).second; 
   assert(bSuc); 
   pObs->notifyReset(); 
}

void CObserveableGameDocument::removeObserver(CGameDocumentObserver *pObs)
{
   int nElms = m_observers.erase(pObs); 
   assert(nElms==1); 
}

const CPlayArray& CObserveableGameDocument::playArray() const
{
   return m_pDoc->playArray(); 
}

CGameDocumentBase::PlayState CObserveableGameDocument::getPlayState() const
{
   return m_pDoc->getPlayState(); 
}

int CObserveableGameDocument::getTime() const
{
   return m_pDoc->getTime(); 
}

void CObserveableGameDocument::uncover(const CFieldPos &p)
{
   m_pDoc->uncover(p); 
   notifyChange(); 
}

void CObserveableGameDocument::uncoverNeighborsIfSat(const CFieldPos &p)
{
   m_pDoc->uncoverNeighborsIfSat(p); 
   notifyChange(); 
}

void CObserveableGameDocument::toggleMarker(const CFieldPos &p)
{
   m_pDoc->toggleMarker(p); 
   notifyChange(); 
}

void CObserveableGameDocument::enableQMMarkers(bool bActive)
{
   m_pDoc->enableQMMarkers(bActive); 
}

bool CObserveableGameDocument::areQMMarkersEnabled() const
{
   return m_pDoc->areQMMarkersEnabled(); 
}



void CObserveableGameDocument::notifyReset()
{
   std::set<CGameDocumentObserver*>::iterator iter; 
   for(iter = m_observers.begin();iter != m_observers.end(); iter++) 
   {
      (*iter)->notifyReset(); 
   }
}

void CObserveableGameDocument::notifyChange()
{
   std::set<CGameDocumentObserver*>::iterator iter; 
   for(iter = m_observers.begin();iter != m_observers.end(); iter++) 
   {
      (*iter)->notifyChange(); 
   }
}