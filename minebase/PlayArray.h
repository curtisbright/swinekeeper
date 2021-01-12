// file      : PlayArray.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef PLAYARRAY_H_INCLUDED
#define PLAYARRAY_H_INCLUDED

#include <cassert>
#include <minebase/MineBase.h>
#include <string>

namespace Storage {
   class CSection; 
}

/** 
 * Field for CPlayArray
 * 
 * @see CPlayArray
 */ 
class CPlayField {
public: 

   enum MarkedState {
      MARKED_BEGIN=0, 
      MARKED_NONE=0, 
      MARKED_BOMB, 
      MARKED_QUESTIONMARK, 
      MARKED_END
   }; 

   CPlayField() : 
      m_bIsBomb(false),
      m_nNeighboredBombCount(0),  
      m_bCovered(false), 
      m_nMarked(MARKED_NONE)
   {}
   void cover() {m_bCovered = true;}
   void uncover() {m_bCovered = false; m_nMarked = MARKED_NONE;}
   bool isCovered() const {return m_bCovered;}
   void makeBomb() {m_bIsBomb = true;}
   bool isBomb() const {return m_bIsBomb;}

   void toggleMarker(bool bWithQuestionMark = false); 
   void setMarkedAsBomb() {m_nMarked = MARKED_BOMB;}

   bool isMarkedAsBomb() const {return isCovered() && (m_nMarked==MARKED_BOMB);}
   bool isMarkedAsQuestionMark() const {return isCovered() && (m_nMarked==MARKED_QUESTIONMARK);}

   void setCount(int nCount) {
      assert(!isBomb());
      assert(nCount >= 0 && nCount <= 8); 
      m_nNeighboredBombCount = nCount; 
   }
   /** 
    * Returns the neighbored bombs. 
    *
    * Note that you have to call setCount() before using this method. 
    * The constructor does not initialize m_nNeighboredBombCount to a
    * valid value. (perhaps design error, but its easier to do it this way) 
    */ 
   int getCount() const {
      assert(!isBomb());
      assert(m_nNeighboredBombCount >= 0 && m_nNeighboredBombCount <= 8); 
      return m_nNeighboredBombCount; 
   }

   bool operator==(const CPlayField &f) const {
      return m_bIsBomb == f.m_bIsBomb
          && m_nNeighboredBombCount == f.m_nNeighboredBombCount 
          && m_bCovered == f.m_bCovered 
          && m_nMarked == f.m_nMarked; 
   }

   bool isObjectValid() const; 
   void transferData(Storage::CSection section); 

   std::string toString() const; 
   bool fromString(const std::string& str); 
   static int getToStringLength(); 

   static bool isCoverStateEqual(const CPlayField &f1, const CPlayField& f2) {
      return f1.isCovered() == f2.isCovered();
   }

private: 
   bool m_bIsBomb; 
   int m_nNeighboredBombCount; 
   bool m_bCovered; 
   MarkedState m_nMarked;  
   
}; 

/** 
 * Mine array that is customized for usage in game play 
 * (i.e. not for resolution algos)
 */ 
class CPlayArray : public CMineArrayBase<CPlayField> {
public: 
   CPlayArray() : m_nBombs(0) {}
   void makePlayField(int nSizeX, int nSizeY, int nBombs); 
   
   void initPlayField(int nSizeX, int nSizeY, int nBombs); 
   void dropBombs(const CFieldPos &NoBombHere); 

   int getBombFlagCount() const; 
   int getCoveredFieldCount() const; 
   int getBombCount() const {return m_nBombs;}

   void transferData(Storage::CSection section); 

   bool isObjectValid() const; 

   bool isCoverStateEqual(const CPlayArray &other) const; 

   void removeBomb(const CFieldPos &pos); 

private:
   int countBombsInArray() const; 
   void computeNeighboredBombCounts(); 
   void computeDependentStates(); 

   int m_nBombs; 
}; 


#endif 
