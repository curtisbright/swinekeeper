// file      : RegressionTest.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#if !defined(AFX_REGRESSIONTEST_H__F492C130_98A7_11D4_BF13_000000000000__INCLUDED_)
#define AFX_REGRESSIONTEST_H__F492C130_98A7_11D4_BF13_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TestFramework.h" 
#include <storage/Document.h>
#include <cassert>
#include <cstdio>

class CRegressionTestContext : public CTestContextBase {
public: 
   virtual void transferInput(Storage::CSection inputSection)=0; 
   virtual void transferOutput(Storage::CSection outputSection)=0; 
   virtual bool initDefaultInput() {return false;}   
}; 

/** 
 * This class executes a regression test. 
 * 
 * Up to now it is not fully implemented, it might change in the future.
 */ 
template <typename CONTEXT>
class CRegressionTestCaller : public CRegressionTest
{
public:
   typedef void (CONTEXT::*RegTestMethodType)(bool bDoCreateOutput = false);
   CRegressionTestCaller(const char *pszFile, const char *pszName, RegTestMethodType pfTestMethod); 
   bool createTest(Storage::CSection inFile); 
   bool createTest(CONTEXT &ctx); 
   bool createTest(); 
   bool createTestFromFile(const char *pszFile); 
   void run(CTestResult *result);
#define NEWREGCALLER(FILE, CLASS, FCT) (new CRegressionTestCaller<CLASS>(FILE, #FCT, (&FCT)))
private: 
   std::string m_filename; 
   RegTestMethodType m_pfTestMethod;
};

template <typename CONTEXT>
CRegressionTestCaller<CONTEXT>::CRegressionTestCaller(
   const char *pszFile, 
   const char *pszName, 
   RegTestMethodType pfTestMethod) : 
      CRegressionTest(pszName), 
      m_filename(pszFile), 
      m_pfTestMethod(pfTestMethod) 
{

}
 
template <typename CONTEXT>
bool CRegressionTestCaller<CONTEXT>::createTest(Storage::CSection inFile)
{
   CONTEXT ctx; 

   ctx.transferInput(inFile); 

   return createTest(ctx); 
}

template <typename CONTEXT>
bool CRegressionTestCaller<CONTEXT>::createTest()
{
   CONTEXT ctx; 
   if (!ctx.initDefaultInput()) 
      return false; 

   return createTest(ctx); 

}

template <typename CONTEXT>
bool CRegressionTestCaller<CONTEXT>::createTestFromFile(const char *pszFile)
{
   Storage::CDocument doc; 
   if (!doc.loadDoc(pszFile)) 
      return false; 
   return createTest(doc.rootSection(false));  
}


template <typename CONTEXT>
bool CRegressionTestCaller<CONTEXT>::createTest(CONTEXT &ctx)
{
   try 
   {
      (ctx.*m_pfTestMethod)(true); 
   }
   catch(...) 
   {
      return false; 
   }

   Storage::CDocument doc("regressiontest");
   Storage::CSection root =  doc.rootSection(true); 

   Storage::CSection infoSection = root.addSection("meta"); 
   infoSection.addItem("name").setString(name()); 

   Storage::CSection inSection = root.addSection("in"); 
   ctx.transferInput(inSection); 

   Storage::CSection outSection = root.addSection("out"); 
   ctx.transferOutput(outSection); 

   FILE *pFile = fopen(m_filename.c_str(), "wt"); 
   if (!pFile) 
      return false; 

   std::string str; 
   doc.serialize(str); 

   int nSuc = fputs(str.c_str(), pFile); 
   fclose(pFile); 
   if (nSuc < 0) {return false;}
   return true; 
}


template <typename CONTEXT>
void CRegressionTestCaller<CONTEXT>::run(CTestResult *pResult) 
{
   FILE *pFile = fopen(m_filename.c_str(), "rt"); 
   if (!pFile) 
   {
      createTest(Storage::CSection()); 
      pFile = fopen(m_filename.c_str(), "rt"); 
      pResult->addMessage(std::string("Created test case ") + m_filename); 
   }

   if (!pFile) 
   {
      pResult->addMessage(std::string("Failed to open File ") + m_filename); 
      return; 
   }

   std::string docStr; 
   char szTmp[256]; 
   while (fgets(szTmp, 256, pFile))    
   {
      docStr += std::string(szTmp); 
   }
   fclose(pFile); 

   Storage::CDocument doc; 
   if (!doc.initFromString(docStr)) 
   {
      pResult->addMessage(std::string("Can't read file")); 
      return; 
   }

   Storage::CSection rootSection = doc.rootSection(false); 
   
   Storage::CSection inSection, outSection; 

   if (!rootSection.findSection("in", inSection)) 
   {
      pResult->addMessage(std::string("No in-section")); 
      return; 
   }

   if (!rootSection.findSection("out", outSection)) 
   {
      pResult->addMessage(std::string("No out-section")); 
      return; 
   }

   pResult->beginTest(name().c_str()); 
   pResult->incTestCount();
   CONTEXT ctx; 
   ctx.transferInput(inSection); 
   ctx.transferOutput(outSection); 

   try 
   {
      (ctx.*m_pfTestMethod)(false); 
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


#endif // !defined(AFX_REGRESSIONTEST_H__F492C130_98A7_11D4_BF13_000000000000__INCLUDED_)
