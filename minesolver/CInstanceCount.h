// file      : CInstanceCount.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CINSTANCECOUNT_H_INCLUDED
#define CINSTANCECOUNT_H_INCLUDED

#include <minebase/MineBase.h>
#include "MineMath.h"
#include <deque>
 
/** 
 * Holds the count of all solutions of a minesweeper array. 
 * - Considers only covered fields that are part of the resolution graph. 
 * - It holds the count of solutions in which a given field is a bomb 
 * - It holds the count of solutions that use a given number of bombs. 
 * -> mathematically, it is a function that 
 *    maps (fieldpos, usedBombs) to solutionCount for all
 *    fields in that are covered and are in the resolution graph. 
 * The whole thing is a bit confusing, however, I need this class 
 * to compute the probability that a given field is a bomb. 
 */ 
class CInstanceCount {
public: 
   CInstanceCount(); 
   void addField(const CFieldPos &p, bool bIsBomb);
   void makeMergeDisjunct(CInstanceCount &c1, CInstanceCount &c2); 
   void makeMergeSameDomain(CInstanceCount &c1, CInstanceCount &c2); 
   void makeAddBomb(CInstanceCount &c, int nBombs); 
   void print(); 

public:
   /** 
    * The total count of solutions using n bombs (n is the parameter of CIntDoubleFct) 
    */ 
   CIntDoubleFct m_TotalCount; 
   
   class CPosFctPair {
   public: 
      CPosFctPair(const CFieldPos &Pos, const CIntDoubleFct &Fct) : 
         m_Pos(Pos), m_Fct(Fct)
      {}
      CPosFctPair() {}
   public: 
      CFieldPos m_Pos; 
      CIntDoubleFct m_Fct; 
   }; 

   CIntDoubleFct &sureBomb() {return m_TotalCount;}
   CIntDoubleFct sureNoBomb() {return CIntDoubleFct(0,0);}
   int getIndex(const CFieldPos &p); 

   /** 
    * The count of solutions that are using n bombs and that 
    * have a bomb at field @ref CPosFctPair::m_Pos 
    */ 
   std::deque<CPosFctPair> m_FieldSet; 

   int getFieldCount() {return m_FieldSet.size();}
   CIntDoubleFct& fct(int i) {return m_FieldSet[i].m_Fct;}
   CFieldPos &pos(int i) {return m_FieldSet[i].m_Pos;}  
}; 


#endif 
