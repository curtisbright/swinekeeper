// file      : SolutionEnumerator.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "SolutionEnumerator.h" 

#include "SolutionIter.h"
#include "CompProbabilities.h" 

#include <cstdio>

using namespace std; 


void CBoolVector::makeAdd(const CBoolVector &v1, const CBoolVector &v2)
{
   m_vector.resize(v1.size() + v2.size()); 
   int i;
   for(i=0;i<v1.size();i++) m_vector[i] = v1.m_vector[i]; 
   for(i=0;i<v2.size();i++) m_vector[i+v1.size()] = v2.m_vector[i]; 
}

void CBoolVector::makeScaled(const CBoolVector &v1, int nFactor)
{
   m_vector.resize(v1.size()*nFactor);
   for(int i=0;i<v1.size();i++)
      for(int j=0;j<nFactor;j++) 
         m_vector[i*nFactor + j] = v1.m_vector[i]; 
}

void CBoolVector::makeRepeated(const CBoolVector &v1, int nFactor)
{
   m_vector.resize(v1.size()*nFactor);
   for(int i=0;i<int(v1.size());i++)
      for(int j=0;j<nFactor;j++) 
         m_vector[i + j*v1.size()] = v1.m_vector[i]; 
}

std::string CBoolVector::toString(int nNum) const
{
   char szTmp[1000]; 
   sprintf(szTmp, "%3d: ", nNum); 
   for(int i=0;i<int(m_vector.size());i++) 
   {
      if (m_vector[i]) 
         strcat(szTmp, "#"); 
      else 
         strcat(szTmp, "0");    
   } 
   return std::string(szTmp); 
}


void CSolutionEnum::makeAdd(const CSolutionEnum &e1,  const CSolutionEnum &e2)
{
   m_vmap.clear(); 
   m_nSize = e1.m_nSize * e2.m_nSize;    
   {
   for(VMapType::const_iterator iter = e1.m_vmap.begin(); 
       iter != e1.m_vmap.end(); 
       iter++) 
   {
      pair<VMapType::iterator, bool> newElm
         = m_vmap.insert(std::make_pair(iter->first, CBoolVector())); 
      assert(newElm.second == true); 
      newElm.first->second.makeRepeated(iter->second, e2.m_nSize); 
      // int nTSize = newElm.first->second.size(); 
      assert(newElm.first->second.size() == m_nSize); 
   }
   }

   {
   for(VMapType::const_iterator iter = e2.m_vmap.begin(); 
       iter != e2.m_vmap.end(); 
       iter++) 
   {
      pair<VMapType::iterator, bool> newElm
         = m_vmap.insert(std::make_pair(iter->first, CBoolVector())); 
      assert(newElm.second == true); 
      newElm.first->second.makeScaled(iter->second, e1.m_nSize); 
      assert(newElm.first->second.size() == m_nSize); 
   }
   }
}

void CSolutionEnum::makeMerge(const CSolutionEnum &e1,  const CSolutionEnum &e2)
{
   assert(e1.m_vmap.size() == e2.m_vmap.size()); 
   m_vmap.clear(); 
   m_nSize = e1.m_nSize + e2.m_nSize;    

   for(VMapType::const_iterator iter = e1.m_vmap.begin(); 
       iter != e1.m_vmap.end(); 
       iter++) 
   {
      VMapType::const_iterator iter2 = e2.m_vmap.find(iter->first); 

      // XXX exit XXX 
      assert(iter2 != e2.m_vmap.end()); 

      pair<VMapType::iterator, bool> newElm
         = m_vmap.insert(std::make_pair(iter->first, CBoolVector())); 
      assert(newElm.second == true); 
      
      newElm.first->second.makeAdd(iter->second, iter2->second);
      assert(newElm.first->second.size() == m_nSize); 
   }
}

void CSolutionEnum::addSolvedField(const CFieldPos &pos, bool bVal)
{
      pair<VMapType::iterator, bool> newElm
         = m_vmap.insert(std::make_pair(pos, CBoolVector())); 
      assert(newElm.second == true); 
      newElm.first->second.makeScaledSingle(bVal, m_nSize); 
}


bool auxSolveEnum(CSolutionIter &it, CSolutionEnum &solEnum) 
{
   const deque<CFieldPos> &resolved = it.resolvedFields(); 
   const CMineArray &array = it.mineArray(); 
   for(deque<CFieldPos>::const_iterator iter = resolved.begin(); iter != resolved.end(); iter++) 
   {
      solEnum.addSolvedField(*iter, array.fieldValue(*iter).isKnownBomb()); 
   }

   CSolutionIterG itg; 
   while(it.getNextUnresolvedSubfield(itg)) 
   {
      CSolutionIter it1, it2; 
      itg.getGuesses(it1, it2); 
      CSolutionEnum solEnum0, solEnum1; 
      auxSolveEnum(it1, solEnum0); 
      auxSolveEnum(it2, solEnum1); 

      CSolutionEnum solEnum01; 
      if (!it1.isValid()) 
      {
         solEnum01 = solEnum0; 
      }
      else if (!it2.isValid()) 
      {
         solEnum01 = solEnum1; 
      }
      else {
         solEnum01.makeMerge(solEnum0, solEnum1); 
      }
       
      if (it1.isValid() || it2.isValid()) 
      {
         CSolutionEnum solEnumTmp; 
         solEnumTmp.makeAdd(solEnum, solEnum01); 
         solEnum = solEnumTmp; 
      }
       
      itg.applyGuesses(it1, it2); 
      it.insertSolution(itg); 
   } 

   return true; 
}

