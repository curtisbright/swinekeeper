// MinePropRegTest.cpp: implementation of the CMinePropRegTest class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h" 
#include "MinePropRegTest.h"

#include <cassert>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "RegressionTest.h" 
#include <minesolver/CInputField.h>
#include <minesolver/CResultField.h>
#include <minebase/MineBaseSerialize.h>
#include <minesolver/CompProbabilities.h>

class CMinePropRegTestContext : public CRegressionTestContext
{
public:
    CMinePropRegTestContext();
    CMinePropRegTestContext(CMineArrayBase<CInputField> &inputArray, int nBombs) :
       m_InputArray(inputArray), m_nInputBombCount(nBombs) {}
      
    virtual ~CMinePropRegTestContext();
   virtual void transferInput(Storage::CSection inputSection); 
   virtual void transferOutput(Storage::CSection outputSection); 
   virtual bool initDefaultInput();
   void execTest(bool bCreateOutput); 
private: 
   CMineArrayBase<CInputField> m_InputArray; 
   int m_nInputBombCount; 

   CMineArrayBase<CResultField> m_OutputArray; 

};


CMinePropRegTestContext::CMinePropRegTestContext() : 
   m_nInputBombCount(0)
{

}

CMinePropRegTestContext::~CMinePropRegTestContext()
{

}

void CMinePropRegTestContext::transferInput(Storage::CSection inputSection)
{
   inputSection.transferItem("bomb-count").transferInt(m_nInputBombCount); 
   Storage::CSection arraySection; 
   inputSection.transferSection("array", arraySection); 
   transferDataCompact<CInputField>(arraySection, m_InputArray); 
}

void CMinePropRegTestContext::transferOutput(Storage::CSection outputSection)
{
   transferData<CResultField>(outputSection, m_OutputArray); 
}

bool CMinePropRegTestContext::initDefaultInput()
{
   return false; 
}

void CMinePropRegTestContext::execTest(bool bCreateOutput)
{
   CMineArrayBase<CResultField> outputArray; 
   bool bSuc = compProbabilities(outputArray, m_InputArray, m_nInputBombCount); 
   EXPECT(bSuc); 

   if (bCreateOutput) 
      m_OutputArray = outputArray; 
   else 
   {
      bool bEqual = CMineArrayBase<CResultField>::isEqualFunc(
         outputArray, 
         m_OutputArray, 
         CResultField::isProbabilityEqual); 
      EXPECT(bEqual); 
   }
}

CRegressionTest *testCreateMinePropRegTest()
{
   return NEWREGCALLER("CMinePropRegTestContext.xml", CMinePropRegTestContext, CMinePropRegTestContext::execTest); 
}

void createTest(const char *pszFilename, 
                const CMineArrayBase<CInputField> &inputField, 
                int nBombCount)
{
   CMineArrayBase<CInputField> inputFieldCopy(inputField); 
   CMinePropRegTestContext ctx(inputFieldCopy, nBombCount); 
   CRegressionTestCaller<CMinePropRegTestContext> caller(
      pszFilename, 
      pszFilename, 
      &CMinePropRegTestContext::execTest); 
   caller.createTest(ctx); 
}


