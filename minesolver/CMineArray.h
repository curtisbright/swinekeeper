// file      : CMineArray.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CMINEARRAY_H_INCLUDED
#define CMINEARRAY_H_INCLUDED

#include "CFieldValue.h"
#include <minebase/MineBase.h> 

#include <deque>

/** 
 * A class that represents a a minesweeper array.
 *  
 * It is only used by algorithms to solve minesweeper fields
 * (i.e. to determine which fields can be uncovered). 
 * 
 * A instance of this class holds a @ref CFieldValue for each 
 * field of the array, and a list of 'active' fields (m_activeSubset). 
 * These are the fields the algorithms is currenly reasoning about. 
 * 
 * Note: In the doku, I use sometimes the term 'resolution graph'.  
 *       This graph has fields as vertices and neighbored field pairs
 *       as edges. A field pair is a edge of this graph iff
 *       - both fields a 8-way neighbored 
 *       - one field is a uncovered field (that always has a bomb count),
 *       - and the other field is a covered, unresolved field. 
 *       In other words, a field pair is a edge if one field of it 
 *       helps to resolve the value of the other. 
 *       @see  CFieldValue::isFromUnsolvedGraphEdge, @see CFieldValue::isGraphEdge. 
 *       
 */ 
class CMineArray : public CMineArrayBase<CFieldValue> {
public:

   CMineArray();

   void makePlayField(int nMineCount); 

   void print(); 
   void printWithMargin(); 
   void printActiveSet(); 

   bool executeUncover(const CFieldPos &p); 

   void convertToSolveField(); 

   void computeGlobalActiveSubset(); 
   bool isGraphVertex(const CFieldPos &p); 
   bool resolveActiveSubset(); 

   void clearFieldMarker(); 

   void makeSubSetField(std::deque<CFieldPos> &subset); 

   bool isResolveableField(const CFieldPos &p); 
   bool findResolveableField(CFieldPos &p); 

   bool getConnectedComponent(CMineArray &subArray);  
   void insertSolution(CMineArray &subField);
   void splitField(CMineArray &field0, CMineArray &field1); 
   void mergeArray(CMineArray &field0, bool bValid0, CMineArray &field1, bool bValid1);
   bool isValidSolutionOf(CMineArray &origField); 
   bool uncoverIfResolved(CMineArray &solution); 

   int uncoveredBombCount(); 
   int resolvedBombCount(); 
   int coveredNonActiveCells(); 
   int unresolvedNonActiveCells(); 
   
   bool isValidArray(); 
   
   int m_nDepth, m_nSolutions, m_nTestedArrays; 

   void getResolvedFields(std::deque<CFieldPos> &resolvedFields); 

   const std::deque<CFieldPos>& activeSubSet() const {
      return m_activeSubset; 
   }

   void toInt(char *pzStr, int nIdx); 

private: 

   std::deque<CFieldPos> m_activeSubset; 

   template<typename OP> void doWithActiveSubset(OP& op)
   {
      for(deque<CFieldPos>::iterator iter = m_activeSubset.begin(); 
          iter != m_activeSubset.end(); 
          iter++) 
      {
         op(fieldValue(*iter)); 
      }
   }
   template<typename OP> void doWithActiveSubsetConst(OP& op) const 
   {
      for(deque<CFieldPos>::const_iterator iter = m_activeSubset.begin(); 
          iter != m_activeSubset.end(); 
          iter++) 
      {
         op(fieldValue(*iter)); 
      }
   }

   void mergeField(const CFieldPos &p, CMineArray &a0,  bool bValid0, CMineArray &a1, bool bValid1); 
}; 







#endif 