void applyToResultArray(
   CMineArrayBase<CResultField> &resultArray, 
   const CSolutionEnum &e,
   int nNum) 
{
   for(CSolutionEnum::VMapType::const_iterator iter = e.m_vmap.begin(); 
       iter != e.m_vmap.end(); 
       iter++) 
   {
      CFieldPos pos = iter->first; 
      resultArray[pos].setDesc(iter->second.toString(nNum)); 
   }
}


bool compSolutionEnum(
   CMineArrayBase<CResultField> &resultArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount,
   CSolEnumArray *pEnumArray)
{
   CMineArray baseArray; 
   int nNum = 0; 

   CSolEnumArray solArray; 
   if (pEnumArray == NULL) 
      pEnumArray = &solArray; 

   compProbabilities(resultArray, inputArray, nTotalBombCount); 
   pEnumArray->init(resultArray); 

   compPreSolvedMineArray(baseArray, inputArray, nTotalBombCount); 
   CSolutionIter it(baseArray); 
   CSolutionIterG itg; 
   while(it.getNextUnresolvedSubfield(itg)) 
   {
      CSolutionIter it1, it2; 
      itg.getGuesses(it1, it2); 
      CSolutionEnum solEnum0, solEnum1; 
      auxSolveEnum(it1, solEnum0); 
      auxSolveEnum(it2, solEnum1); 

      CSolutionEnum solEnum01; 
      if (!it1.isValid()) 
      {
         solEnum01 = solEnum0; 
      }
      else if (!it2.isValid()) 
      {
         solEnum01 = solEnum1; 
      }
      else {
         solEnum01.makeMerge(solEnum0, solEnum1); 
      }
      
      if (it1.isValid() || it2.isValid()) 
      {
         applyToResultArray(resultArray, solEnum01, nNum++); 
         pEnumArray->addSolutionEnum(solEnum01);        
      }

      itg.applyGuesses(it1, it2); 
      it.insertSolution(itg); 
   } 
   
   return true; 
}

void CSolEnumArray::applySolution(int nSet, int nSolIdx)
{
   assert(nSet >= 0 && nSet < int(m_solVector.size())); 
   CSolutionEnum &e = m_solVector[nSet]; 
   e.m_nCurSolution = nSolIdx; 
   assert(nSolIdx >= 0 && nSolIdx < e.solutionCount()); 

   for(CSolutionEnum::VMapType::const_iterator iter = e.m_vmap.begin(); 
       iter != e.m_vmap.end(); 
       iter++) 
   {
      CFieldPos pos = iter->first; 
      (*this)[pos].setTmpSolution(iter->second.solutions()[nSolIdx]); 
   }
   
}

/** 
 * Returns the number of solutions of a given set  
 * @see CSolEnumField::setIndex
 */ 
int CSolEnumArray::getSolutionCount(int nSet) const 
{
   assert(nSet >= 0 && nSet < int(m_solVector.size())); 
   return m_solVector[nSet].solutionCount();
}

/** 
 * Show the next solution of the solution set with index nSet
 */ 
void CSolEnumArray::nextSolution(int nSet)
{
   applySolution(
      nSet, 
      (m_solVector[nSet].m_nCurSolution + 1) % m_solVector[nSet].m_nSize
   ); 
}

static CSolEnumField toSolEnumField(CResultField resF) 
{
   CSolEnumField dstF; 
   if (resF.isKnownBomb()) dstF.setResolved(true); 
   if (resF.isKnownNoBomb()) dstF.setResolved(false); 
   return dstF; 
}

void CSolEnumArray::init(const CMineArrayBase<CResultField> &resField)
{
   convertArray<CSolEnumField, CResultField>(
      *this, 
      resField, 
      CSolEnumField(), 
      toSolEnumField); 
}

void CSolEnumArray::addSolutionEnum(const CSolutionEnum &e)
{
   int nIdx = m_solVector.size(); 
   m_solVector.push_back(e); 
   for(CSolutionEnum::VMapType::const_iterator iter = e.m_vmap.begin(); 
       iter != e.m_vmap.end(); 
       iter++) 
   {
      CFieldPos pos = iter->first; 
      (*this)[pos].setSolutionSet(nIdx); 
   }
   applySolution(nIdx, 0); 
}






