// file      : GameOptions.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef GAMEOPTIONS_H_INCLUDED
#define GAMEOPTIONS_H_INCLUDED

#include "GameConstants.h"
#include <gamecontrol/GameMisc.h>
#include <string>

/** 
 * Class for the High score table. 
 * Not used by this project, only by the projects actually implementing 
 * the UI (MineUI_WTL ...) 
 */ 
class CScoreTable {
public: 
   CScoreTable(); 
   struct Entry {
      Entry() {}
      Entry(int nTime, char *pszName) : 
         m_nTime(nTime), m_name(pszName) 
      {} 
      int time() const {return m_nTime;}
      const std::string name() const {return m_name;}
      int m_nTime; 
      std::string m_name; 
   }; 
   const Entry& entry(GameConstant::GameLevel nLevel); 
   void setEntry(GameConstant::GameLevel nLevel, const std::string name, int nTime); 
public: 
   Entry m_scoreTable[3]; 
}; 

class CGameOptions {
public: 
   CGameOptions(); 
   void setLevel(GameConstant::GameLevel nLevel); 
   void setUserDefinedLevel(const CGameDim& gameDim); 
   GameConstant::GameLevel getLevel() const; 
   CGameDim getGameDim() const; 
   void setQMMarkers(bool bQMMarkers); 
   bool getQMMarkers() const; 
private: 
   GameConstant::GameLevel m_nGameLevel; 
   CGameDim m_gameDim; 
   bool m_bQMMarkers; 
}; 


#endif 
