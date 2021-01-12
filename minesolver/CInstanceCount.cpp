// file      : CInstanceCount.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 

#include "CInstanceCount.h" 

#include <iostream>

using namespace std; 

void CInstanceCount::print()
{
   cout << "Total Count : "; m_TotalCount.print(); cout << "\n"; 
   for(deque<CPosFctPair>::iterator iter = m_FieldSet.begin();
       iter != m_FieldSet.end(); 
       iter++) 
   {
      cout << "Field(" << iter->m_Pos.x() << ", " << iter->m_Pos.y() << ") : "; 
      iter->m_Fct.print(); 
      cout << "\n"; 
   }

}


// no bombs, one instance
CInstanceCount::CInstanceCount() : m_TotalCount(0,1)  
{
}

int CInstanceCount::getIndex(const CFieldPos &p)
{
   for(int i=0;i<int(m_FieldSet.size());i++) 
   {
      if (m_FieldSet[i].m_Pos == p) 
         return i; 
   }
   return -1; 
} 

/** 
 * add a field. 
 * @param p field that must not be in the fieldset of *this
 * @param bIsBomb true iff the newly added field is a bomb
 */ 
void CInstanceCount::addField(const CFieldPos &p, bool bIsBomb)
{
   int nIndex = getIndex(p); 
   if (nIndex >= 0) 
   {
      return; 
   }

   if (bIsBomb) 
   {
      m_FieldSet.push_back(CPosFctPair(p, m_TotalCount)); 
   }
   else 
   {
      m_FieldSet.push_back(CPosFctPair(p, CIntDoubleFct(0,0))); // no bombs for all instances 
   } 
      
   if (bIsBomb) 
   {
      m_TotalCount.shift(1); 
      for(deque<CPosFctPair>::iterator iter= m_FieldSet.begin(); 
          iter != m_FieldSet.end(); 
          iter++) 
      {
         iter->m_Fct.shift(1); 
      }
   }  
} 

/** 
 * c1 and c2 must be two CInstanceCount's that have disjunct fields as fieldSet.  
 * This method computes a CInstanceCount that has the union of both 
 * fieldsets as fieldset and assigns it to *this. 
 */ 
void CInstanceCount::makeMergeDisjunct(CInstanceCount &c1, CInstanceCount &c2)
{
   m_FieldSet.clear(); 

   m_TotalCount.makeMult(c1.m_TotalCount, c2.m_TotalCount); 

   CInstanceCount *pC[2]; 
   pC[0] = &c1; 
   pC[1] = &c2; 

   for(int i=0;i<2;i++) 
   {
      for(deque<CPosFctPair>::iterator iter = pC[i]->m_FieldSet.begin(); iter != pC[i]->m_FieldSet.end(); iter++) 
      {
         assert(pC[1-i]->getIndex(iter->m_Pos) == -1); 
         CIntDoubleFct tmpFct; tmpFct.makeMult(iter->m_Fct, pC[1-i]->m_TotalCount); 
         m_FieldSet.push_back(CPosFctPair(iter->m_Pos, tmpFct)); 
      }
   }
}
 
/** 
 * c1 and c2 must have the same fieldset and must represent 
 * disjunct solutions of the same problem instance. 
 * This function merges both CInstanceCount's. 
 */ 
void CInstanceCount::makeMergeSameDomain(CInstanceCount &c1, CInstanceCount &c2)
{
   m_FieldSet.clear(); 
   assert(c1.m_FieldSet.size() == c2.m_FieldSet.size()); 

   m_TotalCount.makeAdd(c1.m_TotalCount, c2.m_TotalCount); 

   for(deque<CPosFctPair>::iterator iter1= c1.m_FieldSet.begin(); 
       iter1 != c1.m_FieldSet.end(); 
       iter1++) 
   {
      int nFound = 0; 
      deque<CPosFctPair>::iterator iter2tmp; 
      for(deque<CPosFctPair>::iterator iter2 = c2.m_FieldSet.begin(); 
          iter2 != c2.m_FieldSet.end(); 
          iter2++)
      {
         if (iter2->m_Pos == iter1->m_Pos) {iter2tmp = iter2; nFound++; }; 
      }
      assert(nFound == 1); 

      assert(iter2tmp != c2.m_FieldSet.end()); 

      CIntDoubleFct tmpFct; tmpFct.makeAdd(iter1->m_Fct, iter2tmp->m_Fct); 
      m_FieldSet.push_back(CPosFctPair(iter1->m_Pos, tmpFct)); 
   }

}

/** 
 * Creates a CInstanceCount that has nBombs more used bombs. 
 */ 
void CInstanceCount::makeAddBomb(CInstanceCount &c, int nBombs)
{
   m_FieldSet.clear(); 
   m_TotalCount.makeShift(c.m_TotalCount, nBombs); 
   for(deque<CPosFctPair>::iterator iter= c.m_FieldSet.begin(); 
       iter != c.m_FieldSet.end(); 
       iter++) 
   {
      CIntDoubleFct tmpFct; tmpFct.makeShift(iter->m_Fct, nBombs); 
      m_FieldSet.push_back(CPosFctPair(iter->m_Pos, tmpFct)); 
   }
} 

