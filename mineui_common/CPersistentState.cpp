// file      : CPersistentState.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CPersistentState.h" 

#include <cassert>
#include <cstdio>

/* 
const char CPersistentState::szIniFileName[] = "SwineKeeper.ini";
const char CPersistentState::szIniFileOptionSection[] = "game";  
*/ 

// CPersistentState CPersistentState::m_instance; 

CPersistentState::CPersistentState() : 
    m_pDictionary(NULL) 
{
}

CPersistentState::~CPersistentState()
{
   delete m_pDictionary; 
}

/** 
 * Set the medium for the persistency. 
 * This class acquires ownership of pDictionary. 
 */ 
void CPersistentState::init(CPersistentDictionary *pDictionary)
{
   m_pDictionary = pDictionary; 
}


void CPersistentState::getScoreTable(CScoreTable &table) const
{
   table = CScoreTable(); 
   for(int i=0;i<3;i++) 
   {
      m_pDictionary->getInt(
         getScoreTimeKey(static_cast<GameConstant::GameLevel>(i)), 
         table.m_scoreTable[i].m_nTime); 
      
      m_pDictionary->getString(
         getScoreNameKey(static_cast<GameConstant::GameLevel>(i)), 
         table.m_scoreTable[i].m_name);         
   }
}

void CPersistentState::setScoreTable(const CScoreTable &table)
{
   for(int i=0;i<3;i++) 
   {
      m_pDictionary->setInt(
         getScoreTimeKey(static_cast<GameConstant::GameLevel>(i)), 
         table.m_scoreTable[i].m_nTime); 
      
      m_pDictionary->setString(
         getScoreNameKey(static_cast<GameConstant::GameLevel>(i)), 
         table.m_scoreTable[i].m_name);         
   }
}

void CPersistentState::getGameOptions(CGameOptions &options) const
{
   options = CGameOptions();

   std::string strLevel("expert"); 

   if (m_pDictionary->getString("level", strLevel)) 
   { 
      if (strLevel == std::string("beginner")) 
         options.setLevel(GameConstant::LEVEL_BEGINNER); 
      else if (strLevel == std::string("intermediate")) 
         options.setLevel(GameConstant::LEVEL_INTERMEDIATE); 
      else if (strLevel == std::string("expert")) 
         options.setLevel(GameConstant::LEVEL_EXPERT); 
      else if (strLevel == std::string("userdefined")) 
      {
         CGameDim gameDim(options.getGameDim()); 
         m_pDictionary->getInt("width", gameDim.m_nSizeX); 
         m_pDictionary->getInt("height", gameDim.m_nSizeY); 
         m_pDictionary->getInt("mines", gameDim.m_nMines); 
         assert(gameDim.hasReasonableValues());          
         if (gameDim.hasReasonableValues()) 
         {
            options.setUserDefinedLevel(gameDim);      
         }
      }
   }

   bool bQMMarkers = options.getQMMarkers(); 
   m_pDictionary->getBool("markers", bQMMarkers); 
   options.setQMMarkers(bQMMarkers); 
}

void CPersistentState::setGameOptions(const CGameOptions &options)
{
   std::string levelStr; 
   switch(options.getLevel()) {
      case GameConstant::LEVEL_BEGINNER: 
         levelStr = std::string("beginner"); 
         break; 
      case GameConstant::LEVEL_INTERMEDIATE: 
         levelStr = std::string("intermediate"); 
         break; 
      case GameConstant::LEVEL_EXPERT: 
         levelStr = std::string("expert"); 
         break; 
      case GameConstant::LEVEL_USER_DEFINED: 
         levelStr = std::string("userdefined"); 
         break; 
      default: 
         assert(0); 
         levelStr = std::string("expert"); 
   }
   m_pDictionary->setString("level", levelStr);  
   
   CGameDim gameDim(options.getGameDim()); 
   m_pDictionary->setInt("width", gameDim.sizeX()); 
   m_pDictionary->setInt("height", gameDim.sizeY()); 
   m_pDictionary->setInt("mines", gameDim.bombCount()); 

   m_pDictionary->setBool("markers", options.getQMMarkers()); 
}



const char *CPersistentState::getScoreTimeKey(GameConstant::GameLevel level) const
{
   switch (level) {
      case GameConstant::LEVEL_BEGINNER: 
         return "time-beginner"; 
      case GameConstant::LEVEL_INTERMEDIATE: 
         return "time-intermediate"; 
      case GameConstant::LEVEL_EXPERT: 
         return "time-expert"; 
      default: 
         return "time-xxx"; 
   }
}

const char *CPersistentState::getScoreNameKey(GameConstant::GameLevel level) const
{
   switch (level) {
      case GameConstant::LEVEL_BEGINNER: 
         return "name-beginner"; 
      case GameConstant::LEVEL_INTERMEDIATE: 
         return "name-intermediate"; 
      case GameConstant::LEVEL_EXPERT: 
         return "name-expert"; 
      default: 
         return "name-xxx"; 
   }
}

