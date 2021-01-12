#include "StdAfx.h" 
#include "CHistoryDocument.h" 

#include <cassert>

CHistoryDocument::CHistoryDocument(CObserveableGameDocument *pDoc) : 
   m_history(pDoc), m_curDoc(pDoc->getGameDim()), m_bRewindActivated(false) 
{
}

CHistoryDocument::~CHistoryDocument()
{
}

const CPlayArray& CHistoryDocument::playArray() const
{
   return m_curDoc.playArray(); 
}
   
CGameDocumentBase::PlayState CHistoryDocument::getPlayState() const
{
   return m_curDoc.getPlayState(); 
}

int CHistoryDocument::getTime() const
{
   return m_curDoc.getTime(); 
}

void CHistoryDocument::uncover(const CFieldPos &)
{
}

void CHistoryDocument::uncoverNeighborsIfSat(const CFieldPos &)
{
}

void CHistoryDocument::toggleMarker(const CFieldPos &)
{
}



void CHistoryDocument::getDoc() {
   CGameDocument::CDocMemento doc; 
   if (m_history.getCurDoc(doc)) 
      m_curDoc.setMemento(doc); 
}


void CHistoryDocument::next()
{
   if (!m_bRewindActivated) 
      return; 
   m_history.next(); getDoc(); 
}

void CHistoryDocument::prev()
{
   if (!m_bRewindActivated) 
      return; 
   m_history.prev(); getDoc(); 
}

void CHistoryDocument::activateRewind()
{
   getDoc(); 
   m_bRewindActivated = true; 
}



