#include "StdAfx.h" 
#include "CDocHistory.h" 

#include <cassert>

CDocHistory::CDocHistory(CObserveableGameDocument *pDoc) : 
   m_pDoc(pDoc),
   m_nCurDocIdx(0) 
{
   m_pDoc->addObserver(this); 
   assert(getDocCount() >= 0); 
}

CDocHistory::~CDocHistory()
{
   m_pDoc->removeObserver(this);    
}

void CDocHistory::reset()
{
   m_historyList.clear();
   m_nCurDocIdx = 0; 
}

void CDocHistory::rememberDoc(const CGameDocument::CDocMemento &doc)
{
   // this function sometimes was called with an empty 
   // m_historyList. If I called isEqualState() then, the 
   // function crashed because the first parameter was not valid. 
   // The history mechanism is still too error prone, I'll have to 
   // simplify it. 
   if (m_historyList.empty() || !doc.isEqualState(m_historyList.back())) 
   {
      m_historyList.push_back(doc); 
      m_nCurDocIdx = getDocCount()-1; 
   }
} 

bool CDocHistory::getDoc(int nIdx, CGameDocument::CDocMemento &doc) const
{
   std::list<CGameDocument::CDocMemento>::const_iterator iter = m_historyList.begin(); 
   for(int i=0;i<nIdx;i++) {      
      if (iter == m_historyList.end()) 
         return false; 
      iter ++; 
   }
   if (iter == m_historyList.end()) 
      return false; 

   doc = *iter; 
   return true; 
}

int CDocHistory::getDocCount() const
{
   return m_historyList.size(); 
}

void CDocHistory::notifyReset()
{
   reset(); 
   notifyChange(); 
}

void CDocHistory::notifyChange()
{
   CGameDocument::CDocMemento doc; 
   m_pDoc->getMemento(doc); 
   rememberDoc(doc);            
}

