// file      : CLevelMgr.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#if !defined(AFX_CLEVELMGR_H__B0A5E1C9_80C2_11D4_BEF8_000000000000__INCLUDED_)
#define AFX_CLEVELMGR_H__B0A5E1C9_80C2_11D4_BEF8_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CPersistentDictionary.h" 
#include <gamecontrol/GameMisc.h>
#include "GameConstants.h"
#include "CPersistentState.h"

/** 
 * Handles the currently selected Level and the Hall of Fame
 */ 
class CLevelMgr  
{
public:
   CLevelMgr();
   CLevelMgr(CPersistentDictionary *pDictionary);
   virtual ~CLevelMgr();
   
   void init(CPersistentDictionary *pDictionary); 

   void setLevel(GameConstant::GameLevel nLevel); 
   void setUserDefinedLevel(const CGameDim &gameDim); 
   GameConstant::GameLevel getLevel() const; 
   CGameDim getGameDim() const; 

   bool hasReachedNewHighScore(int nTime) const; 
   void enterHallOfFame(const std::string &name ,int nTime); 
   void getScoreTable(CScoreTable &table) const; 
   void clearScoreTable(); 
   bool getCurrentName(std::string &name) const; 

   bool getQMMarkers() const; 
   void setQMMarkers(bool bQMMarkers); 
private: 
   
   CPersistentState *m_pPersistentState; 

   // persistency might not work, since it needs access to the hard drive
   // to keep the game playable, I cache the values here 
   CGameOptions m_cachedGameOptions;    

   GameConstant::GameLevel getPersistentLevel() const; 
   CGameDim getPersistentGameDim() const; 
};

#endif // !defined(AFX_CLEVELMGR_H__B0A5E1C9_80C2_11D4_BEF8_000000000000__INCLUDED_)
