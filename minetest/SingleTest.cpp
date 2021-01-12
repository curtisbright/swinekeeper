// file      : SingleTest.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "SingleTest.h"

#include "TestFramework.h" 
#include <cassert>
#include <minebase/PlayArray.h>
#include <storage/Document.h> 
#include <cstdio>
#include <minebase/MineBaseSerialize.h>
#include <minesolver/CompWinProp.h>
#include <minesolver/CompProbabilities.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

class CSingleTest : public CTestContext  
{
public:
    CSingleTest();
   void execTest(); 
   void trySolve(); 
    virtual ~CSingleTest();
   static CTest *createTest(); 

};


CSingleTest::CSingleTest()
{

}

CSingleTest::~CSingleTest()
{

}

std::string fieldSectionToString(Storage::CSection section) 
{
   bool bCovered(false); 
   section.findItem("covered").getBool(bCovered); 
   std::string markedState; 
   section.findItem("marked-state").getString(markedState); 
   bool bIsBomb(false);
   section.findItem("is-bomb").getBool(bIsBomb); 
   int nBombCount(9); 
   section.findItem("neighbor-bomb-count").getInt(nBombCount); 

   std::string str("~~"); 
   if (bCovered) 
   {
      if (markedState == "bomb") 
         str[0] = 'M'; 
      else if (markedState == "questionmark") 
         str[0] = '?'; 
      else if (markedState == "none") 
         str[0] = 'C'; 
   }
   else 
   {
      str[0] = '.'; 
   }

   if (bIsBomb) 
   {
      str[1] = '*'; 
   }   
   else 
   {
      str[1] = '0' + nBombCount; 
   }
   
   return str; 
}

void CSingleTest::execTest()
{
   CPlayArray playArray; 
   playArray.makePlayField(8, 8, 16); 
   Storage::CDocument doc("playarray"); 
   playArray.transferData(doc.rootSection(true));
   std::string str; 
   doc.serialize(str); 
   printf(str.c_str()); 

   CPlayArray playArray2; 
   Storage::CDocument doc2; 
   doc2.initFromString(str); 
   playArray2.transferData(doc2.rootSection(false)); 

   EXPECT(playArray2.isObjectValid()); 
   
   EXPECT(playArray == playArray2);    
}

void CSingleTest::trySolve()
{
   CPlayArray playArray; 
   Storage::CDocument doc2; 
   
   /* 
   std::string str("<rows><row>1CCCC</row>"
                         "<row>3CCCC</row>"
                         "<row>BB22B</row>"
                         "<row>22111</row></rows>"); 
   */ 
   std::string str("<rows><row>B3B22BB1</row>"
                         "<row>CC4CC332</row>"
                         "<row>CCCCC1CC</row></rows>"); 
   int nBombCount = 9; 
   doc2.initFromString(str); 
   
   CMineArrayBase<CInputField> inputArray; 
   
   bool bSuc = transferDataToObjectCompact<CInputField>(
      doc2.rootSection(false), 
      inputArray); 
   EXPECT(bSuc); 

   CMineArrayBase<CResultField> resultArray; 
   bSuc = compProbabilities(
          // compWinProp(  
      resultArray, inputArray, nBombCount); 
   DbgPrint(bSuc ? "" : "Invalid Array\n"); 

   if (bSuc) 
   {
   Storage::CDocument doc3("prop");
   transferDataFromObjectCompact<CResultField>( 
      doc3.rootSection(true),
      resultArray); 

   std::string docStr; 
   doc3.serialize(docStr); 
    
   DbgPrint(docStr.c_str()); 
   }
}



CTest *CSingleTest::createTest()
{
   CTestSet *pTestSet = new CTestSet("CSingleTest"); 
   //pTestSet->addTest( 
   //   new CTestCaller<CSingleTest>("execTest", &CSingleTest::execTest)
   //); 
   pTestSet->addTest( 
      new CTestCaller<CSingleTest>("trySolve", &CSingleTest::trySolve)
   ); 
   return pTestSet; 
}


CTest *testCreateSingleTest()
{
   return CSingleTest::createTest();
}
