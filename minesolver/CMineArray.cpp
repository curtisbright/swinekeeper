// file      : CMineArray.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CMineArray.h" 

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <cassert>

using namespace std; 

CMineArray::CMineArray() {}

/** 
 * Query the list of resolved fields. 
 * 
 * Returns a list of all covered fields in the active subset 
 * the values of which already have been resolved.
 * (i.e. it is known if there's a bomb under it or not) 
 * 
 * @param resolvedFields : List of resolved active fields 
 */ 
void  CMineArray::getResolvedFields(deque<CFieldPos> &resolvedFields)
{
   resolvedFields.clear(); 
   for(deque<CFieldPos>::iterator iter = m_activeSubset.begin(); 
       iter != m_activeSubset.end(); 
       iter++) 
   {
      if (fieldValue(*iter).isResolved() && fieldValue(*iter).isCovered()) 
         resolvedFields.push_back(*iter); 
   }
}

/** 
 * Returns the count of known bombs in the field. 
 * 
 * (poor name since bombs are never uncovered) 
 * 
 * @return Count of known bombs 
 */ 
int CMineArray::uncoveredBombCount()
{
   CCountTrueOp<CFieldValue> uncoveredBombCounter(&CFieldValue::isUncoveredBomb); 
   doWithArrayConst(uncoveredBombCounter); 
   return uncoveredBombCounter.getCount(); 
}

int CMineArray::resolvedBombCount()
{
   CCountTrueOp<CFieldValue> knownBombCounter(&CFieldValue::isKnownBomb); 
   doWithArrayConst(knownBombCounter); 
   return knownBombCounter.getCount(); 
}


/**   
 * Returns the count of covered cells which are not active 
 *
 * @return Count of non-active covered cells 
 */ 
int CMineArray::coveredNonActiveCells() 
{
   CCountTrueOp<CFieldValue> coveredCells(&CFieldValue::isCovered); 
   doWithArrayConst(coveredCells); 
   CCountTrueOp<CFieldValue> coveredActiveCells(&CFieldValue::isCovered); 
   doWithActiveSubsetConst(coveredActiveCells); 
   return coveredCells.getCount() - coveredActiveCells.getCount(); 
}

int CMineArray::unresolvedNonActiveCells()
{
   CCountTrueOp<CFieldValue> unresolvedCells(&CFieldValue::isUnresolved); 
   doWithArrayConst(unresolvedCells); 
   CCountTrueOp<CFieldValue> unresolvedActiveCells(&CFieldValue::isUnresolved); 
   doWithActiveSubsetConst(unresolvedActiveCells); 
   return unresolvedCells.getCount() - unresolvedActiveCells.getCount(); 
}

class CGetBombCountRangeOp {
public: 
   CGetBombCountRangeOp() : m_nMinBombs(0), m_nMaxBombs(0) {}
   void operator()(CFieldValue &value) {
      if (value.isKnownBomb()) 
      {
         m_nMinBombs++; 
         m_nMaxBombs++; 
      }
      else if (!value.isKnownNoBomb()) 
      {
         m_nMaxBombs++; 
      }
   }
   bool isValidBombCount(int nBombCount) {
      return nBombCount >= m_nMinBombs && nBombCount <= m_nMaxBombs; 
   }
private: 
   int m_nMinBombs;  
   int m_nMaxBombs;      
}; 


bool CMineArray::isValidArray()  
{
   for(CRangeIterator iter(range()); iter.isValid(); iter++) 
   {
      if (!fieldValue(iter.curPos()).isCovered()) 
      {
         CGetBombCountRangeOp bombRangeOp; 
         CFieldPos pos(iter.curPos());
         doWithNeighbors(pos, bombRangeOp); 
         if (!bombRangeOp.isValidBombCount(fieldValue(iter.curPos()).getCount()))
            return false; 
      }       
   }
   return true; 
}



/** 
 * Create a game field. 
 * 
 * After calling this method, the class represents 
 * a game field that contains 'nMineCount' mines. 
 * All fields are covered. 
 * 
 * Note: Resize the field before calling this method
 *
 * @param nMineCount Number of mines in the field. 
 */ 
