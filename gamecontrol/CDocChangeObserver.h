#ifndef CDOCCHANGEOBSERVER_H_INCLUDED
#define CDOCCHANGEOBSERVER_H_INCLUDED

#include "CGameDocumentBase.h" 

class CDocChangeObserver {

public: 
   CDocChangeObserver(CGameDocumentBase *pDoc); 
   void storeState(); 
   void forceFullUpdate(); 
   bool isFullUpdateRequired() const {
      return m_bFullUpdate || hasDocStateChanged(); 
   }
   bool hasDocStateChanged() const {
      return m_pDoc->hasDocStateChanged(m_lastState);
   }
   bool hasFieldChanged(const CFieldPos &pos) const; 
private: 
   CGameDocumentBase *m_pDoc; 
   CGameDocumentBase::CDocMemento m_lastState; 
   bool m_bFullUpdate;
}; 

#endif 

