// CTerminatorEsc.h: interface for the CTerminatorEsc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTERMINATORESC_H__6B3F6705_1C99_11D5_BFAB_000000000000__INCLUDED_)
#define AFX_CTERMINATORESC_H__6B3F6705_1C99_11D5_BFAB_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <minesolver/CTerminator.h>

class CTerminatorEsc : public CTerminator
{
private:
   bool checkTerminate(); 
};

#endif // !defined(AFX_CTERMINATORESC_H__6B3F6705_1C99_11D5_BFAB_000000000000__INCLUDED_)
