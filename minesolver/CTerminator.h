// CTerminator.h: interface for the CTerminator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTERMINATOR_H__6B3F6701_1C99_11D5_BFAB_000000000000__INCLUDED_)
#define AFX_CTERMINATOR_H__6B3F6701_1C99_11D5_BFAB_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTerminator  
{
public:
   CTerminator();
   virtual ~CTerminator();

   bool doTerminate(); 
private: 
   virtual bool checkTerminate() = 0; 
 
   bool m_bDoTerminate; 
};

#endif // !defined(AFX_CTERMINATOR_H__6B3F6701_1C99_11D5_BFAB_000000000000__INCLUDED_)
