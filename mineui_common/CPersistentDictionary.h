// file      : CPersistentDictionary.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#if !defined(AFX_PERSISTENTDICTIONARY_H__B0A5E1C5_80C2_11D4_BEF8_000000000000__INCLUDED_)
#define AFX_PERSISTENTDICTIONARY_H__B0A5E1C5_80C2_11D4_BEF8_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

/** 
 * A dictionary that is persistent across different invocations of 
 * the program
 */ 
class CPersistentDictionary  
{
public:
   CPersistentDictionary();
   virtual ~CPersistentDictionary();

   virtual bool getString(const char *szKey, std::string &val) const =0 ; 
   virtual bool setString(const char *szKey, const std::string &val)=0; 

   virtual bool getInt(const char *szKey, int &nVal) const; 
   virtual bool setInt(const char *szKey, int nVal);

   virtual bool getBool(const char *szKey, bool &bVal) const; 
   virtual bool setBool(const char *szKey, bool bVal); 

};

#endif // !defined(AFX_PERSISTENTDICTIONARY_H__B0A5E1C5_80C2_11D4_BEF8_000000000000__INCLUDED_)
