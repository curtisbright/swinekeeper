// file      : GameOptions.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "GameOptions.h" 
#include <cassert>

CScoreTable::CScoreTable() 
{
   for(int i=0;i<3;i++) 
   {
      m_scoreTable[i] = CScoreTable::Entry(999, "unknown"); 
   }
} 

const CScoreTable::Entry& CScoreTable::entry(GameConstant::GameLevel nLevel)
{
   int nIdx = (int)nLevel; 
   assert(nIdx >= 0 && nIdx < 3); 
   return m_scoreTable[nIdx]; 
}

void CScoreTable::setEntry(GameConstant::GameLevel nLevel, const std::string name, int nTime)
{
   int nIdx = (int)nLevel; 
   assert(nIdx >= 0 && nIdx < 3); 
   m_scoreTable[nIdx].m_name = name;
   m_scoreTable[nIdx].m_nTime = nTime;
}


CGameOptions::CGameOptions() : 
   m_bQMMarkers(false) 
{
   setLevel(GameConstant::LEVEL_EXPERT); 
} 

void CGameOptions::setLevel(GameConstant::GameLevel nLevel)
{
   // use CGameOptions::setUserDefinedLevel to set user defined level 
   assert(nLevel >= GameConstant::LEVEL_BEGINNER && nLevel <= GameConstant::LEVEL_EXPERT); 
   m_nGameLevel = nLevel; 
   m_gameDim = GameConstant::getGameDimOfLevel(m_nGameLevel); 
}

void CGameOptions::setUserDefinedLevel(const CGameDim& gameDim)
{
   m_nGameLevel = GameConstant::LEVEL_USER_DEFINED; 
   m_gameDim = gameDim; 
}

GameConstant::GameLevel CGameOptions::getLevel() const
{
   return m_nGameLevel; 
}

CGameDim CGameOptions::getGameDim() const
{
   return m_gameDim; 
}

void CGameOptions::setQMMarkers(bool bQMMarkers)
{
   m_bQMMarkers = bQMMarkers; 
}

bool CGameOptions::getQMMarkers() const
{
   return m_bQMMarkers; 
}
     
