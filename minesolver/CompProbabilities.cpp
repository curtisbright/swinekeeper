#include "StdAfx.h" 
#include "CompProbabilities.h" 

#include <deque>
#include <cstdio>
#include <string>
#include <cassert>
#include <vector>

#include "SolutionIter.h" 
#include "CMineArray.h" 
#include "CInstanceCount.h" 
#include <minebase/MineStd.h>
#include <storage/Document.h>

using namespace std; 

void CPropField::transferData(Storage::CSection section)
{
   section.transferItem("has-prob").transferBool(m_bHasProp); 
   section.transferItem("prob").transferFloat(m_dProp); 
}



/** 
 * Creates a result field from a propfield
 */ 
CResultField propFieldToResult(CPropField src) 
{
   CResultField res; 
   if (src.hasProp())
   { 
      res.setProp(src.getProp()); 
      if (src.isUndecideable()) 
      {
         char szTmp[1000]; 
         sprintf(szTmp, "P(B)=%5.3f", src.getProp()); 
         res.setDesc(std::string(szTmp)); 
         res.setVal(src.getProp()); 
      }
   }
   return res; 
}


static bool auxSolveProp(CSolutionIter &it, CInstanceCount &instCount, CTerminator *pTerminator) 
{
   const deque<CFieldPos> &resolved = it.resolvedFields(); 
   const CMineArray &array = it.mineArray(); 
   for(deque<CFieldPos>::const_iterator iter = resolved.begin(); iter != resolved.end(); iter++) 
   {
      instCount.addField(*iter, array.fieldValue(*iter).isKnownBomb()); 
   }

   CSolutionIterG itg; 
   while(it.getNextUnresolvedSubfield(itg)) 
   {
      CSolutionIter it1, it2; 
      itg.getGuesses(it1, it2); 
      CInstanceCount inst0, inst1; 

      auxSolveProp(it1, inst0, pTerminator); 
      if (pTerminator && pTerminator->doTerminate()) 
         return false; 

      auxSolveProp(it2, inst1, pTerminator); 
      if (pTerminator && pTerminator->doTerminate()) 
         return false; 

      CInstanceCount inst01; 
      if (!it1.isValid()) 
      {
         inst01 = inst1; 
      }
      else if (!it2.isValid()) 
      {
         inst01 = inst0; 
      }
      else {
         inst01.makeMergeSameDomain(inst0, inst1); 
      }
       
      CInstanceCount instTmp; 
      instTmp.makeMergeDisjunct(instCount, inst01); 
      instCount = instTmp; 
      
      itg.applyGuesses(it1, it2); 
      it.insertSolution(itg); 
   } 
   return it.isValid(); 
}

bool compProbabilities_Aux(
   CMineArrayBase<CPropField> &resultArray, 
   CMineArray &inputResArray, 
   int nTotalBombCount, 
   double *pdWaysToCoverFieldsWithBombs, 
   CTerminator *pTerminator)
{
   CMineArray resField(inputResArray); 

   // the solver algo is not able to recognize some invalid arrays as invalid
   // -> i have to test first 
   if (!inputResArray.isValidArray()) 
      return false; 

   CInstanceCount instCount; 
   CSolutionIter it(resField); 
   if (!auxSolveProp(it, instCount, pTerminator)) 
      return false;  
   resField = it.mineArray(); 

   // count of bombs the position of which has not been resolved yet 
   // XXX uncoveredBombCount is always 0, stupid calculation XXX 
   int nRemainingBombs = nTotalBombCount - resField.uncoveredBombCount(); 

   // covered cells that are not active, i.e. that are not neighbors of a 
   // uncovered cell 
   int nNACoveredCells = resField.coveredNonActiveCells(); 

   CIntDoubleFct &totalCount = instCount.m_TotalCount; 

   int nBaseB = totalCount.minNotZeroIdx();
   int nMaxB = totalCount.size(); 
   assert(nBaseB < nMaxB); 

   // only to avoid very large numbers during the computations below, 
   // some numbers below are divided by (nNACoveredCells)
   //                                   (nMaxBase       ) 
   int nMaxBase = MineStd::auxMin(nRemainingBombs-nBaseB, nNACoveredCells); 

   // vdProp[nB] is the probability that there are nB bombs under the active cells 
   vector<double> vdProp(nMaxB);
    
   double dNAFieldProp(0); // probability that a non-active field contains a bomb 

   double dTotalCount = 0;  // total number of ways to cover the fields with bombs 
   int nB; 
   // for all ways to partition the remaining bombs among the active and 
   // the non-active fields 
   for(nB=0;nB<nMaxB;nB++) 
   {
      // we have nB bombs in the active fiels, and the rest in the non-active fields 
      double dP = 0; 
      if (totalCount[nB] != 0 
          && nRemainingBombs - nB <=nNACoveredCells
          && nB <= nRemainingBombs) 
      {
         double dNAInst = bOutOfC(nRemainingBombs - nB, nNACoveredCells, nMaxBase); 
         double dAInst = totalCount[nB]; 
         dP = dNAInst * dAInst; // dP is the number of ways to cover the fields  
                                // with nB bombs in the active fields (times a constant factor) 
         // assert(!_isnan(dNAInst));

         double dNAFieldIsBomb = double(nRemainingBombs - nB)/nNACoveredCells;
         dNAFieldProp += dP*dNAFieldIsBomb;        
      }
      vdProp[nB] = dP; 
      dTotalCount += dP;  
   }
   
   // happens if there are less covered bombs than cells 
   if (dTotalCount <=0)    
      return false;
   
   for(nB=0;nB<nMaxB;nB++) 
   {
      vdProp[nB] /= dTotalCount; 
      // assert(!_isnan(vdProp[nB])); 
   }  
   dNAFieldProp /= dTotalCount;  

   double dWaysToCoverFieldsWithBombs = dTotalCount * bOutOfC(nMaxBase, nNACoveredCells); 
   if (pdWaysToCoverFieldsWithBombs) 
      *pdWaysToCoverFieldsWithBombs = dWaysToCoverFieldsWithBombs; 
   

   // create a result array (not really part of the algo) 
   resultArray.resize(inputResArray.range()); 
   
   {
   for(CRangeIterator iter(resultArray.range()); iter.isValid(); iter++) 
   {
      CFieldValue &res = resField[iter.curPos()];
      CPropField &resultField = resultArray[iter.curPos()]; 
      if (res.isCovered()) 
      {
         if (res.isKnownBomb()) 
            resultField.setKnownBomb(); 
         if (res.isKnownNoBomb()) 
            resultField.setKnownNoBomb(); 
      }
   }
   }

   int nF = instCount.getFieldCount(); 
   int i; 
   for(i=0;i<nF;i++) 
   {
      double dProp = instCount.fct(i).getProp(vdProp, totalCount); 
      assert(inputResArray[instCount.pos(i)].isCovered()); 
      resultArray[instCount.pos(i)].setProp(dProp); 
   }   

   /* 
   // set the probability of non-active fields 
   {
   for(CRangeIterator iter(resultArray.range()); iter.isValid(); iter++) 
   {
      CFieldValue &res = resField[iter.curPos()];
      CPropField &resultField = resultArray[iter.curPos()]; 
      if (res.isCovered() && !resultField.hasProp()) 
      {
         resultArray[iter.curPos()].setProp(dNAFieldProp); 
      }
   }
   }
   */ 

   bool bSuc = validateProbabilities(resultArray ,inputResArray, nTotalBombCount); 

   assert(bSuc); 

   return true; 
}

