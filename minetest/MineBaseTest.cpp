// file      : MineBaseTest.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "MineBaseTest.h"
#include <minebase/MineBase.h>
#include "TestFramework.h" 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// CTestFieldPos
class CTestFieldPos : public CTestContext
{
public: 
   CTestFieldPos(); 
   void testNeighbor(); 
   void testOperators(); 

   static CTest *createTest(); 
private: 
   CFieldPos m_pos1; 
   CFieldPos m_pos2; 
   CFieldPos m_pos3; 
}; 

CTestFieldPos::CTestFieldPos() : 
   m_pos1(2,3), 
   m_pos2(5,4), 
   m_pos3(10,32) 
{
}

void CTestFieldPos::testNeighbor()
{
   int i,j; 
   for(i=0;i<8;i++) 
   {
      EXPECT(m_pos1.distTo(m_pos1.neighbor(i))==1); 
   }

   for(i=0;i<8;i++) for(j=0;j<8;j++) 
   {
      EXPECT(i == j || m_pos2.neighbor(i).distTo(m_pos2.neighbor(j)) != 0); 
   }
} 

void CTestFieldPos::testOperators()
{
   EXPECT(m_pos1 < m_pos2); 
   EXPECT(m_pos1 == m_pos1); 
   EXPECT(!(m_pos1 == m_pos2));
   EXPECT(m_pos1.inRange(4,4)); 
   EXPECT(!m_pos1.inRange(3,3)); 
   EXPECT(CFieldPos(3,2).sum(2,3) == CFieldPos(5,5));
   EXPECT(CFieldPos(4,5).x() == 4); 
   EXPECT(CFieldPos(4,5).y() == 5); 
}

CTest *CTestFieldPos::createTest()
{
   CTestSet *pTestSet = new CTestSet("CTestFieldPos"); 
   #define ADDTEST(FCT) pTestSet->addTest(new CTestCaller<CTestFieldPos>(#FCT, &CTestFieldPos::FCT))
   ADDTEST(testNeighbor); 
   ADDTEST(testOperators); 
   #undef ADDTEST 
   return pTestSet; 
}

class CFieldRangeTest : public CTestContext 
{
public: 
   CFieldRangeTest(); 
   void testOperators(); 
   static CTest *createTest(); 
public: 
   CFieldRange m_range1; 
   CFieldRange m_range2; 
   CFieldPos m_pos1; 
   CFieldPos m_pos2; 
}; 

CFieldRangeTest::CFieldRangeTest() : 
   m_range1(2,1,4,5), 
   m_range2(2,2,3,7), 
   m_pos1(1,2), 
   m_pos2(3,6)
{}

void CFieldRangeTest::testOperators()
{
   EXPECT(m_range1.beginX() == 2); 
   EXPECT(m_range1.getFieldCount() == 8);
   EXPECT(m_range1.enlarged(1) == CFieldRange(1,0,5,6)); 
   EXPECT(m_range1.inRange(CFieldPos(2,2))); 
   EXPECT(!m_range1.inRange(CFieldPos(2,5))); 
}

CTest *CFieldRangeTest::createTest()
{
   CTestSet *pTestSet = new CTestSet("CFieldRangeTest"); 
   #define ADDTEST(FCT) pTestSet->addTest(new CTestCaller<CFieldRangeTest>(#FCT, &CFieldRangeTest::FCT))
   ADDTEST(testOperators); 
   #undef ADDTEST 
   return pTestSet; 
}

CTest *testCreateMineBaseTest()
{
   CTestSet *pTestSet = new CTestSet("MineBaseTest"); 
   pTestSet->addTest(CTestFieldPos::createTest()); 
   pTestSet->addTest(CFieldRangeTest::createTest()); 
   return pTestSet; 
}




