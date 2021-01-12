// file      : TestFramework.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#if !defined(AFX_TESTRESULT_H__A622DDB5_72B5_11D4_BEDE_000000000000__INCLUDED_)
#define AFX_TESTRESULT_H__A622DDB5_72B5_11D4_BEDE_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#pragma warning (disable:4786) // identifier was truncated to '255' characters in the debug information
#endif // _MSC_VER > 1000

#include <string>
#include <deque>

#define CLASS_WITHOUT_COPYOP(CLASS_) private: CLASS_(const CLASS_&); const CLASS_& operator=(const CLASS_ &); 

// General Description: 
// The classes in this file constitute a framework for the
// implementation of tests. 
// The framework is implemented according to the CppUnit Testing Framework 
// from Michael Feathers. (look e.g. at www.xprogramming.com) 

void DbgPrint(const char *psz); 

/** 
 * A Exception that is thrown when a test fails 
 */ 
class CTestException {

public: 
   CTestException(); 
   CTestException(
      const std::string &msg, 
      const std::string &file, 
      int nLine); 
   virtual ~CTestException() {}

   std::string message() const; 
   std::string filename() const; 
   int fileline() const; 
           
private: 
   std::string m_message;

   std::string m_fileName;   
   int m_lineNumber;
}; 

/** 
 * A class that logs the failed tests
 */ 
class CTestResult  
{
   struct CFailedTest {
      std::string m_testName; 
      CTestException m_exception; 
   }; 

public:
   CTestResult();
   virtual ~CTestResult();
   virtual void testFailed(const CTestException &e);
   virtual void addMessage(const std::string &str); 
   virtual int errorCount() const;
   virtual bool success() const;
   virtual void beginTest(const std::string &testName); 
   virtual void endTest(); 
   virtual void incTestCount(); 

   void printLog() const; 
private: 
   std::string curTestDesc() const; 

   std::deque<CFailedTest> m_failedTests; 
   std::deque<std::string> m_testNameStack; 
   typedef std::deque<CFailedTest>::const_iterator FailedTestIter; 

   int m_nTestCount; 
};

/** 
 * Base class for all tests
 */ 
class CTest {
public:
   CTest(const char *pszName); 
   virtual ~CTest ();

   virtual void run (CTestResult *result) = 0;
protected: 
   std::string name();
private: 
   std::string m_name; // XXX just for convenience of subclasses XXX 
}; 

namespace Storage { class CSection;}

class CRegressionTest : public CTest 
{
public: 
   CRegressionTest(const char *pszName); 
   virtual bool createTest(Storage::CSection inFile)=0; 
   virtual bool createTestFromFile(const char *pszFile)=0; 

}; 

/** 
 * A composite of tests. 
 */ 
class CTestSet : public CTest {
   CLASS_WITHOUT_COPYOP(CTestSet) 
public: 
   CTestSet(const char *pszName); 
   ~CTestSet(); 
   void run (CTestResult *result);
   void addTest(CTest *); 
private: 
   std::deque<CTest*> m_tests; 
   typedef std::deque<CTest*>::iterator TestsIter; 
}; 

class CTestContextBase {
public: 
   void expect(bool expr, const char *pszExpr, const char *pszFile, int nLine); 
#define EXPECT(expr) expect(expr, #expr, __FILE__, __LINE__); 
}; 

/** 
 * Subclasses of this class will contain the test code. 
 * The class provides auxillary functions for this test code
 */ 
class CTestContext : public CTestContextBase {
}; 

/** 
 * Invokes a single test function that is defined in a 
 * @ref CTestContext 
 */ 
template <typename CONTEXT>
class CTestCaller : public CTest 
{
public: 
   typedef void (CONTEXT::*TestMethodType)();
   CTestCaller(const char *pszName, TestMethodType pfTestMethod); 
   void run (CTestResult *result);
#define NEWCALLER(CLASS, FCT) (new CTestCaller<CLASS>(#FCT, (FCT)))
private: 
   TestMethodType m_pfTestMethod; 
}; 

template <typename CONTEXT>
CTestCaller<CONTEXT>::CTestCaller(const char *pszName, TestMethodType pfTestMethod) : 
   CTest(pszName), 
   m_pfTestMethod(pfTestMethod) 
{
}

template <typename CONTEXT>
void CTestCaller<CONTEXT>::run(CTestResult *pResult)
{  
   pResult->beginTest(name().c_str()); 
   pResult->incTestCount();
   CONTEXT ctx; 
   try 
   {
      (ctx.*m_pfTestMethod)(); 
   }
   catch(CTestException &except) 
   {
      pResult->testFailed(except); 
   }
   catch(...) 
   {
      CTestException e("Unknown Exception", "", 0); 
      pResult->testFailed(e); 
   }
   pResult->endTest(); 
}

/** 
 * Sets the seed of the crt random number generator 
 * before executing the child test. 
 * The seed itself is described in the test name : rand(SEED)
 */ 
class CSetRandDecorator : public CTest 
{
   CLASS_WITHOUT_COPYOP(CSetRandDecorator) 
public: 
   CSetRandDecorator(CTest *pTest); 
   ~CSetRandDecorator(); 
   void run (CTestResult *result);
   void runWithSeed(unsigned int nSeed, CTestResult *result);
private: 
   CTest *m_pTest; 
}; 

class CTestRepeater : public CTest 
{
   CLASS_WITHOUT_COPYOP(CTestRepeater) 
public: 
   CTestRepeater(CTest *pTest, int nCount); 
   ~CTestRepeater(); 
   void run (CTestResult *result);
private: 
   int m_nCount; 
   CTest *m_pTest; 
}; 

#endif // !defined(AFX_TESTRESULT_H__A622DDB5_72B5_11D4_BEDE_000000000000__INCLUDED_)
