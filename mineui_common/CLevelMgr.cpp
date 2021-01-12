// file      : CLevelMgr.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#include "StdAfx.h" 
#include "CLevelMgr.h"
#include <cassert>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLevelMgr::CLevelMgr() : 
   m_pPersistentState(NULL) 
{
}


CLevelMgr::CLevelMgr(CPersistentDictionary *pDictionary)
{
   m_pPersistentState = new CPersistentState; 
   m_pPersistentState->init(pDictionary); 

   m_pPersistentState->getGameOptions(m_cachedGameOptions); 
}

void CLevelMgr::init(CPersistentDictionary *pDictionary)
{
   m_pPersistentState = new CPersistentState; 
   m_pPersistentState->init(pDictionary); 

   m_pPersistentState->getGameOptions(m_cachedGameOptions); 
}


CLevelMgr::~CLevelMgr()
{
   delete m_pPersistentState; 
}

void CLevelMgr::setLevel(GameConstant::GameLevel nLevel)
{
   assert(nLevel >= GameConstant::LEVEL_BEGINNER && nLevel <= GameConstant::LEVEL_EXPERT); 
   m_cachedGameOptions.setLevel(nLevel); 
   m_pPersistentState->setGameOptions(m_cachedGameOptions); 
}

void CLevelMgr::setUserDefinedLevel(const CGameDim &gameDim)
{
   m_cachedGameOptions.setUserDefinedLevel(gameDim); 
   m_pPersistentState->setGameOptions(m_cachedGameOptions); 
}

GameConstant::GameLevel CLevelMgr::getLevel() const
{
   assert(m_cachedGameOptions.getLevel() == getPersistentLevel()); 
   return m_cachedGameOptions.getLevel(); 
}


GameConstant::GameLevel CLevelMgr::getPersistentLevel() const
{
   CGameOptions gameOptions; 
   m_pPersistentState->getGameOptions(gameOptions); 
   return gameOptions.getLevel(); 
}

CGameDim CLevelMgr::getGameDim() const
{
   assert(m_cachedGameOptions.getGameDim() == getPersistentGameDim()); 
   return m_cachedGameOptions.getGameDim(); 
} 


CGameDim CLevelMgr::getPersistentGameDim() const
{
   CGameOptions gameOptions; 
   m_pPersistentState->getGameOptions(gameOptions); 
   return gameOptions.getGameDim(); 
}

bool CLevelMgr::hasReachedNewHighScore(int nTime) const
{
   GameConstant::GameLevel nLevel = getLevel(); 
   if (nLevel == GameConstant::LEVEL_USER_DEFINED) 
      return false; 

   CScoreTable scoreTable; 
   m_pPersistentState->getScoreTable(scoreTable); 
   int nCurrentHighScoreTime = scoreTable.entry(nLevel).time(); 
   
   return (nTime < nCurrentHighScoreTime); 
}

bool CLevelMgr::getCurrentName(std::string &name) const
{
   GameConstant::GameLevel nLevel = getLevel(); 
   if (nLevel == GameConstant::LEVEL_USER_DEFINED) 
      return false; 
   CScoreTable scoreTable; 
   m_pPersistentState->getScoreTable(scoreTable); 

   name = scoreTable.entry(nLevel).name(); 
   return true; 
} 

void CLevelMgr::enterHallOfFame(const std::string &name ,int nTime)
{
   assert(hasReachedNewHighScore(nTime)); 
   CScoreTable scoreTable; 
   m_pPersistentState->getScoreTable(scoreTable); 
   scoreTable.setEntry(getLevel(), name, nTime); 
   m_pPersistentState->setScoreTable(scoreTable); 
}

void CLevelMgr::clearScoreTable()
{
   CScoreTable scoreTable; 
   m_pPersistentState->setScoreTable(scoreTable); 
}

 
void CLevelMgr::getScoreTable(CScoreTable &scoreTable) const
{
   m_pPersistentState->getScoreTable(scoreTable); 
}

bool CLevelMgr::getQMMarkers() const
{
   return m_cachedGameOptions.getQMMarkers(); 
}

void CLevelMgr::setQMMarkers(bool bQMMarkers)
{
   m_cachedGameOptions.setQMMarkers(bQMMarkers);
   m_pPersistentState->setGameOptions(m_cachedGameOptions); 
}



