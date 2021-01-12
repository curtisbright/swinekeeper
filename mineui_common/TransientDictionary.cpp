// TransientDictionary.cpp: implementation of the CTransientDictionary class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h" 
#include "TransientDictionary.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransientDictionary::CTransientDictionary()
{

}

CTransientDictionary::~CTransientDictionary()
{

}

bool CTransientDictionary::getString(const char *szKey, std::string &val) const
{
   std::map<std::string, std::string>::const_iterator iter(m_map.find(szKey));
   if (iter != m_map.end()) 
   {
      val = iter->second; 
      return true; 
   }
   else 
   {
      return false; 
   }
}

bool CTransientDictionary::setString(const char *szKey, const std::string &val)
{
   m_map[std::string(szKey)] = val; 
   return true; 
}