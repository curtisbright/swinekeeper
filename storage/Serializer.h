// file      : Serializer.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#if !defined(AFX_SERIALIZER_H__C0F01234_931F_11D4_BF0C_000000000000__INCLUDED_)
#define AFX_SERIALIZER_H__C0F01234_931F_11D4_BF0C_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

namespace Storage {
class CTreeListNode; 
class CTreeNode; 

class CSerializer {
public: 
   bool readTree(const std::string &str, CTreeListNode **ppNode); 
   bool writeTree(std::string &str, const CTreeListNode *pNode); 
   
private: 

   struct Stream {
      Stream(const std::string str) : m_str(str), m_nCurPos(0) {}
      void skipWhiteSpace(); 
      bool isEnd() const; 
      void skipChar(); 
      char nextChar() const; 
      std::string readUntilXMLToken(); 
   
      enum XMLToken {
         XML_BEGIN_TOKENS = 0, 
         XML_OPEN_END=0,    // </ (longer tokens first!) 
         XML_OPEN_BEGIN=1,  // <
         XML_CLOSE=2,       // >
         XML_END_TOKENS=3, 
         XML_NO_TOKEN=3, 
         XML_INVALID=4
      }; 
   
      XMLToken readXMLToken(); 

   private: 
      std::string m_str; 
      unsigned int m_nCurPos; 
      bool isClassValid() const; 

      // indexed by XMLToken
      static const char *ppszTokenStr[]; 
   }; 

   struct XMLTag {
      XMLTag() : m_bIsTag(false), m_bIsEndTag(false) {}
      void makeTextToken(const std::string& str) {m_str = str; m_bIsTag = false;}
      void makeTagToken(const std::string& name, bool bEnd) 
         {m_str = name; m_bIsTag = true; m_bIsEndTag = bEnd;}
      bool isTag() const {return m_bIsTag;}
      bool isBeginTag() const {return m_bIsTag && !m_bIsEndTag;}
      bool isEndTag() const {return m_bIsTag && m_bIsEndTag;}
      std::string string() const {return m_str;}
   private: 
      bool m_bIsTag; 
      bool m_bIsEndTag; 
      std::string m_str; 
   }; 

   bool readSubTree(Stream &stream, const XMLTag &beginToken, CTreeNode **ppNode); 
   void writeSubTree(std::string &str, const CTreeNode *pNode, int nDepth) const; 
   bool readXMLTag(Stream &stream, XMLTag &token); 

   static std::string space(int nIndentDepth);
}; 


}

#endif // !defined(AFX_SERIALIZER_H__C0F01234_931F_11D4_BF0C_000000000000__INCLUDED_)
