// file      : CText.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#include "StdAfx.h"
#include "CText.h"

#include <cassert>
#include <cstdio>

using namespace Storage; 

CText::CText(const std::string &text)
{
   m_text = stripWS(text);
}


void CText::setString(const std::string &text) 
{
   m_text = stripWS(text);
   assert(isValidTextString(m_text)); 
}

void CText::setQuotedString(const std::string &text)
{
   setString("\"" + text + "\""); 
}

bool CText::getQuotedString(std::string &text)
{
   if (m_text.length() <= 2) 
      return false; 
   if (m_text[0] != '\"') 
      return false; 
   if (m_text[m_text.length()-1] != '\"') 
      return false; 

   text = m_text.substr(1, m_text.length()-2); 
   return true; 
}

bool CText::getInt(int &nVal) const
{
   int nTmpVal(-1); 
   int nFields = sscanf(m_text.c_str(), "%d", &nTmpVal); 
   if (nFields == 1) {
      nVal = nTmpVal; 
      return true; 
   }
   else {
      return false;
   }
}

bool CText::isValidInt() const
{
   int nDummy(-1); 
   return getInt(nDummy); 
}

int CText::getInt() const
{
   int nVal(0); 
   if (getInt(nVal)) 
      return nVal; 
   else 
      return 0; 
}

void CText::setInt(int nVal)
{
   char szStr[256]; 
   sprintf(szStr,"%d", nVal); 
   setString(std::string(szStr)); 
}


bool CText::getBool(bool &bVal) const
{
   if (m_text == "true") 
   {
      bVal = true; 
      return true; 
   }
   else if (m_text == "false") 
   {
      bVal = false; 
      return false; 
   }
   else 
   {
      return false; 
   }
}

bool CText::isValidBool() const
{
   bool bDummy(false); 
   return getBool(bDummy); 
   
}

bool CText::getBool() const
{
   bool bVal(false); 
   if (getBool(bVal)) 
      return bVal; 
   else 
      return false;
}

void CText::setBool(bool bVal)
{
   if (bVal) 
      setString(std::string("true")); 
   else 
      setString(std::string("false")); 
}

bool CText::isValidFloat() const
{
   double dDummy(0); 
   return getFloat(dDummy); 
}

double CText::getFloat() const
{
   double dVal(0); 
   if (getFloat(dVal)) 
      return dVal; 
   else 
      return 0; 
}

bool CText::getFloat(double &dV) const
{
   double dTmpVal(0); 
   int nFields = sscanf(m_text.c_str(), "%lf", &dTmpVal); 
   if (nFields == 1) {
      dV = dTmpVal; 
      return true; 
   }
   else {
      return false;
   }
}

void CText::setFloat(double dV)
{
   char szStr[256]; 
   sprintf(szStr,"%f", dV); 
   setString(std::string(szStr));    
}

std::string CText::stripWS(const std::string &str)
{
   unsigned int nBeginPos = str.find_first_not_of(" \n\t"); 
   if (nBeginPos == std::string::npos) nBeginPos = 0; 
   unsigned int nEndPos = str.find_last_not_of(" \n\t");
   if (nEndPos == std::string::npos)
      nEndPos = str.length(); 
   else 
      nEndPos++; 
   
   return str.substr(nBeginPos, nEndPos - nBeginPos); 
}

bool CText::isValidTextChar(char c)
{
   return    (isprint(c) || isspace(c)) 
          && (c&0x80)==0
          && c!='<' 
          && c!='>'
          && c!='&';  
}


bool CText::isValidTextString(const std::string &str)
{
   for(int i=0;i<int(str.length());i++) 
   {
      if (!isValidTextChar(str[i]))
         return false; 
   }

   if (str.length() == 0) 
      return false; 

   return true; 
}
