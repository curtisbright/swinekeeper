#include "StdAfx.h" 
#include "CActionRecorder.h" 

#include "CGameDocumentBase.h" 
#include "CGameDocument.h" 
#include <cassert>


void CGameDocAction::execute(CGameDocumentBase *pDoc)
{
   switch(m_action) {
      case ACTION_UNCOVER:
         pDoc->uncover(m_pos);  
         break; 
      case ACTION_UNCOVERNEIGHBORS:
         pDoc->uncoverNeighborsIfSat(m_pos);  
         break; 
      case ACTION_TOGGLE_MARKER:
         pDoc->toggleMarker(m_pos);  
         break; 
      default: 
         assert(0); 
   }
}


CActionRecorder::CActionRecorder(const CGameDim &gameDim) : 
   m_pDoc(new CGameDocument(gameDim)) 
{
}

CActionRecorder::~CActionRecorder()
{
   assert(m_observers.size()==0); 
   delete m_pDoc; 
}

void CActionRecorder::addObserver(CActionObserver *pObs)
{
   bool bSuc = m_observers.insert(pObs).second; 
   assert(bSuc); 
}

void CActionRecorder::removeObserver(CActionObserver *pObs)
{
   int nElms = m_observers.erase(pObs); 
   assert(nElms==1); 
}

const CPlayArray& CActionRecorder::playArray() const
{
   return m_pDoc->playArray(); 
}

CGameDocumentBase::PlayState CActionRecorder::getPlayState() const
{
   return m_pDoc->getPlayState(); 
}

int CActionRecorder::getTime() const
{
   return m_pDoc->getTime(); 
}

void CActionRecorder::uncover(const CFieldPos &p)
{
   notifyAction(p, CGameDocAction::ACTION_UNCOVER); 
   m_pDoc->uncover(p); 
}

void CActionRecorder::uncoverNeighborsIfSat(const CFieldPos &p)
{
   notifyAction(p, CGameDocAction::ACTION_UNCOVERNEIGHBORS); 
   m_pDoc->uncoverNeighborsIfSat(p); 
}

void CActionRecorder::toggleMarker(const CFieldPos &p)
{
   notifyAction(p, CGameDocAction::ACTION_TOGGLE_MARKER); 
   m_pDoc->toggleMarker(p); 
}

void CActionRecorder::enableQMMarkers(bool bActive)
{
   m_pDoc->enableQMMarkers(bActive); 
}

void CActionRecorder::notifyAction(const CFieldPos &p, CGameDocAction::ActionType nType)
{
   CGameDocAction action(p,nType); 
   std::set<CActionObserver*>::iterator iter; 
   for(iter = m_observers.begin();iter != m_observers.end(); iter++) 
   {
      (*iter)->notifyAction(&action); 
   }
}

CActionHistory::CActionHistory(CActionRecorder *pActionRecorder) :
   m_pActionRecorder(pActionRecorder)
{
   m_pActionRecorder->addObserver(this); 
}
 
CActionHistory::~CActionHistory()
{
   m_pActionRecorder->removeObserver(this);    
}

void CActionHistory::notifyAction(const CGameDocAction *pAction)
{
   CHistoryEntry histEntry; 
   histEntry.m_action = *pAction; 
   m_pActionRecorder->getMemento(histEntry.m_docMemento); 
      m_historyList.push_back(histEntry); 
}




