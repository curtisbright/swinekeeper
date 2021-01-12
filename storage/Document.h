// file      : Document.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#if !defined(AFX_STORAGE_H__20D2A073_8FFF_11D4_BF09_000000000000__INCLUDED_)
#define AFX_STORAGE_H__20D2A073_8FFF_11D4_BF09_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <list>
#include "CText.h"

namespace Storage {

class CTreeNode; 
class CTreeListNode;
class CText;  
class CTreeLeafNode; 

enum PropertyAttributes {
   PROP_STANDARD = 0,
   PROP_TRANSIENT = 1,
   PROP_OPTIONAL = 2, 
   PROP_READ_REQUIRED = 4 
}; 

/** 
 * A baseclass for classes that are used to convert arbitrary 
 * objects to strings and vice versa. 
 * See subclasses for examples 
 */ 
class CObjStringMap {
public: 
   virtual bool isValid(const std::string& )
   {
      std::string dummy; 
      return fromString(dummy); 
   }
   virtual bool toString(std::string &str)=0; 
   virtual bool fromString(const std::string &str)=0; 
}; 

/** 
 * A baseclass for classes that convert enums to strings and vice versa  
 */ 
class CEnumStringMap : public CObjStringMap {
   enum AnyEnum {VAL}; 

protected: 
   struct Map {
      AnyEnum m_nVal; 
      const char *pszTag; 
   }; 

public: 
   CEnumStringMap(AnyEnum *pEnumVal); 
   bool toString(std::string &str); 
   bool fromString(const std::string &str); 
private: 
   virtual void getMap(Map **pMap, int *nEntries)=0; 

   AnyEnum *m_pEnumVal; 
}; 

/** 
 * A class to log errors, 
 * still incomplete 
 */ 
class CErrorLog {
public: 
   CErrorLog() : m_nErrorCount(0) {}
   void pushTag(const char *pszTagName); 
   void popTag(); 
   void error();
   int errorCount() {return m_nErrorCount;}
private: 
   bool m_nErrorCount; 
}; 

/** 
 * A element of a document, 
 * Only for implementation inheritance with 
 * @see CItem, @see CSection 
 */ 
class CDocElement {
public: 
   CDocElement() : m_bCreateDoc(true), m_pLog(NULL), m_nAttr(PROP_STANDARD) {}
   CDocElement(bool bCreateDoc, CErrorLog *pLog) : 
      m_bCreateDoc(bCreateDoc), m_pLog(pLog), m_nAttr(PROP_STANDARD){}

   bool isTransferDocToObject() const {return !m_bCreateDoc;}

protected: 
   bool doCreateDoc() {return m_bCreateDoc;}
   bool error() {if (m_pLog) m_pLog->error(); return false;}
   void makeOptional() {m_nAttr |= PROP_OPTIONAL;}
private: 
   bool m_bCreateDoc;       
   CErrorLog *m_pLog;    
   int m_nAttr; 
}; 

/** 
 * A leaf item of a document, storing a single value 
 * e.g. <height>12.21</height>
 */ 
class CItem : public CDocElement {
   friend class CSection; 
   friend class CDocument; 
   CItem(CTreeLeafNode *pLeaf, bool bCreateDoc, CErrorLog *pLog) : 
      CDocElement(bCreateDoc, pLog), 
      m_pLeaf(pLeaf) {}
   CItem(CTreeLeafNode *pLeaf, const CDocElement &parent) : 
      CDocElement(parent), 
      m_pLeaf(pLeaf) {}
public: 
   CItem() : m_pLeaf(NULL) {}
   void setString(const std::string& string); 
   void setInt(int nVal); 
   void setBool(bool bVal); 
   void setQuotedString(const std::string &string); 
   bool setConv(CObjStringMap &conv); 
   void setFloat(double dVal); 

   bool getString(std::string &string); 
   bool getInt(int &nVal); 
   bool getBool(bool &bVal);
   bool getQuotedString(std::string &string); 
   bool getConv(CObjStringMap &conv); 
   bool getFloat(double &dVal); 
       
   void transferString(std::string &string); 
   void transferInt(int &nVal); 
   void transferBool(bool &bVal); 
   void transferQuotedString(std::string &string); 
   void transferConv(CObjStringMap &conv); 
   void transferFloat(double &dVal); 

   void transfer(int &nVal) {transferInt(nVal);}
   void transfer(bool &bVal) {transferBool(bVal);}
   void transfer(std::string &string) {transferQuotedString(string);}

   bool isValid() {return m_pLeaf != NULL;}   

   CItem optional() {makeOptional(); return *this;}

private: 
   CTreeLeafNode *m_pLeaf;  
}; 

class CSection  : public CDocElement {
   friend class CDocument; 
   CSection(CTreeListNode *pList, bool bCreateDoc, CErrorLog *pLog) : 
      CDocElement(bCreateDoc, pLog), 
      m_pList(pList) {}
   CSection(CTreeListNode *pList, const CDocElement &parent) : 
      CDocElement(parent), 
      m_pList(pList) {}
public: 
   CSection() : m_pList(NULL) {}
   CItem addItem(const char *pszTagName); 

   CSection addSection(const char *pszTagName);
   CSection addClonedSection(const char *pszTagName, CSection section); 

   bool findSection(const char *pszTagName, CSection &newSection);
   CItem findItem(const char *pszTagName); 

   void findSections(const char *pszTagName, std::list<CSection>& sections); 
   void findItems(const char *pszTagName, std::list<CItem> &items); 

   CItem transferItem(const char *pszTagName); 
   bool transferSection(const char *pszTagName, CSection &section); 

   CItem transferOptionalItem(const char *pszTagName, bool &bHasVal); 

   bool isValid() {return m_pList != NULL;}   
private: 
   CTreeListNode *m_pList; 
}; 

/** 
 * A XML like document 
 */ 
class CDocument {
   class CErrorLog; 

public: 
   CDocument() : m_pRoot(NULL) {}
   CDocument(const char *pszTagName);
   ~CDocument();
   bool serialize(std::string &str) const; 
   bool initFromString(const std::string &str);
   void initEmpty(const std::string &rootTagName);

   CSection rootSection(bool bCreateDoc = true); 
   CSection rootSectionForRead() {return rootSection(false);}
   CSection rootSectionForWrite() {return rootSection(true);}

   bool saveDoc(const char *pszFilename); 
   bool loadDoc(const char *pszFilename); 

private: 
   CTreeListNode *m_pRoot;  
   CDocument(const CDocument&); 
   CDocument& operator=(const CDocument&); 
}; 

}

#endif // !defined(AFX_STORAGE_H__20D2A073_8FFF_11D4_BF09_000000000000__INCLUDED_)
