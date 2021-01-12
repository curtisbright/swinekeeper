#ifndef COBSERVEABLEGAMEDOCUMENT_H_INCLUDED
#define COBSERVEABLEGAMEDOCUMENT_H_INCLUDED

#include <set> 
#include "CGameDocumentBase.h"

class CGameDocument; 

class CObserveableGameDocument : public CGameDocumentBase {
public: 
   
   class CGameDocumentObserver {
   public: 
      virtual ~CGameDocumentObserver() {}
      virtual void notifyReset()=0; 
      virtual void notifyChange()=0; 
   }; 

   CObserveableGameDocument(const CGameDim &gameDim); 
   ~CObserveableGameDocument(); 

   void addObserver(CGameDocumentObserver *pObs); 
   void removeObserver(CGameDocumentObserver *pObs); 

   const CPlayArray& playArray() const;   
   PlayState getPlayState() const;
   int getTime() const;

   void uncover(const CFieldPos &p);
   void uncoverNeighborsIfSat(const CFieldPos &p);
   void toggleMarker(const CFieldPos &p);
   void enableQMMarkers(bool bActive); 
   bool areQMMarkersEnabled() const; 

private: 
   CGameDocumentBase *m_pDoc; 
   std::set<CGameDocumentObserver*> m_observers; 

   void notifyReset(); 
   void notifyChange(); 

}; 

#endif 
