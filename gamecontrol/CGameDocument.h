// file      : CGameDocument.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CGAMEDOCUMENT_H_INCLUDED
#define CGAMEDOCUMENT_H_INCLUDED

#include <minebase/PlayArray.h>
#include "CGameTimer.h"
#include "GameMisc.h" 
#include "CGameDocumentBase.h" 

namespace Storage {
   class CSection; 
}

/** 
 * Document that holds the data of the minesweeper game. 
 * It implements the logic and the behaviour of the 
 * game. 
 * The class @ref CGameView is responsible for drawing 
 * this document.  
 */ 
class CGameDocument : public CGameDocumentBase {
public: 

   CGameDocument(const CGameDim &gameDim); 
   ~CGameDocument() 
   {
   }

   void setMemento(const CDocMemento &doc); 
   const CPlayArray& playArray() const {return m_PlayArray;}

   PlayState getPlayState() const {return m_nPlayState;}
      
   int getTime() const;

   void uncover(const CFieldPos &p); 
   void uncoverNeighborsIfSat(const CFieldPos &p); 
   void toggleMarker(const CFieldPos &p); 

   void enableQMMarkers(bool bEnabled) {
      m_bWithQMMarkers = bEnabled;
   }
   bool areQMMarkersEnabled() const {return m_bWithQMMarkers;}

   void transferData(Storage::CSection section); 

private: 
   CPlayArray m_PlayArray; 
   PlayState m_nPlayState; 
   CGameTimer m_timer; 
   bool m_bWithQMMarkers;   // true, if the user wants to have 
                            // 'questionmark' markers 

   void setPlayState(PlayState nPlayState); 
   bool acceptsActions() const {
      return    getPlayState() == PLAY_BEFORE_START 
             || getPlayState() == PLAY_RUNNING; 
   }
}; 



#endif 
