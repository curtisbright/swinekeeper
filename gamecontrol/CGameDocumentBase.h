#ifndef CGAMEDOCUMENTBASE_H_INCLUDED
#define CGAMEDOCUMENTBASE_H_INCLUDED

#include <minebase/PlayArray.h>
#include "CGameTimer.h"
#include "GameMisc.h" 

class CGameDocumentBase {
public:       

   enum PlayState {
      PLAY_BEFORE_START, 
      PLAY_RUNNING, 
      PLAY_WON, 
      PLAY_LOST
   }; 

   class CDocMemento {
      friend class CGameDocumentBase; 
      friend class CGameDocument; 
   public: 
      bool isEqualState(const CDocMemento &doc) const; 
   private: 
      CPlayArray m_playArray; 
      PlayState m_playState; 
      int m_nTime;       
   }; 

   virtual ~CGameDocumentBase() {}

   virtual void getMemento(CDocMemento &doc) const; 
   // virtual void setMemento(const CDocMemento &doc)=0; 
   bool isFieldEqual(const CDocMemento &doc, const CFieldPos &p) const; 
   bool hasDocStateChanged(const CDocMemento &doc) const; 

   virtual const CPlayArray& playArray() const=0; 
   
   virtual PlayState getPlayState() const = 0;
   virtual int getTime() const = 0;
   
   virtual void uncover(const CFieldPos &p) = 0;
   virtual void uncoverNeighborsIfSat(const CFieldPos &p) = 0;
   virtual void toggleMarker(const CFieldPos &p) = 0;
   virtual void enableQMMarkers(bool bActive) = 0; 
   virtual bool areQMMarkersEnabled() const=0;

   virtual CGameDim getGameDim() const;     
   virtual const CPlayField& field(const CFieldPos &p) const;
   virtual int getRemainingBombs() const;
}; 


#endif 
