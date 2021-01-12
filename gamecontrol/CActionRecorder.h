#ifndef CACTIONRECORDER_H_INCLUDED
#define CACTIONRECORDER_H_INCLUDED

#include <set> 
#include <list>
#include "CGameDocumentBase.h"

class CGameDocument; 

class CGameDocAction {
public: 
   enum ActionType {
      ACTION_UNCOVER, 
      ACTION_UNCOVERNEIGHBORS,
      ACTION_TOGGLE_MARKER
   }; 

   CGameDocAction() : m_action(ACTION_UNCOVER) {}
   CGameDocAction(const CFieldPos &p, ActionType nType) : 
      m_pos(p), m_action(nType) {}
   void execute(CGameDocumentBase *pDoc); 

private: 
   CFieldPos m_pos; 
   ActionType m_action; 
}; 


class CActionRecorder : public CGameDocumentBase {
public: 

   class CActionObserver {
   public: 
      virtual ~CActionObserver() {}
      virtual void notifyAction(const CGameDocAction *) = 0; 
   }; 

   CActionRecorder(const CGameDim &gameDim); 
   ~CActionRecorder(); 

   void addObserver(CActionObserver *pObs); 
   void removeObserver(CActionObserver *pObs); 

   const CPlayArray& playArray() const;   
   PlayState getPlayState() const;
   int getTime() const;

   void uncover(const CFieldPos &p);
   void uncoverNeighborsIfSat(const CFieldPos &p);
   void toggleMarker(const CFieldPos &p);
   void enableQMMarkers(bool bActive); 

private: 
   CGameDocumentBase *m_pDoc; 
   std::set<CActionObserver*> m_observers; 

   void notifyAction(const CFieldPos &p, CGameDocAction::ActionType nType); 
}; 

class CActionHistory : public CActionRecorder::CActionObserver {
public:
   CActionHistory(CActionRecorder *pActionRecorder); 
   ~CActionHistory(); 
   void notifyAction(const CGameDocAction *pAction); 
private: 
   struct CHistoryEntry {
      CGameDocumentBase::CDocMemento m_docMemento; 
      CGameDocAction m_action; 
   }; 

   std::list<CHistoryEntry> m_historyList;  
   CActionRecorder *m_pActionRecorder; 

   CActionHistory(const CActionHistory&); 
   CActionHistory& operator=(const CActionHistory&); 
}; 

#endif 
