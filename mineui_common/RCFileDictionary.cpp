// RCFileDictionary.cpp: implementation of the CRCFileDictionary class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h" 
#include "RCFileDictionary.h"
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>      

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRCFileDictionary::CRCFileDictionary(const std::string &rcFilePath, const std::string &section) : 
   m_rcFilePath(rcFilePath),
   m_section(section), 
   m_bTransactionRunning(false) 
{
   loadFromRCFile(); 
   saveToRCFile(); 
}

CRCFileDictionary::~CRCFileDictionary()
{

}

bool CRCFileDictionary::getString(const char *szKey, std::string &val) const 
{
   if (!m_bTransactionRunning) 
   {
      CRCFileDictionary *nonConstThis = const_cast<CRCFileDictionary*>(this); 

      if (!nonConstThis->loadFromRCFile()) 
         return false; 
   }

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
 
bool CRCFileDictionary::setString(const char *szKey, const std::string &val) 
{
   m_map[std::string(szKey)] = val; 

   if (!m_bTransactionRunning) 
   {
      if (!saveToRCFile()) 
         return false; 
   }
   else 
   {
      m_bNeedsWriting = true; 
   }

   return true; 
}

bool CRCFileDictionary::startTransaction()
{
   loadFromRCFile(); 
      
   m_bTransactionRunning = true; 
   m_bNeedsWriting = false; 

   return true; 
}

bool CRCFileDictionary::endTransaction()
{
   m_bTransactionRunning = false; 
   
   if (m_bNeedsWriting) 
      return saveToRCFile(); 
   else 
      return true; 
}

bool CRCFileDictionary::loadFromRCFile()
{
   std::ifstream instr(m_rcFilePath.c_str()); 
   std::string line; 
   bool bInSection(false); 

   std::string sectionStart = std::string("[") + m_section + std::string("]"); 

   while (std::getline(instr, line)) 
   {
      stripSpaces(line); 
      if (line == sectionStart) 
      {
         bInSection = true; 
      }
      else if (line[0] == '[') 
      {
         bInSection = false;    
      }
      if (bInSection) 
      {
         std::string key, val; 
         if (parseLine(line, key, val)) 
         {
            m_map[key] = val; 
         }     
      }
   }
   return true; 
}

bool CRCFileDictionary::existFile(const std::string &file)
{
    struct stat dummy;
    if (stat(file.c_str(), &dummy)==0) {
	return true; 
    } 
    else {
	return false;
    }
}

bool CRCFileDictionary::findTmpName(const std::string &nameBase, std::string &tmpName)
{
    for(int i=0;i<256;i++) {
	char szNum[16]; 
	sprintf(szNum, "%03d", i); 
	std::string name(nameBase + "_tmp_" + szNum);
	if (!existFile(name)) 
	{
	    tmpName = name; 
	    return true; 
	}
    }
    return false ;
}
 
bool CRCFileDictionary::saveToRCFile() const
{
   std::string tmpFileName; 
   if (!findTmpName(m_rcFilePath, tmpFileName)) 
       return false ;

   std::ofstream ostr(tmpFileName.c_str()); 
   if (!ostr) 
      return false; 

   std::ifstream instr(m_rcFilePath.c_str()); 
   std::string line; 
   bool bInSection(false); 
   bool bDictWritten(false); 

   std::string sectionStart = std::string("[") + m_section + std::string("]"); 

   while (std::getline(instr, line)) 
   {
      stripSpaces(line); 
      if (line == sectionStart) 
      {
         bInSection = true; 
         writeDictionary(ostr);
         bDictWritten = true; 
      }
      else if (line[0] == '[') 
      {
         bInSection = false;    
      }

      if (!bInSection) 
      {
         ostr << line; 
      }
   }

   if (!bDictWritten) 
   {
      writeDictionary(ostr);
   }

   if (ostr.bad())
   {
      remove(tmpFileName.c_str()); 
      return false; 
   }
   else 
   {
      ostr.close(); 
      instr.close();
      remove(m_rcFilePath.c_str()); 
      rename(tmpFileName.c_str(), m_rcFilePath.c_str()); 
      return true; 
   }
}

bool CRCFileDictionary::writeDictionary(std::ostream &ostr) const
{
   ostr << "[" << m_section << "]" << std::endl; 
   for(std::map<std::string, std::string>::const_iterator iter(m_map.begin()); iter != m_map.end(); iter++) 
   {
      ostr << iter->first << " = " << iter->second << std::endl; 
   }
   return !ostr.bad(); 
} 

void CRCFileDictionary::stripSpaces(std::string &str)
{
   std::string whitespace(" \t\r"); 
   std::string::size_type firstChar = str.find_first_not_of(whitespace); 
   std::string::size_type lastChar = str.find_last_not_of(whitespace); 
   if (firstChar == std::string::npos || lastChar == std::string::npos)
      return; 
   
   str = str.substr(firstChar, lastChar-firstChar+1); 
}

bool CRCFileDictionary::parseLine(const std::string &line, std::string &key, std::string &val)
{
   std::string::size_type firstAssig = line.find_first_of("="); 
   if (firstAssig == std::string::npos || firstAssig==0 || firstAssig==line.size()-1) 
      return false; 

   key = line.substr(0, firstAssig); stripSpaces(key); 
   val = line.substr(firstAssig+1, line.size() -(firstAssig+1)); stripSpaces(val); 

   if (key.empty()) 
      return false; 
   
   return true; 
}

bool CRCFileDictionary::verify()
{
   if (!setString("test", "JustToVerify"))
      return false; 

   std::string tmp; 
   if (!getString("test", tmp)) 
      return false; 

   if (tmp != "JustToVerify")
      return false; 

   return true; 
}
