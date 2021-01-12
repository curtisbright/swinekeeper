// file      : MineSolver.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 

#include <vector>
#include <cstdlib>
#include <cassert>
#include <deque>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <float.h>
#include <cstdio>

#include <minebase/MineBase.h>
#include <minebase/MineStd.h> 

#include "MineMath.h"
#include "CFieldValue.h"
#include "CMineArray.h" 
#include "CInstanceCount.h" 

#include "MineSolver.h" 
#include "SolutionIter.h" 
#include "CompProbabilities.h" 

using namespace std; 

void auxSolve(CSolutionIter &it)
{
   CSolutionIterG itg; 
   while(it.getNextUnresolvedSubfield(itg)) 
   {
      CSolutionIter it1, it2; 
      itg.getGuesses(it1, it2); 
      auxSolve(it1); 
      auxSolve(it2); 
      itg.applyGuesses(it1, it2); 
      it.insertSolution(itg); 
   }
}

double evalGoodness(
   CMineArray &baseArray, 
   CMineArrayBase<CPropField> &initialPropArray, 
   CMineArrayBase<CPropField> &newPropArray) 
{
   double dGoodness = 0; 
   for(CRangeIterator iter(baseArray.range()); iter.isValid(); iter++) 
   {
      // CFieldValue &baseField = baseArray[iter.curPos()];
      CPropField &initialPropField = initialPropArray[iter.curPos()]; 
      CPropField &newPropField = newPropArray[iter.curPos()]; 
      if (   initialPropField.isUndecideable() 
          && newPropField.isKnownNoBomb()) 
         dGoodness += 1;     
   }
   return dGoodness; 
} 
    
   
/** 
 * Experimental code, propably not useful 
 */ 
bool compGoodness(
   CMineArrayBase<CResultField> &goodnessArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount)
{
   CMineArray baseArray; 

   inputArrayToSolveArray(baseArray, inputArray); 
   
   CMineArrayBase<CPropField> initialPropArray; 
   compProbabilities_Aux(initialPropArray, baseArray, nTotalBombCount); 

   {
   for(CRangeIterator iter(baseArray.range()); iter.isValid(); iter++) 
   {
      CFieldValue &baseField = baseArray[iter.curPos()];
      CPropField &resultField = initialPropArray[iter.curPos()]; 
      if (baseField.isCovered()) 
      {
         if (resultField.isKnownBomb()) 
            baseField.setResolvedAs(true); 
         if (resultField.isKnownNoBomb()) 
            baseField.setResolvedAs(false); 
      }
   }
   }
      
   // CMineArrayBase<CPropField> goodnessArray(initialPropArray); 

   convertArray<CResultField, CPropField>(
      goodnessArray, 
      initialPropArray, 
      CResultField(), 
      propFieldToResult); 

   for(CRangeIterator iter(baseArray.range()); iter.isValid(); iter++) 
   {
      // CFieldValue &baseField = baseArray[iter.curPos()];
      CPropField &resultField = initialPropArray[iter.curPos()]; 
      
      if (resultField.isUndecideable()) 
      {
         double vdProp[2]; 
         vdProp[0] = 1-resultField.getProp(); 
         vdProp[1] = resultField.getProp(); 
         double vdGoodness[2]; 
         for(int nBomb=0;nBomb<2;nBomb++) 
         {
            CMineArray tmpArray(baseArray);
            tmpArray[iter.curPos()].setResolvedAs(nBomb==1);
            CMineArrayBase<CPropField> tmpPropArray; 
            compProbabilities_Aux(tmpPropArray, tmpArray, nTotalBombCount); 
            double dGoodness = /*vdProp[nBomb]*/ evalGoodness(baseArray, initialPropArray, tmpPropArray);
            vdGoodness[nBomb] = dGoodness; 
         }
         char szTmp[1000]; 
         sprintf(szTmp, "P(B)=%5.3f (%5.3f/%5.3f)", resultField.getProp(), vdGoodness[0], vdGoodness[1]); 
         goodnessArray[iter.curPos()].setDesc(std::string( szTmp));    
      }
   }
   // resultArray = goodnessArray; 

   return true; 

}

void markKnownFields(
   CMineArrayBase<CPropField> &resultArray,   
   CMineArray &solveArray, 
   int /*nTotalBombCount*/) 
{
   CSolutionIter it(solveArray); 
   auxSolve(it); 
   CMineArray tmpArray(it.mineArray()); 
   for(CRangeIterator iter(solveArray.range()); iter.isValid(); iter++) 
   {
      CFieldValue &solveField = solveArray[iter.curPos()];
      CFieldValue &tmpField = tmpArray[iter.curPos()]; 
      if (solveField.isCovered()) 
      {
         if (tmpField.isKnownBomb()) 
         {
            solveField.setResolvedAs(true); 
            resultArray[iter.curPos()].setKnownBomb(); 
         }
         if (tmpField.isKnownNoBomb()) 
         {
            solveField.setResolvedAs(false); 
            resultArray[iter.curPos()].setKnownNoBomb(); 
         }
         if (tmpField.isUndecideable()) 
         {
            resultArray[iter.curPos()].setProp(.5); 
         }
      }
   }
}

void auxSolveCounting(CSolutionIter &it, int &nCount)
{
   CSolutionIterG itg; 
   nCount = 1; 
   while(it.getNextUnresolvedSubfield(itg)) 
   {
      CSolutionIter it1, it2; 
      itg.getGuesses(it1, it2); 
      int nCount1, nCount2; 
      auxSolveCounting(it1, nCount1); 
      auxSolveCounting(it2, nCount2); 
      itg.applyGuesses(it1, it2); 
      it.insertSolution(itg); 
      nCount *= (nCount1 + nCount2); 
   }
}

bool compPreSolvedMineArray(
   CMineArray &mineArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount)
{
   inputArrayToSolveArray(mineArray, inputArray); 

   CMineArrayBase<CPropField> propArray;  
   propArray.resize(inputArray.range()); 
   markKnownFields(propArray, mineArray, nTotalBombCount); 
   return true; 
}

bool compSolutionSets(
   CMineArrayBase<CResultField> &resultArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount)
{
   CMineArray baseArray; 

   inputArrayToSolveArray(baseArray, inputArray); 
   
   CMineArrayBase<CPropField> propArray;  
   propArray.resize(inputArray.range()); 
   markKnownFields(propArray, baseArray, nTotalBombCount); 

   convertArray<CResultField, CPropField>(
      resultArray, 
      propArray, 
      CResultField(), 
      propFieldToResult); 

   CSolutionIter it(baseArray); 
   CSolutionIterG itg; 
   while(it.getNextUnresolvedSubfield(itg)) 
   {
      CSolutionIter it1, it2; 
      itg.getGuesses(it1, it2); 
      int nCount1, nCount2; 
      auxSolveCounting(it1, nCount1); 
      auxSolveCounting(it2, nCount2); 
      itg.applyGuesses(it1, it2); 
      it.insertSolution(itg); 
      int nCount = (nCount1 + nCount2); 
      for(std::deque<CFieldPos>::const_iterator iter = itg.activeSubSet().begin(); 
          iter != itg.activeSubSet().end(); 
          iter++) 
      {
         char szTmp[1000]; 
         sprintf(szTmp, "#S=%d", nCount); 
         resultArray[*iter].setDesc(std::string(szTmp)); 
      }
   }

   return true; 
}