void CMineArray::makePlayField(int nMineCount) 
{
   // initialize all fields to be uncovered, no bombs 
   CFieldValue initVal; 
   CSetValueOp<CFieldValue> setInitValueOp(initVal); 
   doWithArray(setInitValueOp); 

   // mark the margin fields (i.e. the fields that are beside the array) 
   CMethodOp1<CFieldValue, bool> setMarginOp(&CFieldValue::setMargin, true); 
   doWithArrayAndMargin(setMarginOp); 
   CMethodOp1<CFieldValue, bool> setInteriorOp(&CFieldValue::setMargin, false); 
   doWithArray(setInteriorOp); 

   // drop bombs on the array 
   assert(nMineCount < getArrayFieldsCount()); 
   while(nMineCount > 0) {
      CFieldPos fp(range().rand()); 
      if (!fieldValue(fp).isBombOracle()) 
      {
         fieldValue(fp).makeBomb(); 
         nMineCount--; 
      }  
   }

   // compute the count of neighboring bombs for each field 
   for(CRangeIterator iter(range()); iter.isValid(); iter++) 
   {
      if (!fieldValue(iter.curPos()).isBombOracle()) 
      {
         CCountTrueOp<CFieldValue> bombSum(&CFieldValue::isBombOracle); 
         CFieldPos pos(iter.curPos());
         doWithNeighborsConst(pos, bombSum); 
         fieldValue(iter.curPos()).setCount(bombSum.getCount());
      }       
   }

   // cover all fields 
   CMethodOp0<CFieldValue> coverFieldsOp(&CFieldValue::cover); 
   doWithArrayAndMargin(coverFieldsOp); 
}

/** 
 * Create a 'solve field' from a 'play field'. 
 * 
 * Call this method before invoking the resolution algorithm.
 */ 
void CMineArray::convertToSolveField()
{
   // remove the information wether a covered field contains a bomb or not 
   CMethodOp0<CFieldValue> makeSolveCellsOp(&CFieldValue::makeSolveCell); 
   doWithArrayAndMargin(makeSolveCellsOp); 
   // compute the initial 'active subset' 
   computeGlobalActiveSubset(); 
}

/** 
 * Clear all markers. 
 */ 
void CMineArray::clearFieldMarker()
{
   CMethodOp1<CFieldValue, bool> clearMarkersOp(&CFieldValue::setMarkedFlag, false); 
   doWithArrayAndMargin(clearMarkersOp); 
}


/** 
 * Determine if field p is a vertex of the 'resolution graph' 
 * 
 * see @ref CFieldValue. 
 * 
 */ 
bool CMineArray::isGraphVertex(const CFieldPos &p) 
{
   CFieldValue nCenterValue(fieldValue(p)); 
   for(int i=0;i<8;i++) 
   {
      if (nCenterValue.isGraphEdge(fieldValue(p.neighbor(i))))
         return true; 
   }
   return false; 
}

/** 
 * Conpute the initial 'active subset'.
 * 
 * The initial active subset contains all fields that could 
 * help the algorithm to find a solution. 
 * These are all fields that are vertices in the 'resolution graph'. 
 * 
 */ 
void CMineArray::computeGlobalActiveSubset() 
{
   m_activeSubset.resize(0); 
   for(CRangeIterator iter(range()); iter.isValid(); iter++) 
   {
      if (isGraphVertex(iter.curPos()) 
          // new 
          || fieldValue(iter.curPos()).isKnownBomb()
         ) 
      {
         m_activeSubset.push_back(iter.curPos()); 
      }
   }
}

/** 
 * Determines if there's a chance to determine the value of field p.
 * 
 * This algorithm can only determine the value of covered
 * fields that are part of the resolution graph. 
 */ 
bool CMineArray::isResolveableField(const CFieldPos &p) 
{
   CFieldValue nCenterValue(fieldValue(p)); 
   if (fieldValue(p).isMarked()) 
      return false; 
   for(int i=0;i<8;i++) 
   {
      if (nCenterValue.isFromUnsolvedGraphEdge(fieldValue(p.neighbor(i))))
         return true; 
   }
   return false; 
}

/** 
 * Tries to find a resolveable field in the active subset. 
 * 
 * @return true iff a resolveable field was found. 
 * @param p If the function returns true, p contains the resolveable field. 
 */ 
bool CMineArray::findResolveableField(CFieldPos &p)
{
   for(deque<CFieldPos>::iterator iter = m_activeSubset.begin(); 
       iter != m_activeSubset.end(); 
       iter++) 
   {
      if (isResolveableField(*iter))
      {
         p = *iter; 
         return true; 
      }
   }
   return false; 
}

