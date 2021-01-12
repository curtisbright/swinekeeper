// file      : SolverTest.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "SolverTest.h"

#include "TestFramework.h" 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include <cassert>
#include <minebase/PlayArray.h>
#include <minesolver/SolutionUtil.h>
#include <cstdio>
#include <minesolver/CompProbabilities.h>

// uses the solver algo to play minesweeper 
// tests if the fields that were uncovered by the algo were 
// actually no bombs etc. 
class CSolverTest : public CTestContext 
{
public:
    CSolverTest();
   void execTest(); 
   static CTest *createTest(); 

private: 
   void autoUncover(CPlayArray &array, const CFieldPos &pos, bool bSureNoBomb); 
   bool uncoverSolveableFields(CPlayArray &array, int nTotalBombCount); 
};

CSolverTest::CSolverTest()
{

}


void CSolverTest::autoUncover(CPlayArray &array, const CFieldPos &pos, bool bSureNoBomb) 
{
   if (!array[pos].isBomb()) 
   {
      array[pos].uncover(); 
      if (array[pos].getCount()==0) 
      {
         for(int i=0;i<8;i++) 
         {
            CFieldPos nei(pos.neighbor(i)); 
            if (array[nei].isCovered()) 
               autoUncover(array, nei, true); 
         }
      }
   }
   else 
   {
      EXPECT(!bSureNoBomb); 
   } 
}

bool CSolverTest::uncoverSolveableFields(CPlayArray &array, int nTotalBombCount)
{
   // solve the minesweeper instance described by 'array' 
   CMineArrayBase<CInputField> solverInputArray; 
   convertArray<CInputField, CPlayField>(
      solverInputArray, 
      array, 
      CInputField(), 
      SolUtil::cnvToInputField); 
   CMineArrayBase<CResultField> propArray; 
   compProbabilities(
      propArray, 
      solverInputArray,
      nTotalBombCount);  

   // check if the computed values are consistent with 
   // the source data and uncover fields that are by sure no bombs 
   bool bUncoveredAField(false); 
   for(CRangeIterator iter(array.range()); iter.isValid(); iter++) 
   {
      if (propArray[iter.curPos()].isKnownNoBomb() && array[iter.curPos()].isCovered()) 
      {
         // algo said: there's no bomb under this field 
         EXPECT(!array[iter.curPos()].isBomb()); 
         autoUncover(array, iter.curPos(), true); 
         bUncoveredAField = true; 
      }
      if (propArray[iter.curPos()].isKnownBomb()) 
      {
         // algo said: there's a bomb under this field 
         EXPECT(array[iter.curPos()].isBomb()); 
         array[iter.curPos()].setMarkedAsBomb(); 
      }
   }

   return bUncoveredAField; 
}

void CSolverTest::execTest()
{
   CPlayArray playArray; 
   playArray.makePlayField(30, 16, 99); 
   for(int i=10;i<20;i++) 
      autoUncover(playArray, CFieldPos(i, 0), false);
               
   while (uncoverSolveableFields(playArray, 99)); 
   printf("SimpleTest : Remaining Fields: %d, Remaining Bombs: %d\n", 
      playArray.getCoveredFieldCount()-playArray.getBombFlagCount(), 
      99-playArray.getBombFlagCount()); 
}

CTest *CSolverTest::createTest()
{
   CTestSet *pTestSet = new CTestSet("CSolverTest"); 
   pTestSet->addTest( 
      new CTestRepeater(
         new CSetRandDecorator( 
            new CTestCaller<CSolverTest>("execTest", &CSolverTest::execTest)
         ), 
         10 
      )
   ); 
   return pTestSet; 
}


CTest *testCreateSolverTest()
{
   return CSolverTest::createTest();
}



