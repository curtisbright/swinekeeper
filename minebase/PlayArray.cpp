// file      : PlayArray.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "PlayArray.h" 
#include <storage/Document.h>
#include "MineBaseSerialize.h" 

bool CPlayField::isObjectValid() const
{
   // if it is not a bomb, we need to have a valid count 
   if (!m_bIsBomb && (m_nNeighboredBombCount < 0 || m_nNeighboredBombCount >= 8)) 
      return false; 

   if (m_nMarked < MARKED_BEGIN || m_nMarked >= MARKED_END) 
      return false; 
   
   if (isCovered() && m_nMarked != MARKED_NONE) 
      return false; 

   return true; 
}


class CMarkedStateStringMap : public Storage::CEnumStringMap 
{
public: 
   CMarkedStateStringMap(CPlayField::MarkedState &markedState) : 
          Storage::CEnumStringMap(reinterpret_cast<AnyEnum*>(&markedState)) {}
private: 
   static Map m_map[]; 
   void getMap(Map **pMap, int *pnEntries); 
}; 

Storage::CEnumStringMap::Map CMarkedStateStringMap::m_map[] = {
   {(AnyEnum)CPlayField::MARKED_NONE,            "none"}, 
   {(AnyEnum)CPlayField::MARKED_BOMB,            "bomb"},  
   {(AnyEnum)CPlayField::MARKED_QUESTIONMARK,    "questionmark"}
}; 

void CMarkedStateStringMap::getMap(Map **pMap, int *pnEntries) {
   *pMap = m_map; 
   *pnEntries = sizeof(m_map)/sizeof(Map); 
}


void CPlayField::transferData(Storage::CSection section)
{
   section.transferItem("covered").transfer(m_bCovered); 
   if (m_bCovered) 
   {
      CMarkedStateStringMap markedStateRef(m_nMarked); 
      section.transferItem("marked-state").transferConv(markedStateRef); 
   }
   else 
   {
      if (section.isTransferDocToObject())
      {
         m_nMarked = MARKED_NONE; 
      }
   }

   section.transferItem("is-bomb").transfer(m_bIsBomb); 
   if (!m_bIsBomb) 
   {  
      section.transferItem("neighbor-bomb-count").transfer(m_nNeighboredBombCount); 
   }
   else 
   {
      m_nNeighboredBombCount = -1; 
   }
}

std::string CPlayField::toString() const
{
   std::string str("~~"); 

   if (isCovered()) {
      if (m_nMarked == MARKED_NONE) 
         str[0] = 'C'; 
      else if (m_nMarked == MARKED_BOMB) 
         str[0] = 'M'; 
      else if (m_nMarked == MARKED_QUESTIONMARK) 
         str[0] = '?'; 
   }
   else {
      str[0] = '.'; 
   }

   if (isBomb())
   {
      str[1] = '*';
   } 
   else 
   {
      str[1] = '_';
   }

   return str; 
}

int CPlayField::getToStringLength() 
{
   return 2; 
} 


bool CPlayField::fromString(const std::string &str )
{
   m_nNeighboredBombCount = -1; 

   if (str.length() != 2) 
      return false; 

   if (str[0] == '.') 
   {
      m_bCovered = false; 
      m_nMarked = MARKED_NONE; 
   }
   else 
   {
      m_bCovered = true; 
      if (str[0] == 'C') 
         m_nMarked = MARKED_NONE; 
      else if (str[0] == 'M') 
         m_nMarked = MARKED_BOMB; 
      else if (str[0] == '?') 
         m_nMarked = MARKED_QUESTIONMARK; 
      else 
         return false; 
   }

   if (str[1] == '*') 
   {
      m_bIsBomb = true; 
   }
   else if (str[1] == '_') 
   {
      m_bIsBomb = false; 
   }
   else 
   {
      return false; 
   }

   return true; 
}


/** 
 * Create a new mine array 
 * 
 * @param nSizeX Width of the array 
 * @param nSizeY Height of the array 
 * @param nBombs Count of bombs 
 */ 
void CPlayArray::makePlayField(int nSizeX, int nSizeY, int nBombs)
{
   initPlayField(nSizeX, nSizeY, nBombs); 
   dropBombs(CFieldPos(-1,-1)); 
}

/** 
 * Create a new array, but do not determine the positions of the 
 * bombs jet. 
 */ 