/** 
 * Extracts a mine array with a restricted active subset from *this. 
 * 
 * This method returns a mine array that represents the same 
 * array as *this, but the active subset of which contains 
 * only fields from a single connected component of the resolution 
 * graph. 
 * Note that it uses the 'isMarked' method if CFieldPos to determine 
 * which fields have already been processed. 
 * 
 * @return true, iff a connected component was found 
 * @param subArray If the function returned true, this parameter 
 *                 contains the subarray.            
 */ 
bool CMineArray::getConnectedComponent(CMineArray &subArray) 
{
   CFieldPos p; 
   if (!findResolveableField(p)) 
      return false; 

   deque<CFieldPos> depthSearchStack; 
   deque<CFieldPos> subFieldSet;

   depthSearchStack.push_back(p); 

   while (!depthSearchStack.empty()) 
   {
      CFieldPos curPos = depthSearchStack.back(); 

      depthSearchStack.pop_back(); 
      if (fieldValue(curPos).isMarked()) 
         continue; 

      subFieldSet.push_back(curPos); 
      fieldValue(curPos).setMarkedFlag(true); 

      for(int i=0;i<8;i++) 
      {
         if (fieldValue(curPos).isGraphEdge(fieldValue(curPos.neighbor(i)))) 
         {
            depthSearchStack.push_back(curPos.neighbor(i)); 
         }
      }
   }
   
   subArray = *this; 
   subArray.m_activeSubset = subFieldSet; 

   return true; 
}

/** 
 * Insert a resolved subgraph into *this.
 * 
 * 'subField' must be a array the active subset of which has 
 * already been resolved. 
 * This function inserts the solved of 'subField' fields into *this. 
 */ 
void CMineArray::insertSolution(CMineArray &subField)
{
   for(deque<CFieldPos>::iterator iter = subField.m_activeSubset.begin(); 
       iter != subField.m_activeSubset.end(); 
       iter++) 
   {
      assert(subField.fieldValue(*iter).isResolved()); 
      assert(!fieldValue(*iter).isCovered() || !fieldValue(*iter).isResolved()); 
      fieldValue(*iter).copySolution(subField.fieldValue(*iter)); 
   }
}


/** 
 * Guesses the value of a covered field. 
 *
 * This function selects a single unresolved field from the 
 * array. It then creates two mine arrays. 
 * In one, this field is marked as a bomb, in the other it 
 * is marked as a no-bomb. 
 * It is the job of the caller to determine if these
 * guesses are right or not. 
 */ 
void CMineArray::splitField(CMineArray &field0, CMineArray &field1) 
{
   field0 = *this; 
   field1 = *this;

   int nMidIdx = m_activeSubset.size()/2; 
   int nSplitIdx = -1; 
   for (int i=0;i<nMidIdx+1;i++) 
   {
      int nTmpIdx = nMidIdx-i; 
      if (   nTmpIdx >= 0 
          && fieldValue(m_activeSubset[nTmpIdx]).isCovered()
          && !fieldValue(m_activeSubset[nTmpIdx]).isResolved())
      {
         nSplitIdx = nTmpIdx; 
         break; 
      }
      nTmpIdx = nMidIdx+i; 
      if (nTmpIdx < int(m_activeSubset.size()) 
          && fieldValue(m_activeSubset[nTmpIdx]).isCovered()
          && !fieldValue(m_activeSubset[nTmpIdx]).isResolved())
      {
         nSplitIdx = nTmpIdx; 
         break; 
      }
   }
   assert(nSplitIdx != -1);        
   CFieldPos fp(m_activeSubset[nSplitIdx]); 

   assert(fieldValue(fp).isCovered() && !fieldValue(fp).isResolved()); 

   field0.fieldValue(fp).setResolvedAs(false);
   field1.fieldValue(fp).setResolvedAs(true);
}

/** 
 * Merge a field of two 'guesses' to a single field.
 * 
 * @see CMineArray::mergeArray
 */
void CMineArray::mergeField(
   const CFieldPos &p, 
   CMineArray &a0, bool bValid0, 
   CMineArray &a1, bool bValid1)
{
   if (!bValid0) {
      fieldValue(p) = a1.fieldValue(p); 
   }
   else if (!bValid1) {
      fieldValue(p) = a0.fieldValue(p); 
   }
   else {   
      fieldValue(p) = a0.fieldValue(p).mergedWith(a1.fieldValue(p));
   }
}

/** 
 * Merges two 'guessed' array to a single array.
 * 
 * This function takes two solved arrays which have been created using 
 * ref @CMineArray::splitField. It merges these arrays to a single array (*this)
 * using the rules defined in @CFieldValue::mergeWith. 
 *
 * @param bValid0: true iff field0 contains a valid solution 
 * @param bValid1: true iff field1 contains a valid solution 
 */  
