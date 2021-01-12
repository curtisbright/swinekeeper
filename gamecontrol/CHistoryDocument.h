#ifndef CHISTORYDOCUMENT_H_INCLUDED
#define CHISTORYDOCUMENT_H_INCLUDED

#include "CGameDocumentBase.h" 
#include "CGameDocument.h" 
#include "CDocHistory.h" 

class CHistoryDocument : public CGameDocumentBase
{
public: 

   CHistoryDocument(CObserveableGameDocument *pDoc); 
   ~CHistoryDocument(); 

   const CPlayArray& playArray() const;    
   PlayState getPlayState() const;
   int getTime() const;

   void uncover(const CFieldPos &p);
   void uncoverNeighborsIfSat(const CFieldPos &p);
   void toggleMarker(const CFieldPos &p);
   void enableQMMarkers(bool) {}
   bool areQMMarkersEnabled() const {return false;}

   void activateRewind(); 
   void next(); 
   void prev(); 

private: 
   CDocHistory m_history; 
   CGameDocument m_curDoc; 
   bool m_bRewindActivated; 
   void getDoc(); 
}; 

#endif 
