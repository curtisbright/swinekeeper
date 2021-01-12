// file      : CPersistentDictWin.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#if !defined(AFX_CPERSISTENTDICTWIN_H__B0A5E1C8_80C2_11D4_BEF8_000000000000__INCLUDED_)
#define AFX_CPERSISTENTDICTWIN_H__B0A5E1C8_80C2_11D4_BEF8_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mineui_common/CPersistentDictionary.h>

class CPersistentDictWin : public CPersistentDictionary
{
public:
   CPersistentDictWin(const char *pszIniFileName, const char *pszIniFileSection);
   virtual ~CPersistentDictWin();

   virtual bool getString(const char *szKey, std::string &val) const; 
   virtual bool setString(const char *szKey, const std::string &val); 
private: 
   std::string m_iniFileName; 
   std::string m_iniFileSection; 

};

#endif // !defined(AFX_CPERSISTENTDICTWIN_H__B0A5E1C8_80C2_11D4_BEF8_000000000000__INCLUDED_)
