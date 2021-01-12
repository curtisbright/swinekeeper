// MinePropRegTest.h: interface for the CMinePropRegTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MINEPROPREGTEST_H__E8505EB1_BD6D_11D4_BF45_000000000000__INCLUDED_)
#define AFX_MINEPROPREGTEST_H__E8505EB1_BD6D_11D4_BF45_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegressionTest; 

class CInputField;
template<class CInputField> class CMineArrayBase;

CRegressionTest *testCreateMinePropRegTest(); 

void createTest(const char *pszFilename, 
                const CMineArrayBase<CInputField> &inputField, 
                int nBombCount); 


#endif // !defined(AFX_MINEPROPREGTEST_H__E8505EB1_BD6D_11D4_BF45_000000000000__INCLUDED_)
