// file      : SolutionSet.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef SOLUTIONSET_H_INCLUDED
#define SOLUTIONSET_H_INCLUDED

#include <minebase/MineBase.h>
#include "MineMath.h"
#include <deque>
#include <vector>

class CFieldSolutionSet {
public: 
   CFieldSolutionSet(bool isBomb);
   CFieldSolutionSet() {}
   void init(bool isBomb); 
   void setInstPerBC(int nBC, double nInst); 
   const CFieldSolutionSet& makeAdd(const CFieldSolutionSet &c1, const CFieldSolutionSet &c2); 
   const CFieldSolutionSet& add(const CFieldSolutionSet &c1); 
   const CFieldSolutionSet& makeMult(const CFieldSolutionSet &c1, const CFieldSolutionSet &c2); 
   const CFieldSolutionSet& mult(const CFieldSolutionSet &c1); 
public: 
   std::vector<bool> m_solutions; 
}; 

class CArraySolutionSet {
public: 
   CInstanceCount(); 
   void addField(const CFieldPos &p, bool bIsBomb);
   void makeMergeDisjunct(CArraySolutionSet &c1, CArraySolutionSet &c2); 
   void makeMergeSameDomain(CArraySolutionSet &c1, CArraySolutionSet &c2); 

private: 
   class FieldPosSetPair {
   public: 
      CFieldPos m_pos; 
      CFieldSolutionSet m_set; 
   }; 

   std::deque<FieldPosSetPair> m_set; 
}; 


#endif 
