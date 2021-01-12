#include "StdAfx.h" 
#include "CGameDocumentBase.h" 

bool CGameDocumentBase::CDocMemento::isEqualState(const CGameDocumentBase::CDocMemento &doc) const
{
   return m_playArray.isCoverStateEqual(doc.m_playArray); 
}

void CGameDocumentBase::getMemento(CGameDocumentBase::CDocMemento &doc) const 
{
   doc.m_nTime = getTime(); 
   doc.m_playArray = playArray(); 
   doc.m_playState = getPlayState(); 
}

bool CGameDocumentBase::isFieldEqual(const CDocMemento &doc, const CFieldPos &p) const
{
   return (doc.m_playArray[p] == field(p)); 
}

bool CGameDocumentBase::hasDocStateChanged(const CDocMemento &doc) const
{
   return (doc.m_playState != getPlayState()); 
}


const CPlayField& CGameDocumentBase::field(const CFieldPos &p) const
{
   return playArray().fieldValue(p); 
}

int CGameDocumentBase::getRemainingBombs() const
{
   return playArray().getBombCount() - playArray().getBombFlagCount(); 
}

CGameDim CGameDocumentBase::getGameDim() const
{
   CFieldRange range = playArray().range(); 
   return CGameDim(range.sizeX(), range.sizeY(), playArray().getBombCount()); 
}