bool compProbabilities(
   CMineArrayBase<CResultField> &resultArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount, 
   CTerminator *pTerminator)
{
   CMineArray solveArray; 

   inputArrayToSolveArray(solveArray, inputArray); 
   
   CMineArrayBase<CPropField> propArray; 
   if (!compProbabilities_Aux(propArray, solveArray, nTotalBombCount, NULL, pTerminator)) 
      return false; 

   convertArray<CResultField, CPropField>(
      resultArray, 
      propArray, 
      CResultField(), 
      propFieldToResult); 

   return true; 
}

double compTotalProp( 
   CMineArray &inputArray, 
   int nTotalBombCount) 
{
   CMineArrayBase<CPropField> dummy; 
   double dWaysToCoverFieldsWithBombs = 0; 
   if (!compProbabilities_Aux(dummy, inputArray, nTotalBombCount, &dWaysToCoverFieldsWithBombs)) 
      return 0; 
     
   double dTotalWays = bOutOfC(nTotalBombCount ,inputArray.range().getFieldCount());   
      
   double dTotalProp = dWaysToCoverFieldsWithBombs/dTotalWays; 
   assert(dTotalProp >= 0 && dTotalProp <= 1); 
   
   //inputResArray.print(); 
   //printf("Total Prop: %lf\n", dTotalProp); 

   return dTotalProp; 
}   

class CProbabililitySum {
public: 
   CProbabililitySum() : m_dProp(0) {}
   void operator()(const CPropField &value) {
      if (value.hasProp()) 
         m_dProp += value.getProp(); 
   }
   double getSum() {return m_dProp;}
private: 
   double m_dProp; 
}; 


bool validateProbabilities( 
   CMineArrayBase<CPropField> &resultArray, 
   CMineArray &inputResArray, 
   int /*nTotalBombCount*/) 
{
   if (!(resultArray.range() == inputResArray.range()))
      return false; 

   // each probability must be in the valid range 
   for(CRangeIterator piter(resultArray.range()); piter.isValid(); piter++) 
   {
      if (resultArray[piter.curPos()].hasProp())
      {
         double dProp = resultArray[piter.curPos()].getProp(); 
         if (dProp < -.01 || dProp > 1.01)    
            return false; 
      }
   }

   // the expected number of bombs around a uncovered field must 
   // be equal to the number of bombs around the field 
   for(CRangeIterator iter(inputResArray.range()); iter.isValid(); iter++) 
   {
      CFieldPos pos = iter.curPos(); 
      CFieldValue curVal = inputResArray[pos]; 
      if (curVal.isKnownCount()) 
      {
         CProbabililitySum neighborPropSum; 
         resultArray.doWithNeighbors(pos, neighborPropSum); 
         if (fabs(neighborPropSum.getSum() - curVal.getCount()) > .01)
            return false;  
      }
   }

   /* 
   // the expected number of bombs in the array must be equal to the 
   // total number of bombs 
   // XXX does only work if non-active fields have probabilities 
   CProbabililitySum totalPropSum; 
   resultArray.doWithArray(totalPropSum); 
   if (fabs(totalPropSum.getSum() - nTotalBombCount) > .01) 
      return false; 
   */ 
   return true; 
}



