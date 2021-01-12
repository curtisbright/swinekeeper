// file      : CFieldValue.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 

#include "CFieldValue.h" 

/** 
 * Determine if *this is a valid solution of nV
 */ 
bool CFieldValue::isValidSolutionOf(CFieldValue nV) const 
{
   assert(isValidSolveCell()); 
   assert(nV.isValidPlayCell()); 

   if (!isBombStateKnown()) return true; 
   return (isKnownBomb() == nV.isBombOracle()); 
}

/** 
 * Uncover *this if nRes is resolved 
 */ 
bool CFieldValue::uncoverIfResolved(CFieldValue nRes) 
{
   assert(nRes.isValidSolveCell()); 
   assert(isValidPlayCell()); 
   assert(nRes.isValidSolutionOf(*this)); 

   if (nRes.isBombStateKnown()) 
   {
      if (isCovered()) 
      {
         uncover(); 
         return true; 
      }
   }
   return false; 
}

/** 
 * Merge two fields (*this, nV) from two guesses. 
 * 
 * @see CMineArray::mergeArray
 */ 
CFieldValue CFieldValue::mergedWith(CFieldValue nV) const
{
   assert(nV.isValidSolveCell() && isValidSolveCell()); 
   assert(isCovered() == nV.isCovered()); 
   
   // if the fields are not covered, both must have the same value anyway 
   if (!isCovered() || !nV.isCovered()) 
      return *this; 

   assert(isResolved() && nV.isResolved()); 

   // if one of them is not decideable, the result is not decideable 
   if (isUndecideable() || nV.isUndecideable())
   {
      CFieldValue nRet = *this; 
      nRet.setAsUnresolveable(); 
      return nRet; 
   }
  
   // if both are resolved to the same value, return that value
   // otherwise, the field is not resolveable 
   CFieldValue nRet = *this; 
   if (nV.isKnownBomb() != isKnownBomb()) 
      nRet.setAsUnresolveable(); 
   else 
      nRet.setResolvedAs(isKnownBomb()); 
   return nRet;  
}
   
/** 
 * Convert state of *this to int, only for debugging. 
 */ 
int CFieldValue::toInt() {
   return m_nFieldValue | (m_bIsCovered*16) | (m_bIsMarked*32) | (m_bIsMargin*64); 
}

int CFieldValue::toSolveInt()
{
   if (m_bIsCovered) 
      return 15; 
   else 
      return m_nFieldValue; 
}



