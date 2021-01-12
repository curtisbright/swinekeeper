// file      : RegressionTestTest.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "RegressionTestTest.h"

#include "RegressionTest.h" 



class CRegressionTestTestContext : public CRegressionTestContext
{
public:
   CRegressionTestTestContext(); 
   virtual void transferInput(Storage::CSection inputSection); 
   virtual void transferOutput(Storage::CSection outputSection); 
   virtual bool initDefaultInput();
   void execTest(bool bCreateOutput); 
private:    
   int i1_s, i2_s; 
   int o1_s;
};

CRegressionTestTestContext::CRegressionTestTestContext() : 
   i1_s(-1), i2_s(-1), o1_s(-1)
{}

void CRegressionTestTestContext::transferInput(Storage::CSection inputSection)
{
   inputSection.transferItem("i1").transferInt(i1_s); 
   inputSection.transferItem("i2").transferInt(i2_s); 
}

void CRegressionTestTestContext::transferOutput(Storage::CSection outputSection)
{
   outputSection.transferItem("o1").transferInt(o1_s); 
}


bool CRegressionTestTestContext::initDefaultInput()
{
   i1_s = 10; 
   i2_s = 15; 
   return true;  
}


void CRegressionTestTestContext::execTest(bool bCreateOutput)
{
   int o1 = i1_s + i2_s; 
   if (!bCreateOutput) 
      {EXPECT(o1 == o1_s);}
   else 
      o1_s = o1; 
}



CRegressionTest *testCreateRegressionTestTest()
{
   return NEWREGCALLER("test.xml", CRegressionTestTestContext, CRegressionTestTestContext::execTest); 
}

