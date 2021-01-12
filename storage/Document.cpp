// file      : Document.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#include "StdAfx.h"
#include "Document.h"

#include <cassert>
#include "Tree.h"
#include "Serializer.h" 
#include <cstdio>

namespace Storage {


CEnumStringMap::CEnumStringMap(AnyEnum *pEnumVal) : 
   m_pEnumVal(pEnumVal)
{
}

bool CEnumStringMap::toString(std::string &str)
{
   Map *pMap = NULL; 
   int nEntries(0); 
   getMap(&pMap, &nEntries); 

   for(int i=0;i<nEntries;i++) 
   {
      if (*m_pEnumVal == pMap[i].m_nVal)
      {
         str = pMap[i].pszTag; 
         return true; 
      }
   }
   return false; 
}

bool CEnumStringMap::fromString(const std::string &str)
{
   Map *pMap = NULL; 
   int nEntries(0); 
   getMap(&pMap, &nEntries); 

   for(int i=0;i<nEntries;i++) 
   {
      if (str == pMap[i].pszTag)
      {
         *m_pEnumVal = pMap[i].m_nVal;  
         return true; 
      }
   }
   return false; 
   
}

CSection CDocument::rootSection(bool bCreateDoc) 
{
   assert(m_pRoot); return CSection(m_pRoot, bCreateDoc, NULL);
}



CDocument::~CDocument() 
{
   delete m_pRoot; 
}  


void CDocument::initEmpty(const std::string &rootTagName) {
   assert(m_pRoot == NULL); 
   m_pRoot = new CTreeListNode(rootTagName); 
}

CDocument::CDocument(const char *pszTagName) : m_pRoot(NULL) {
   initEmpty(std::string(pszTagName)); 
}

bool CDocument::serialize(std::string &str) const
{
   assert(m_pRoot); 
   CSerializer serializer;  
   return serializer.writeTree(str, m_pRoot); 
}

bool CDocument::initFromString(const std::string &str)
{
   assert(!m_pRoot); 
   
   CTreeListNode *pNode = NULL;
   CSerializer serializer;  
   if (!serializer.readTree(str, &pNode))
      return false; 

   m_pRoot = pNode; 

   return true; 
}

bool CDocument::saveDoc(const char *pszFilename)
{
   std::string str; 
   if (!serialize(str)) 
      return false; 

   FILE *pFile = fopen(pszFilename, "wt"); 
   if (!pFile) 
      return false; 

   int nSuc = fputs(str.c_str(), pFile); 
   fclose(pFile); 
   if (nSuc < 0) 
      return false;
   
   return true; 
}

bool CDocument::loadDoc(const char *pszFilename)
{
   std::string docStr; 
   char szTmp[256]; 

   FILE *pFile = fopen(pszFilename, "rt"); 
   if (!pFile) 
      return false; 

   while (fgets(szTmp, 256, pFile))    
   {
      docStr += std::string(szTmp); 
   }
   fclose(pFile); 

   if (!initFromString(docStr)) 
   {
      return false; 
   }
   return true; 
}


void CItem::setString(const std::string& string)
{
   if (!isValid()) return; 
   m_pLeaf->setText(CText(string)); 
}

void CItem::setInt(int nVal)
{
   if (!isValid()) return; 
   m_pLeaf->setText(CText(nVal)); 
}

void CItem::setBool(bool bVal)
{
   if (!isValid()) return; 
   m_pLeaf->setText(CText(bVal)); 
}

void CItem::setQuotedString(const std::string &string)
{
   if (!isValid()) return; 
   CText text; 
   text.setQuotedString(string); 
   m_pLeaf->setText(text); 
}

bool CItem::setConv(CObjStringMap& conv)
{
   if (!isValid()) return false; 
   std::string str; 
   if (!conv.toString(str)) 
      return false; 
   setString(str); 
   return true; 
}

void CItem::setFloat(double dVal)
{
   if (!isValid()) return; 
   CText text; 
   text.setFloat(dVal); 
   m_pLeaf->setText(text); 
}

bool CItem::getString(std::string &string)
{
   if (!isValid()) return false; 
   CText text = m_pLeaf->getText(); 
   string = text.getString(); 
   return true; 
}

bool CItem::getInt(int &nVal)
{
   if (!isValid()) return false; 
   CText text = m_pLeaf->getText(); 
   return text.getInt(nVal); 
}

bool CItem::getBool(bool &bVal)
{
   if (!isValid()) return false; 
   CText text = m_pLeaf->getText(); 
   return text.getBool(bVal); 
}

bool CItem::getQuotedString(std::string &string)
{
   if (!isValid()) return false; 
   CText text = m_pLeaf->getText(); 
   return text.getQuotedString(string); 
}

bool CItem::getConv(CObjStringMap& conv)
{
   if (!isValid()) return false; 
   std::string str; 
   if (!getString(str)) 
      return false; 
   if (!conv.fromString(str)) 
      return false; 
   return true;    
}

bool CItem::getFloat(double &dVal)
{
   if (!isValid()) return false; 
   CText text = m_pLeaf->getText(); 
   return text.getFloat(dVal); 
}

void CItem::transferString(std::string &string)
{
   if (!isValid()) return; 
   if (doCreateDoc())
      setString(string); 
   else 
      getString(string) || error(); 
}

void CItem::transferInt(int &nVal)
{
   if (!isValid()) return; 
   if (doCreateDoc())
      setInt(nVal); 
   else 
      getInt(nVal) || error(); 
}

void CItem::transferBool(bool &bVal)
{
   if (!isValid()) return; 
   if (doCreateDoc())
      setBool(bVal); 
   else 
      getBool(bVal) || error(); 
}

void CItem::transferQuotedString(std::string &string)
{
   if (!isValid()) return; 
   if (doCreateDoc())
      setQuotedString(string); 
   else 
      getQuotedString(string) || error(); 
}

void CItem::transferConv(CObjStringMap &conv)
{
   if (!isValid()) return; 
   if (doCreateDoc())
      setConv(conv) || error();  
   else 
      getConv(conv) || error(); 
}

void CItem::transferFloat(double &dVal)
{
   if (!isValid()) return; 
   if (doCreateDoc())
      setFloat(dVal);  
   else 
      getFloat(dVal) || error(); 
}


CItem CSection::addItem(const char *pszTagName)
{
   if (!isValid()) return CItem(); 
   CTreeLeafNode *pLeafNode = new CTreeLeafNode(std::string(pszTagName)); 
   m_pList->addChild(pLeafNode); 
   return CItem(pLeafNode, *this); 
}

CSection CSection::addSection(const char *pszTagName) 
{
   if (!isValid()) return CSection(); 
   CTreeListNode *pNewList = new CTreeListNode(std::string(pszTagName)); 
   m_pList->addChild(pNewList); 
   return CSection(pNewList, *this); 
}

CSection CSection::addClonedSection(const char *pszTagName, CSection section)
{
   if (!isValid()) return CSection(); 
   CTreeListNode *pNewList = static_cast<CTreeListNode*>(section.m_pList->clone()); 
   pNewList->setTagName(pszTagName); 
   m_pList->addChild(pNewList); 
   return CSection(pNewList, *this); 
}


bool CSection::findSection(const char *pszTagName, CSection &newSection) 
{
   if (!isValid()) return false; 
   CTreeNode *pNode = m_pList->findFirstChild(std::string(pszTagName)); 
   if (!pNode || pNode->isLeaf()) 
      return false; 
   newSection = CSection(static_cast<CTreeListNode*>(pNode), *this);
   return true;  
} 

void CSection::findSections(const char *pszTagName, std::list<CSection>& sections)
{
   if (!isValid()) return; 
   std::list<CTreeNode*> nodes; 
   m_pList->findChildren(std::string(pszTagName), nodes); 
   for(std::list<CTreeNode*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++) 
   {
      CTreeNode *pNode = (*iter); 
      if (!pNode->isLeaf()) 
      { 
         sections.push_back(CSection(static_cast<CTreeListNode*>(pNode), *this));    
      }
   }
}

CItem CSection::findItem(const char *pszTagName)
{
   if (!isValid()) return CItem(); 
   CTreeNode *pNode = m_pList->findFirstChild(std::string(pszTagName)); 
   if (!pNode || !pNode->isLeaf()) 
      return CItem(); 

   return CItem(static_cast<CTreeLeafNode*>(pNode), *this); 
}

CItem CSection::transferItem(const char *pszTagName)
{
   if (!isValid()) return CItem(); 
   if (doCreateDoc()) 
      return addItem(pszTagName); 
   else
   { 
      CItem item = findItem(pszTagName); 
      if (!item.isValid()) error(); 
      return item; 
   }
}

bool CSection::transferSection(const char *pszTagName, CSection &section)
{
   if (!isValid()) return false; 
   if (doCreateDoc()) 
   {
      section = addSection(pszTagName); 
      return true; 
   }
   else
   { 
      return findSection(pszTagName, section); 
   }
}

CItem CSection::transferOptionalItem(const char *pszTagName, bool &bHasVal)
{
   if (!isValid()) return CItem(); 
   if (doCreateDoc()) 
   {
      if (bHasVal) 
         return transferItem(pszTagName); 
      else 
         return CItem(); 
   }
   else 
   {
      CItem item = findItem(pszTagName); 
      bHasVal = item.isValid(); 
      if (bHasVal) 
         return transferItem(pszTagName); 
      else 
         return CItem(); 
   }
}


#if _MSC_VER > 1000
#pragma warning (disable: 4786) // identifier was truncated to '255' characters in the debug information
#endif 

void CSection::findItems(const char *pszTagName, std::list<CItem> &items)
{
   if (!isValid()) return; 
   std::list<CTreeNode*> nodes; 
   m_pList->findChildren(std::string(pszTagName), nodes); 
   for(std::list<CTreeNode*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++) 
   {
      CTreeNode *pNode = (*iter); 
      if (pNode->isLeaf()) 
      { 
         items.push_back(CItem(static_cast<CTreeLeafNode*>(pNode), *this));    
      }
   }
}

void CErrorLog::error() {
   m_nErrorCount++; 
   assert(0); 
}


}



