// TransientDictionary.h: interface for the CTransientDictionary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSIENTDICTIONARY_H__E47EF3C9_C6A0_490D_B461_EF8BE5163430__INCLUDED_)
#define AFX_TRANSIENTDICTIONARY_H__E47EF3C9_C6A0_490D_B461_EF8BE5163430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mineui_common/CPersistentDictionary.h>
#include <string>
#include <map>

class CTransientDictionary : public CPersistentDictionary  
{
public:
   CTransientDictionary();
   virtual ~CTransientDictionary();

   virtual bool getString(const char *szKey, std::string &val) const; 
   virtual bool setString(const char *szKey, const std::string &val); 

private: 
   std::map<std::string, std::string> m_map; 
};

#endif // !defined(AFX_TRANSIENTDICTIONARY_H__E47EF3C9_C6A0_490D_B461_EF8BE5163430__INCLUDED_)
