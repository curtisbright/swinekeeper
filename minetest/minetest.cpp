// file      : minetest.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h"
#include <cstdio>
#include "MineBaseTest.h" 
#include "SolverTest.h"
#include "TestFramework.h" 
#include "SingleTest.h" 
#include "RegressionTestTest.h" 
#include "MinePropRegTest.h" 

CTestSet *getStdTests()
{
   CTestSet *pStdTestSet = new CTestSet("STD_TEST"); 
   pStdTestSet->addTest(testCreateMineBaseTest()); 
   return pStdTestSet; 
}

int main(int argc, char* argv[])
{

   CTestSet *pTestSet = new CTestSet("ROOT"); 
  //  pTestSet->addTest(getStdTests()); 

   // pTestSet->addTest(testCreateSolverTest()); 
   // pTestSet->addTest(testCreateRegressionTestTest()); 
   pTestSet->addTest(testCreateSingleTest());
   // pTestSet->addTest(testCreateMinePropRegTest()); 

   CTestResult result; 
   pTestSet->run(&result); 
   result.printLog(); 
   
   delete pTestSet; 
    return 0;
}

