// CTerminator.cpp: implementation of the CTerminator class.
//
//////////////////////////////////////////////////////////////////////

#include "CTerminator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTerminator::CTerminator() : 
   m_bDoTerminate(false) 
{

}

CTerminator::~CTerminator()
{

}

bool CTerminator::doTerminate() 
{
   if (!m_bDoTerminate) 
   {
      m_bDoTerminate = checkTerminate(); 
   }
     
   return m_bDoTerminate;
} 

