// file      : CPersistentDictionary.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#include "StdAfx.h" 
#include "CPersistentDictionary.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPersistentDictionary::CPersistentDictionary()
{

}

CPersistentDictionary::~CPersistentDictionary()
{

}

/** 
 * Queries a string from the dictionary. 
 * 
 * @param szKey key of the queried entry 
 * @param val Queried value. Trailing and leading spaces will be removed. 
 *            If the key is not in the dictionary, this value is not modified. 
 * @return true if the key has been found in the dictionary 
 * 
 */ 
bool CPersistentDictionary::getString(const char * /*szKey*/, std::string &/*val*/) const
{
   return false; 
}

/** 
 * Saves a string in the dictionary 
 * 
 * A empty string indicates no entry for the key. 
1* 
 * @return true if the function was successful 
 */ 
bool CPersistentDictionary::setString(const char * /*szKey*/, const std::string &/*val*/)
{
   return false; 
}

/** 
 * Query an integer from the dictionary. 
 *
 * Subclasses may override the default implementation. 
 * @see CPersistentDictionary::getString. 
 *
 */ 
bool CPersistentDictionary::getInt(const char *szKey, int &nVal) const
{
   std::string strVal; 
   if (!getString(szKey, strVal))
      return false; 
   int nTmpVal = 0; 
   int nFields = sscanf(strVal.c_str(), "%d", &nTmpVal); 
   if (nFields != 1) 
      return false; 
   nVal = nTmpVal; 
   return true; 
}

/** 
 * Save a integer in the dictionary 
 * @see CPersistentDictionary::setString. 
 */ 
bool CPersistentDictionary::setInt(const char *szKey, int nVal)
{
   char szTmp[100]; 
   sprintf(szTmp, "%d", nVal); 
   return setString(szKey, szTmp); 
}

/** 
 * Query a boolean value from the dictionary. 
 * @see CPersistentDictionary::getString. 
 */ 
bool CPersistentDictionary::getBool(const char *szKey, bool &bVal) const
{
   std::string strVal; 
   if (!getString(szKey, strVal)) 
      return false; 
       
   for(int i=0;i<int(strVal.size());i++) 
      strVal[i] = tolower(strVal[i]); 

   if (strVal == std::string("false") || strVal == std::string("0")) 
   {
      bVal = false; 
      return true; 
   }
   else if (strVal == std::string("true") || strVal == std::string("1"))
   {
      bVal = true;  
      return true; 
   }
   else 
   {
      return false; 
   }
}

/** 
 * Save a boolean value in the dictionary 
 * @see CPersistentDictionary::setString. 
 */ 
bool CPersistentDictionary::setBool(const char *szKey, bool bVal)
{
   std::string strVal; 
   if (bVal) 
      strVal = std::string("true"); 
   else 
      strVal = std::string("false"); 

  return setString(szKey, strVal); 
}












