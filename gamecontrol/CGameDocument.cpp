// file      : CGameDocument.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CGameDocument.h"

#include <mineuibase/UIDrawContext.h>
#include <storage/Document.h>


CGameDocument::CGameDocument(const CGameDim &gameDim) : 
   m_nPlayState(PLAY_BEFORE_START),
   m_bWithQMMarkers(false)
{
   /* 
   m_PlayArray.makePlayField(
      gameDim.sizeX(), 
      gameDim.sizeY(), 
      gameDim.bombCount());  
   */ 
   m_PlayArray.initPlayField(gameDim.sizeX(), gameDim.sizeY(), gameDim.bombCount()); 
}


void CGameDocument::setMemento(const CGameDocument::CDocMemento &doc)
{
   m_timer.setStoppedTime(doc.m_nTime); 
   m_PlayArray = doc.m_playArray; 
   m_nPlayState = doc.m_playState; 
}


/** 
 * Returns the current time. 
 * Note that this function returns a valid time 
 * independant of the state of the game. 
 * (e.g. if the game has not yet started, it simply 
 * returns 0) 
 */ 
int CGameDocument::getTime() const 
{
   int nTime = m_timer.getSecsValue(); 
   if (nTime > 999) nTime = 999; 
   return nTime; 
}

/** 
 * Uncover a field. 
 * 
 * This function does all things that usually happen if a user 
 * left-clicks on a covered field: 
 * - If the game is not started yet this function will start the game. 
 * - If a field with a bomb is uncovered, the game goes into the 'game-lost' state. 
 * - If the last covered field is uncovered, the game is won. 
 * - The method has no effect if the game is already finished. 
 * 
 * @param pos Position of the field to uncover 
 */ 
void CGameDocument::uncover(const CFieldPos &pos)
{
   if (!acceptsActions())
      return; 

   // don't uncover fields that are marked as bombs 
   if (m_PlayArray[pos].isMarkedAsBomb()) 
         return; 

   if (m_nPlayState == PLAY_BEFORE_START)
   {
      m_PlayArray.dropBombs(pos); 
      setPlayState(PLAY_RUNNING);
   }

   m_PlayArray[pos].uncover(); 

   if (m_PlayArray[pos].isBomb()) 
   {
      setPlayState(PLAY_LOST); 
      return; 
   }
   if (m_PlayArray.getCoveredFieldCount() == m_PlayArray.getBombCount()) 
   {
      setPlayState(PLAY_WON); 
      return; 
   }
   
   // uncover neighbored fields if the bomb count of this field is zero
   if (!m_PlayArray[pos].isBomb() && m_PlayArray[pos].getCount()==0) 
   {
      // very simple flood-fill implementation 
      // XXX results in very deep recursions on large mine arrays XXX 
      for(int i=0;i<8;i++) 
         if (m_PlayArray[pos.neighbor(i)].isCovered())
            uncover(pos.neighbor(i)); 
   }
}

/** 
 * Uncover the neighbors of a uncovered field 
 * if the bomb count of the field is equal to the flags in the neighborhood. 
 * 
 * This method implements the behaviour of a 'middle-click' on a field. 
 */
void CGameDocument::uncoverNeighborsIfSat(const CFieldPos &pos)
{
   if (!acceptsActions())
      return; 

   if (m_PlayArray[pos].isCovered())
      return; 

   CCountTrueOp<CPlayField> bombMarks(&CPlayField::isMarkedAsBomb); 
   m_PlayArray.doWithNeighborsConst(pos, bombMarks); 

   if (bombMarks.getCount() >= m_PlayArray[pos].getCount()) 
   {
      for(int i=0;i<8;i++) 
      {
         CFieldPos n(pos.neighbor(i)); 
         if (m_PlayArray[n].isCovered() && !m_PlayArray[n].isMarkedAsBomb())
            uncover(n); 
      }
   }
}

/** 
 * Toggle the flag state. 
 * 
 * This method implements the behaviour of a right-click on a field. 
 */ 
void CGameDocument::toggleMarker(const CFieldPos &p)
{
   if (!acceptsActions())
      return; 

   m_PlayArray[p].toggleMarker(m_bWithQMMarkers);   
}

/** 
 * Set the new game state (won, lost, ...) 
 */ 
void CGameDocument::setPlayState(PlayState nPlayState)
{
   PlayState nOldPlayState = m_nPlayState; 

   if (nPlayState == PLAY_RUNNING && nOldPlayState != PLAY_RUNNING) 
      m_timer.startClock();       

   if (nPlayState != PLAY_RUNNING && nOldPlayState == PLAY_RUNNING) 
      m_timer.stopClock();            

   if (nPlayState == PLAY_BEFORE_START) 
      m_timer.reset(); 

   m_nPlayState = nPlayState; 
}

class CPlayStateStringMap : public Storage::CEnumStringMap 
{
public: 
   CPlayStateStringMap(CGameDocument::PlayState &playState) : 
          Storage::CEnumStringMap(reinterpret_cast<AnyEnum*>(&playState)) {}
private: 
   static Map m_map[]; 
   void getMap(Map **pMap, int *pnEntries); 
}; 

Storage::CEnumStringMap::Map CPlayStateStringMap::m_map[] = {
   {(AnyEnum)CGameDocument::PLAY_BEFORE_START, "before-start"}, 
   {(AnyEnum)CGameDocument::PLAY_RUNNING,      "running"}, 
   {(AnyEnum)CGameDocument::PLAY_WON,          "won"}, 
   {(AnyEnum)CGameDocument::PLAY_LOST,         "lost"}
}; 

void CPlayStateStringMap::getMap(Map **pMap, int *pnEntries) {
   *pMap = m_map; 
   *pnEntries = sizeof(m_map)/sizeof(Map); 
}

void CGameDocument::transferData(Storage::CSection section)
{
   CPlayStateStringMap playstateRef(m_nPlayState); 
   section.transferItem("play-state").transferConv(playstateRef); 
   section.transferItem("questionmark-markers").transfer(m_bWithQMMarkers); 

   Storage::CSection playArraySection; 
   if (section.transferSection("play-array", playArraySection)) 
   {
      m_PlayArray.transferData(playArraySection); 
   }
}
