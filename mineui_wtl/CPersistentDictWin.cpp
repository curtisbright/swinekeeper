// file      : CPersistentDictWin.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#include "StdAfx.h" 
#include "CPersistentDictWin.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPersistentDictWin::CPersistentDictWin(const char *pszIniFileName, const char *pszIniFileSection) : 
   m_iniFileName(pszIniFileName), 
   m_iniFileSection(pszIniFileSection)
{

}

CPersistentDictWin::~CPersistentDictWin()
{

}

bool CPersistentDictWin::getString(const char *szKey, std::string &val) const
{
   char szTmp[1024]; 
   DWORD nCopiedChars = 
      GetPrivateProfileString(
         m_iniFileSection.c_str(), 
         szKey, 
         "", 
         szTmp, 1024,
         m_iniFileName.c_str()); 
   if (nCopiedChars == 0) 
      return false; 

   val = std::string(szTmp);          

   return true; 
}

bool CPersistentDictWin::setString(const char *szKey, const std::string &val)
{
   BOOL bSuc = WritePrivateProfileString(
      m_iniFileSection.c_str(), 
      szKey, 
      val.c_str(),
      m_iniFileName.c_str()); 
   return (bSuc!=0); 
}


/* 
   UINT uInt = GetPrivateProfileInt(
      szIniFileScoreSection, 
      szKey, 
      static_cast<UINT>(nVal),
      szIniFileName);
   nVal = int(uInt); 
*/ 
