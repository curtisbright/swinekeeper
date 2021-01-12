// RCFileDictionary.h: interface for the CRCFileDictionary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RCFILEDICTIONARY_H__FAA8F0FD_0457_4B85_B511_1CAE843E5F49__INCLUDED_)
#define AFX_RCFILEDICTIONARY_H__FAA8F0FD_0457_4B85_B511_1CAE843E5F49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CPersistentDictionary.h"
#include <string>
#include <iosfwd>
#include <map>

class CRCFileDictionary : public CPersistentDictionary  
{
public:
   CRCFileDictionary(const std::string &rcFilePath, const std::string &section);
   virtual ~CRCFileDictionary();

   bool startTransaction(); 
   bool endTransaction(); 

   bool verify(); 

   virtual bool getString(const char *szKey, std::string &val) const; 
   virtual bool setString(const char *szKey, const std::string &val); 

   static bool existFile(const std::string &file); 

private: 
   std::string m_rcFilePath; 
   std::string m_section; 
   std::map<std::string, std::string> m_map; 
   mutable bool m_bTransactionRunning; 
   mutable bool m_bNeedsWriting; 

   bool loadFromRCFile(); 
   bool saveToRCFile() const;
   static void stripSpaces(std::string &str);  
   static bool parseLine(const std::string &line, std::string &key, std::string &val); 

   bool writeDictionary(std::ostream &ostr) const; 
   static bool findTmpName(const std::string &nameBase, std::string &tmpName); 
};

#endif // !defined(AFX_RCFILEDICTIONARY_H__FAA8F0FD_0457_4B85_B511_1CAE843E5F49__INCLUDED_)




