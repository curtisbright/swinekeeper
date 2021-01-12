// file      : TestFramework.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "TestFramework.h"

#include <cassert>


// XXX put into config module XXX 
#ifdef _MSC_VER
#include <windows.h>
void DbgPrint(const char *psz) 
{
   OutputDebugString(psz); 
   printf("%s", psz); 
}
#else 
#include <cstdio>
void DbgPrint(const char *psz) 
{
   printf("%s", psz); 
}
#endif 



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestException::CTestException()
{
}


CTestException::CTestException(
   const std::string &msg, 
   const std::string &file, 
   int nLine) : 
      m_message(msg), 
      m_fileName(file), 
      m_lineNumber(nLine) 
   {} 



std::string CTestException::message() const
{
   return m_message; 
}

std::string CTestException::filename() const
{
   return m_fileName; 
}

int CTestException::fileline() const
{
   return m_lineNumber; 
}

CTestResult::CTestResult() : 
   m_nTestCount(0)
{

}

CTestResult::~CTestResult()
{

}

void CTestResult::testFailed(const CTestException &e)
{
   CFailedTest failedTest; 
   failedTest.m_exception = e; 
   failedTest.m_testName = curTestDesc(); 
   m_failedTests.push_back(failedTest); 
}

void CTestResult::addMessage(const std::string &str)
{
   CFailedTest failedTest; 
   failedTest.m_exception = CTestException(str, std::string("Framework"), 0); 
   failedTest.m_testName = curTestDesc(); 
   m_failedTests.push_back(failedTest); 
}


int CTestResult::errorCount() const 
{
   return m_failedTests.size(); 
}

bool CTestResult::success() const
{
   return errorCount()==0; 
}

void CTestResult::beginTest(const std::string &testName)
{
   m_testNameStack.push_back(testName); 
}

void CTestResult::endTest()
{
   m_testNameStack.pop_back(); 
}

void CTestResult::incTestCount()
{
   m_nTestCount++;
}


std::string CTestResult::curTestDesc() const
{
   std::string desc; 
   for(std::deque<std::string>::const_iterator iter = m_testNameStack.begin(); 
       iter != m_testNameStack.end(); iter++) 
   {
      desc += "/" + (*iter); 
   }
   return desc; 
}


void CTestResult::printLog() const
{
   if (success()) 
   {
      char szStr[1024]; 
      sprintf(szStr, "\n#### All Tests succeeded (%d Tests) ####\n\n", m_nTestCount); 
      DbgPrint(szStr); 
   }
   else 
   {
      DbgPrint("\n#### There were failures:\n\n"); 
   }

   for(FailedTestIter iter = m_failedTests.begin(); iter != m_failedTests.end(); iter++) 
   {
      char szStr[1024]; 
      sprintf(
         szStr, 
         "%s(%d): Test %s failed: %s\n", 
         (*iter).m_exception.filename().c_str(), 
         (*iter).m_exception.fileline(), 
         (*iter).m_testName.c_str(), 
         (*iter).m_exception.message().c_str()
      ); 
      DbgPrint(szStr);
   } 
   if (!success()) 
      DbgPrint("####################################################### \n"); 
}


CTest::CTest(const char *pszName) : 
   m_name(pszName) 
{
}

CTest::~CTest () 
{
}

std::string CTest::name() 
{
   return m_name; 
}

CRegressionTest::CRegressionTest(const char *pszName) : CTest(pszName) {}


CTestSet::CTestSet(const char *pszName) : 
   CTest(pszName) {}

CTestSet::~CTestSet()
{
   for(TestsIter iter = m_tests.begin(); iter != m_tests.end(); iter++) 
      delete (*iter); 
}


void CTestSet::run (CTestResult *pResult) 
{
   pResult->beginTest(name().c_str()); 
   for(TestsIter iter = m_tests.begin(); iter != m_tests.end(); iter++) 
      (*iter)->run(pResult); 
   pResult->endTest(); 
}

void CTestSet::addTest(CTest *pTest)
{
   m_tests.push_back(pTest); 
}

void CTestContextBase::expect(bool expr, const char *pszExpr, const char *pszFile, int nLine)
{
   if (!expr) 
      throw CTestException(std::string(pszExpr), std::string(pszFile), nLine); 
}

CSetRandDecorator::CSetRandDecorator(CTest *pTest) : 
   CTest("XXX"), // XXX remove name from CTest XXX 
   m_pTest(pTest) 
{
   assert(m_pTest != NULL); 
}

CSetRandDecorator::~CSetRandDecorator()
{
   delete m_pTest;
}


void CSetRandDecorator::run (CTestResult *pResult)
{
   unsigned int nSeed = (unsigned int)(rand()); 
   runWithSeed(nSeed, pResult);   
}

void CSetRandDecorator::runWithSeed(unsigned int nSeed, CTestResult *pResult)
{
   char szStr[256]; 
   sprintf(szStr, "Rand(%d)", int(nSeed)); 
   pResult->beginTest(szStr); 
   srand(nSeed); 
   m_pTest->run(pResult); 
   pResult->endTest();      
}

CTestRepeater::CTestRepeater(CTest *pTest, int nCount) : 
   CTest("Repeater"), 
   m_nCount(nCount), 
   m_pTest(pTest)
{
   assert(m_pTest != NULL); 
}

CTestRepeater::~CTestRepeater()
{
   delete m_pTest; 
}

void CTestRepeater::run(CTestResult *pResult)
{
   pResult->beginTest(name().c_str()); 
   for(int i=0;i<m_nCount; i++) 
      m_pTest->run(pResult); 
   pResult->endTest(); 
}