void CMineArray::mergeArray(CMineArray &field0, bool bValid0, CMineArray &field1, bool bValid1)
{
   assert(bValid0 || bValid1); 
   for(deque<CFieldPos>::iterator iter = m_activeSubset.begin(); 
       iter != m_activeSubset.end(); 
       iter++) 
   {
      CFieldValue fp = fieldValue(*iter); 
      assert(!fp.isCovered() || !fp.isResolved()); 
      mergeField(*iter, field0, bValid0, field1, bValid1); 
   }
}

/** 
 * Function object that counts the unresolved fields and the known bombs 
 */ 
class CSumFieldTypesOp {
public: 
   CSumFieldTypesOp() : m_nKnownBombCount(0), m_nUnresolvedFieldCount(0) {}
   void operator()(CFieldValue &value) {
      if (value.isKnownBomb()) 
         m_nKnownBombCount++; 
      if (!value.isKnownNoBomb() && !value.isKnownBomb()) 
         m_nUnresolvedFieldCount++; 
   }
   int getKnownBombCount() {return m_nKnownBombCount;}
   int getUnresolvedFieldCount() {return m_nUnresolvedFieldCount;}

private: 
   int m_nKnownBombCount;  
   int m_nUnresolvedFieldCount;      
}; 

/** 
 * Function object that marks covered and unresolved fields
 * as bomb/noBomb.
 */ 
class CResolveOp {
public: 
   CResolveOp(bool bUnresolvedFieldsAreBombs) : 
      m_bUnresolvedFieldsAreBombs(bUnresolvedFieldsAreBombs), 
      m_bHasChanged(false) 
   {}
   void operator()(CFieldValue &value) {
      if (!value.isResolved())
      {
         value.setResolvedAs(m_bUnresolvedFieldsAreBombs); 
         m_bHasChanged = true; 
      }  
   }
   bool hasChanged() {return m_bHasChanged;}
private: 
   bool m_bUnresolvedFieldsAreBombs; 
   bool m_bHasChanged; 
}; 

/** 
 * Use a simple heuristic to resolve the 'easy' fields in the active subset.
 * 
 * This function uses a simple 'local' heuristic to find 
 * bombs/noBombs under the active fields. 
 * It marks these fields as resolved. 
 * 
 * @return false, iff the mine array is invalid, i.e. it has 
 *          no solution at all. (This happens if a guess (see above) was wrong) 
 */ 
bool CMineArray::resolveActiveSubset()
{
   bool bChanged(false); 

   do {
      bChanged = false; 
      for(deque<CFieldPos>::iterator iter = m_activeSubset.begin(); 
          iter != m_activeSubset.end(); 
          iter++) 
      {
         if (fieldValue(*iter).isKnownCount()) {
            CSumFieldTypesOp fieldSums; 
            doWithNeighbors(*iter, fieldSums); 
            int nCount = fieldValue(*iter).getCount(); 
            if (nCount == fieldSums.getKnownBombCount()) 
            {
               CResolveOp resolveNoBomb(false); 
               doWithNeighbors(*iter, resolveNoBomb); 
               bChanged |= resolveNoBomb.hasChanged(); 
            }
            if (fieldSums.getKnownBombCount() == nCount-fieldSums.getUnresolvedFieldCount()) 
            {
               CResolveOp resolveBomb(true); 
               doWithNeighbors(*iter, resolveBomb); 
               bChanged |= resolveBomb.hasChanged(); 
            }
            if (   fieldSums.getKnownBombCount() > nCount 
                || fieldSums.getKnownBombCount() < nCount - fieldSums.getUnresolvedFieldCount()) 
            {
               return false; 
            }         
         } // if (value.isKnownCount()) 
      }
   } while (bChanged); 
   return true; 
}

/** 
 * Testing method that determines if *this is a valid solution of origField.
 * 
 * Used to test if this algorithm works correctly. 
 * *this must be a solved field, origField must be the 'source field'. 
 * This function determines if the resolved fields actually have 
 * the same value in both arrays. 
 */ 
bool CMineArray::isValidSolutionOf(CMineArray &origField) 
{
   bool bAllFieldsOK = true; 
   for(CRangeIterator iter(range()); iter.isValid(); iter++) 
   {
      bAllFieldsOK &= fieldValue(iter.curPos()).isValidSolutionOf(origField.fieldValue(iter.curPos())); 
   }
   return bAllFieldsOK; 
}

