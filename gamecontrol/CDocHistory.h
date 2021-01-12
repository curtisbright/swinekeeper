#ifndef CDOCHISTORY_H_INCLUDED
#define CDOCHISTORY_H_INCLUDED

#include "CGameDocument.h" 
#include <list>
#include "CObserveableGameDocument.h" 

class CDocHistory : public CObserveableGameDocument::CGameDocumentObserver  {

public: 
   CDocHistory(CObserveableGameDocument *pDoc);
   ~CDocHistory(); 
   void reset(); 
   void rememberDoc(const CGameDocument::CDocMemento &doc); 

   bool getDoc(int nIdx, CGameDocument::CDocMemento &doc) const; 
   int getDocCount() const; 
   
   void prev() {if (m_nCurDocIdx>0) m_nCurDocIdx--;}
   void next() {if (m_nCurDocIdx<getDocCount()-1) m_nCurDocIdx++;}
   bool getCurDoc(CGameDocument::CDocMemento &doc) const {
      return getDoc(m_nCurDocIdx, doc); 
   }

   virtual void notifyReset();  
   virtual void notifyChange();  

private: 
   CObserveableGameDocument *m_pDoc; 
   std::list<CGameDocument::CDocMemento> m_historyList;  
   int m_nCurDocIdx; 

   CDocHistory(const CDocHistory&); 
   CDocHistory& operator=(const CDocHistory&); 
}; 



#endif 
