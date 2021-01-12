#include "CDocChangeObserver.h" 

CDocChangeObserver::CDocChangeObserver(CGameDocumentBase *pDoc) : 
   m_pDoc(pDoc),
   m_bFullUpdate(false)
{
   storeState();
}

void CDocChangeObserver::storeState() {
   m_pDoc->getMemento(m_lastState); 
   m_bFullUpdate = false; 
}

void CDocChangeObserver::forceFullUpdate() {
   m_bFullUpdate = true; 
}

bool CDocChangeObserver::hasFieldChanged(const CFieldPos &pos) const 
{
   return m_bFullUpdate 
          || !(m_pDoc->isFieldEqual(m_lastState, pos));
}