void CPlayArray::initPlayField(int nSizeX, int nSizeY, int nBombs)
{
   resize(CFieldRange(0,0, nSizeX, nSizeY)); 
   CMethodOp0<CPlayField> coverFieldsOp(&CPlayField::cover); 
   m_nBombs = nBombs; 
   doWithArray(coverFieldsOp); 
}

/** 
 * Drop the bombs. (Call after @ref CPlayArray::initPlayField). 
 * 
 * @param NoBombHere: The function never sets a bomb at this 
 *    location. Usually the first field picked, since this 
 *    field should never contain a bomb.
 */ 
void CPlayArray::dropBombs(const CFieldPos &NoBombHere)
{
   int nBombs(m_nBombs); 
   while (nBombs != 0) {
      CFieldPos pos = range().rand(); 
      if (!fieldValue(pos).isBomb() && !(pos == NoBombHere)) {
         fieldValue(pos).makeBomb();  
         nBombs--; 
      }
   }

   computeDependentStates(); 
}

void CPlayField::toggleMarker(bool bWithQuestionMark) {
   if (m_nMarked == MARKED_NONE) 
      m_nMarked = MARKED_BOMB; 
   else if (m_nMarked == MARKED_BOMB && bWithQuestionMark) 
      m_nMarked = MARKED_QUESTIONMARK; 
   else 
      m_nMarked = MARKED_NONE;    
}

int CPlayArray::getBombFlagCount() const
{
   CCountTrueOp<CPlayField> bombMarkers(&CPlayField::isMarkedAsBomb); 
   doWithArrayConst(bombMarkers); 
   return bombMarkers.getCount(); 
}

int CPlayArray::getCoveredFieldCount() const
{
   CCountTrueOp<CPlayField> coveredFields(&CPlayField::isCovered); 
   doWithArrayConst(coveredFields); 
   return coveredFields.getCount(); 
}

int CPlayArray::countBombsInArray() const
{
   CCountTrueOp<CPlayField> bombsCounter(&CPlayField::isBomb); 
   doWithArrayConst(bombsCounter); 
   return bombsCounter.getCount(); 
}

void CPlayArray::computeNeighboredBombCounts()
{
   for(CRangeIterator iter(range()); iter.isValid(); iter++) 
   {
      if (!fieldValue(iter.curPos()).isBomb()) 
      {
         CCountTrueOp<CPlayField> neighborMines(&CPlayField::isBomb); 
         doWithNeighborsConst(iter.curPos(), neighborMines); 
         fieldValue(iter.curPos()).setCount(neighborMines.getCount()); 
      }
   }
}

void CPlayArray::computeDependentStates()
{
   computeNeighboredBombCounts(); 
}

void CPlayArray::transferData(Storage::CSection section)
{
   Storage::CSection arraySection; 
   if (section.transferSection("array", arraySection)) 
   {
      if (!section.isTransferDocToObject()) 
      {
         transferDataFromObjectCompact<CPlayField>(arraySection, *this); 
      }
      else 
      {
         transferDataToObjectCompact<CPlayField>(arraySection, *this); 
      }
   }
   else 
   {
      assert(0); 
   }

   if (section.isTransferDocToObject()) 
   {
      m_nBombs = countBombsInArray();
      computeDependentStates(); 
   }
}

bool CPlayArray::isObjectValid() const
{
   if (range().sizeX() <= 3 || range().sizeY() <= 3) 
      return false; 

   // check if each field is ok 
   CCountFalseOp<CPlayField> invalidObjCounter(&CPlayField::isObjectValid); 
   doWithArrayConst(invalidObjCounter);
   if (invalidObjCounter.getCount() != 0) 
      return false; 

   // check all cached (dependent) data, if it is consistent with 
   // the state of the object  
   for(CRangeIterator iter(range()); iter.isValid(); iter++) 
   {
      if (!fieldValue(iter.curPos()).isBomb()) 
      {
         CCountTrueOp<CPlayField> neighborMines(&CPlayField::isBomb); 
         doWithNeighborsConst(iter.curPos(), neighborMines); 
         if (fieldValue(iter.curPos()).getCount() != neighborMines.getCount()) 
            return false; 
      }
   }
 
   CCountTrueOp<CPlayField> bombsCounter(&CPlayField::isBomb); 
   doWithArrayConst(bombsCounter); 
   if (bombsCounter.getCount() != m_nBombs) 
      return false; 

   return true; 
}

bool CPlayArray::isCoverStateEqual(const CPlayArray &other) const
{
   return isEqualFunc(*this, other, CPlayField::isCoverStateEqual); 

}