/** 
 * Uncovers the fields of *this which have been resolved in 'solution'. 
 */ 
bool CMineArray::uncoverIfResolved(CMineArray &solution) 
{
   bool bSomethingUncovered = false; 
   for(CRangeIterator iter(range()); iter.isValid(); iter++) 
   {
      bSomethingUncovered |= fieldValue(iter.curPos()).uncoverIfResolved(solution.fieldValue(iter.curPos())); 
   }
   return bSomethingUncovered; 
}

/** 
 * Sets the active subset. 
 */ 
void CMineArray::makeSubSetField(deque<CFieldPos> &subset)
{
   m_activeSubset = subset; 
}

/** 
 * Printing for debugging purposes 
 */ 
void CMineArray::print()
{
   const CFieldRange &r = range(); 

   int nX, nY; 
   for(nY = r.beginY(); nY < r.endY(); nY++) 
   {
      for(nX = r.beginX(); nX < r.endX(); nX++) 
      {
         CFieldValue fp(fieldValue(CFieldPos(nX, nY))); 
         if (false) 
         {

         }
         else if (fp.isCovered())
         {
            cout << "="; 
         }
         else if (fp.isBombOracle()) 
         {
            cout << "*"; 
         }
         else 
         {
            cout << fp.getCountOracle();
         }
      }
      if (1) {
      cout << "    "; 
      for(nX = r.beginX(); nX < r.endX(); nX++) 
      {
         CFieldValue fp(fieldValue(CFieldPos(nX, nY))); 
         ios::fmtflags oldFlags = cout.flags(); 
         cout << " "<< std::hex << std::setw(2) << std::setfill('0')  << fp.toInt();
         cout.flags(oldFlags); 
      }
      }
      cout << "\n"; 
   }
   cout << "\n";
}

/** 
 * Printing for debugging purposes 
 */ 
void CMineArray::printWithMargin()
{
   const CFieldRange &r = range(); 
   int nX, nY; 
   for(nY = r.beginY()-1; nY < r.endY()+1; nY++) 
   {
      for(nX = r.beginX()-1; nX < r.endX()+1; nX++) 
      {
         CFieldValue fp(fieldValue(CFieldPos(nX, nY))); 
         if (false) 
         {

         }
         else if (fp.isCovered())
         {
            cout << "="; 
         }
         else if (fp.isBombOracle()) 
         {
            cout << "*"; 
         }
         else 
         {
            cout << fp.getCountOracle();
         }
      }
      cout << "    "; 
      for(nX = r.beginX()-1; nX < r.endX()+1; nX++) 
      {
         CFieldValue fp(fieldValue(CFieldPos(nX, nY))); 
         ios::fmtflags oldFlags = cout.flags(); 
         assert(fp.toInt() < 256); 
         cout << " "<< std::hex << std::setw(2) << std::setfill('0')  << fp.toInt();
         cout.flags(oldFlags); 
      }
      cout << "\n"; 
   }
   cout << "\n";
   printActiveSet(); 
}

/** 
 * Printing for debugging purposes 
 */ 
void CMineArray::printActiveSet() 
{
   for(deque<CFieldPos>::iterator iter = m_activeSubset.begin(); 
       iter != m_activeSubset.end(); 
       iter++) 
   {
      iter->print(); 
   }
   cout << "\n"; 
}

/** 
 * Uncovers a single field. 
 * 
 * If the field has bomb-count 0, it uncovers the neighbors too. 
 */ 
bool CMineArray::executeUncover(const CFieldPos &p)
{
   CFieldValue &nValue = fieldValue(p);
    
   nValue.uncover(); 

   if (nValue.isBombOracle()) 
      return false; 
      
   if (nValue.getCountOracle() == 0) 
   {
      for(int i=0;i<8;i++) 
      {
         CFieldPos neighbor(p.neighbor(i)); 
         if (range().inRange(neighbor) && fieldValue(neighbor).isCovered())
            executeUncover(neighbor); 
      } 
   }
   return true;       
}

void CMineArray::toInt(char *pStr, int nMaxIdx)
{
   int nIdx=0; 
   assert(range().getFieldCount() < nMaxIdx*2); 
   for(CRangeIterator iter(range()); iter.isValid(); iter++) 
   {
      int nVal = fieldValue(iter.curPos()).toSolveInt(); 
      if (!(nIdx & 1)) 
         pStr[nIdx/2] = nVal; 
      else 
         pStr[nIdx/2] |= (nVal<<4); 
      nIdx++; 
   }
}

