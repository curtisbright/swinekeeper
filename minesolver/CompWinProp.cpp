#include "StdAfx.h" 
#include "CompWinProp.h" 

#include "CompProbabilities.h" 
#include "SolutionIter.h" 
#include <cstdio>

struct CacheEntry {
   CacheEntry() {pV[0] = 0; pV[1] = 0; dVal = -1;}
   bool equalID(CacheEntry &val) {return pV[0] == val.pV[0] && pV[1] == val.pV[1];}
   int pV[2]; 
   float dVal; 
}; 

static int nCached = 0; 
static int nComp = 0; 

double compTotalProp_Cached(
   CMineArray &inputArray, 
   int nTotalBombCount) 
{
   int pV[2];
   pV[0] = 0; pV[1] = 0;  
   inputArray.toInt((char*)pV, 8); 

   static CacheEntry *pEntries = NULL; 
   if (!pEntries) 
   {
      pEntries = new CacheEntry[0x10000]; 
   }

   int nIdx = (((pV[0] * pV[1])>>16)
               + ((pV[0] * 1232232123) >> 14) 
               + ((pV[1] * 12355341) >> 17) ) & 0xffff;  

   CacheEntry newEntry; 
   newEntry.pV[0]= pV[0]; 
   newEntry.pV[1]= pV[1]; 

   if (pEntries[nIdx].dVal<0 || !pEntries[nIdx].equalID(newEntry)) 
   {
      newEntry.dVal = compTotalProp(inputArray, nTotalBombCount);  
      pEntries[nIdx] = newEntry; 
   }
   else {
      nCached++; 
   }
      nComp++; 
   //float compVal = float(compTotalProp(inputArray, nTotalBombCount)); 
   //assert(pEntries[nIdx].dVal == compVal); 

   return pEntries[nIdx].dVal; 
}   



double compWinProp_Aux( 
   CMineArray &inputResArray,
   const CFieldPos &pos,  
   int nTotalBombCount); 

double compWinProp( 
   CMineArray &inputResArray,
   int nTotalBombCount, 
   CMineArrayBase<CResultField> *pResultArray = NULL) 
{
   CMineArrayBase<CPropField> resultArray; 

   if (!compProbabilities_Aux(resultArray, inputResArray, nTotalBombCount)) 
   {
      assert(0); 
      return 0; 
   }

   for(CRangeIterator iter(inputResArray.range()); iter.isValid(); iter++) 
   {
      if (inputResArray[iter.curPos()].isCovered())
      {
         if (resultArray[iter.curPos()].isKnownBomb()) 
         {
            if (pResultArray) 
               (*pResultArray)[iter.curPos()].setProp(0); 
         }
      }
   }

   double dMaxWinProp(0); 
   bool bAllResolved(true); 
   for(CRangeIterator iter2(inputResArray.range()); iter2.isValid(); iter2++) 
   {
      if (pResultArray) {
         printf("%s", "*"); 
         fflush(NULL); 
      }

      if (inputResArray[iter2.curPos()].isCovered() && 
          !resultArray[iter2.curPos()].isKnownBomb()&& 
          !resultArray[iter2.curPos()].isKnownNoBomb())
         bAllResolved = false; 

      if (inputResArray[iter2.curPos()].isCovered() && 
          !resultArray[iter2.curPos()].isKnownBomb())
      {
         double dProp = compWinProp_Aux(inputResArray, iter2.curPos(), nTotalBombCount); 
         if (pResultArray) 
         {
            (*pResultArray)[iter2.curPos()].setProp(dProp); 
            printf("%f", dProp); 
         }
         if (dProp > dMaxWinProp) 
            dMaxWinProp = dProp; 
      }
   }
   if (pResultArray) 
      printf("\n"); 
   //assert(dMaxWinProp >= -.01 && dMaxWinProp <= 1.01); 

   if (bAllResolved) 
      return 1; 
   else 
      return dMaxWinProp; 
}   

bool compWinProp(
   CMineArrayBase<CResultField> &resultArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount)
{
   CMineArray solveArray; 

   inputArrayToSolveArray(solveArray, inputArray); 
   
   resultArray.resize(inputArray.range()); 

   compWinProp(solveArray, nTotalBombCount, &resultArray); 

   return true; 
}

double compWinProp_Aux( 
   CMineArray &inputResArray,
   const CFieldPos &pos,  
   int nTotalBombCount)  
{ 
   CMineArray tmpArray = inputResArray; 
   assert(inputResArray[pos].isCovered()); 

   double dBaseProp = compTotalProp/*_Cached*/(tmpArray, nTotalBombCount); 

   double dWinProp(0); 
   double dSumProp(0); 
   for(int i=0;i<=8;i++) 
   {
      CMineArray tmpArray = inputResArray; 
      assert(tmpArray[pos].isCovered()); 
      tmpArray[pos] = CFieldValue(); 
      tmpArray[pos].setCount(i); 
      double dTotalProp = compTotalProp/*_Cached*/(tmpArray, nTotalBombCount)/dBaseProp; 
      if (dTotalProp > 1e-6) 
      {
         dWinProp += dTotalProp * compWinProp(tmpArray, nTotalBombCount); 
         dSumProp += dTotalProp; 
      }
      if (!(dWinProp >= -.01 && dWinProp <= 1.01 && dWinProp <= dSumProp+.01)) 
      { 
         printf("error!"); 
         assert(0); 
      }
   }


   return dWinProp; 
}
