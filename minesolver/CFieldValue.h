// file      : CFieldValue.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CFIELDVALUE_H_INCLUDED
#define CFIELDVALUE_H_INCLUDED

#include <cassert>

/** 
 * The contens of a field in @ref CMineArray. 
 *
 * It has methods and members that are necessary to resolve a array. 
 * 
 * Note: This class actually has two states: 
 *       - It can be a 'playCell', i.e. a cell that contains 
 *       also information for covered fields. (@ref CFieldValue::isValidPlayCell) 
 *       - It can be a 'solveCell', i.e. a cell in which the information
 *       under covered cells has been removed, and which has 
 *       additional states for the resolution algorithm. (@ref CFieldValue::isValidSolveCell).
 *       PlayCells were actually only useful during the initial development, 
 *       now it is better to use the class @ref CPlayField instead. 
 */ 
class CFieldValue {
public: 
   enum FieldState {
      // play field states 
      BEGIN_NOBOMB_COUNT = 0, 
      END_NOBOMB_COUNT = 9,
      BOMB = 9, 
      // solve field states 
      SOLVE_UNKNOWN = 10,         // nothing known about this covered field   
      SOLVE_UNRESOLVEABLE = 11,   // it is definitly not possible to determine if this field is a bomb 
      SOLVE_NOBOMB = 12,          // this covered field has been resolved as no-bomb  
      SOLVE_BOMB = 13,            // this covered field has been resolved as bomb 
      END_VALUES = 14
   }; 
   
   CFieldValue() : m_nFieldValue(BEGIN_NOBOMB_COUNT), m_bIsCovered(false), m_bIsMargin(false), m_bIsMarked(false) {}
   CFieldValue(FieldState nState) : m_nFieldValue(nState), m_bIsCovered(false), m_bIsMargin(false), m_bIsMarked(false)   {} 
   
   bool isCovered() const {return m_bIsCovered;}
   bool isPlayCell() const {return m_nFieldValue >= BEGIN_NOBOMB_COUNT && m_nFieldValue <= BOMB;}
   
   bool isSolveSubjectCell() const {return m_nFieldValue >= SOLVE_UNKNOWN && m_nFieldValue <= SOLVE_BOMB;}

   bool isValidPlayCell() const {
      assert(m_nFieldValue >= 0 && m_nFieldValue < END_VALUES); 
      return isPlayCell(); 
   }
   
   bool isValidSolveCell() const {
      assert(m_nFieldValue >= 0 && m_nFieldValue < END_VALUES); 
      return (isCovered() && isSolveSubjectCell()) || (!isCovered() && isPlayCell());
   }       
        
   void makeBomb() {
      m_nFieldValue = BOMB; 
   }
   void setCount(int nCount) {
      assert(nCount >= BEGIN_NOBOMB_COUNT && nCount < END_NOBOMB_COUNT); 
      assert(m_nFieldValue == 0); 
      m_nFieldValue = nCount; 
   }
   void setMargin(bool bIsMargin) {
      assert(m_nFieldValue == BEGIN_NOBOMB_COUNT && !isCovered()); 
      m_bIsMargin = bIsMargin; 
   }     
   bool isMargin() const {
      return m_bIsMargin; 
   }
   void cover() {
      m_bIsCovered = true; 
   }
   void uncover() {
      m_bIsCovered = false; 
   }
   
   /** 
    * Convert a play cell to a solve cell
    */ 
   void makeSolveCell() {
      if (isCovered()) 
         m_nFieldValue = SOLVE_UNKNOWN; 
      if (isMargin()) 
         m_nFieldValue = SOLVE_NOBOMB; 
   }

   void makeSolveCovered()
   {
      m_nFieldValue = SOLVE_UNKNOWN; 
      m_bIsCovered = true;       
      m_bIsMargin = false; 
      m_bIsMarked = false; 
   }
   void makeSolveMargin() 
   {
      m_nFieldValue = SOLVE_NOBOMB; 
      m_bIsCovered = true;       
      m_bIsMargin = true; 
      m_bIsMarked = false; 
   }
   void makeSolveCount(int nCount) 
   {
      assert(nCount >= 0 && nCount <= 8); 
      m_nFieldValue = nCount; 
      m_bIsCovered = false;       
      m_bIsMargin = false; 
      m_bIsMarked = false; 
   }


   void setResolvedAs(bool bIsBomb) {
      //assert(m_nFieldValue == SOLVE_UNKNOWN); 
      m_nFieldValue = (bIsBomb ? SOLVE_BOMB : SOLVE_NOBOMB); 
   }
   void setAsUnresolveable() {
      //assert(m_nFieldValue == SOLVE_UNKNOWN); 
      m_nFieldValue = SOLVE_UNRESOLVEABLE; 
   }

   bool isBombOracle() const {
      assert(!isSolveSubjectCell()); 
      return m_nFieldValue==BOMB; 
   }
   int getCountOracle() const {
      assert(!isSolveSubjectCell() && !isBombOracle()); 
      return m_nFieldValue; 
   } 

   // queries for solution 
   bool isKnownCount() const {
      assert(isValidSolveCell()); 
      return !isCovered() && !isBombOracle();
   }
   int getCount() const {
      assert(!isCovered() && !isBombOracle()); 
      return getCountOracle(); 
   }
   bool isKnownBomb() const {
      assert(isValidSolveCell()); 
      return !isCovered() && isBombOracle() || m_nFieldValue==SOLVE_BOMB; 
   }
   bool isKnownNoBomb() const {
      assert(isValidSolveCell()); 
      return !isCovered() && !isBombOracle() || m_nFieldValue==SOLVE_NOBOMB; 
   }
   bool isUndecideable() const {
      assert(isValidSolveCell()); 
      return m_nFieldValue==SOLVE_UNRESOLVEABLE; 
   }
   void copySolution(CFieldValue nV) {
      assert(nV.isResolved()); 
      assert(!isCovered() || !isResolved()); 
      m_nFieldValue = nV.m_nFieldValue; 
   }

   bool isResolved() const {
      return isKnownBomb() || isKnownNoBomb() || isUndecideable(); 
   }
   bool isUnresolved() const {
      return !isResolved();
   }

   bool isBombStateKnown() const {
      return isKnownBomb() || isKnownNoBomb(); 
   }
      
   /**
    * Determine if the directed edge (*this, nV) is a edge of the resolution graph
    * and that it emerges from an unsolved field 
    */  
   bool isFromUnsolvedGraphEdge(CFieldValue nV) const {
      return nV.isKnownCount() && !isResolved(); 
   }

   /** 
    * Determine if (*this, nV) is a edge of the resolution graph
    * 
    * @see CMineArray
    */ 
   bool isGraphEdge(CFieldValue nV) const {
      return isFromUnsolvedGraphEdge(nV) || nV.isFromUnsolvedGraphEdge(*this); 
   }

   bool isValidSolutionOf(CFieldValue nV) const; 

   void setMarkedFlag(bool bIsMarked) {m_bIsMarked = bIsMarked;}
   bool isMarked() const {return m_bIsMarked;}


   bool uncoverIfResolved(CFieldValue nRes);  
   CFieldValue mergedWith(CFieldValue nV) const; 
   int toInt(); 
   int toSolveInt(); 

   bool isUncoveredBomb() const {return !isCovered() && isBombOracle();}

private: 

   int m_nFieldValue; 
   bool m_bIsCovered; 
   bool m_bIsMargin; 
   bool m_bIsMarked; 
}; 

#endif 
