// file      : Serializer.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#include "StdAfx.h"
#include "Serializer.h"
#include "Tree.h" 
#include <cassert>
#include <memory>

using namespace Storage; 

const char *CSerializer::Stream::ppszTokenStr[] = {"</", "<", ">"}; 

bool CSerializer::readTree(const std::string &str, CTreeListNode **ppNode)
{
   Stream stream(str); 
   XMLTag token; 
   if (!readXMLTag(stream, token)) 
      return false; 

   CTreeNode *pNode = NULL;
   if (!readSubTree(stream, token, &pNode)) 
      return false; 
   
   if (pNode->isLeaf()) 
      return false; 

   *ppNode = static_cast<CTreeListNode*>(pNode); 

   return true; 
}

bool CSerializer::writeTree(std::string &str, const CTreeListNode *pNode)
{
   str.reserve(0x10000); 
   writeSubTree(str, pNode, 0); 
   return true; 
}


void CSerializer::Stream::skipWhiteSpace()
{
   assert(isClassValid()); 
   while(!isEnd() && isspace(m_str[m_nCurPos])) m_nCurPos++; 
}

bool CSerializer::Stream::isEnd() const
{
   assert(isClassValid()); 
   return m_nCurPos >= m_str.length(); 
}

void CSerializer::Stream::skipChar()
{
   assert(isClassValid()); 
   if (isEnd()) return; 
   m_nCurPos++; 
}

char CSerializer::Stream::nextChar() const
{
   assert(isClassValid() && !isEnd()); 
   return m_str[m_nCurPos]; 
}

std::string CSerializer::Stream::readUntilXMLToken()
{
   assert(isClassValid()); 
   
   unsigned int nFoundPos = std::string::npos; 

   for(XMLToken nTok = XML_BEGIN_TOKENS; nTok < XML_END_TOKENS; nTok = XMLToken(nTok+1)) 
   {      
      unsigned int nPos = m_str.find(ppszTokenStr[nTok], m_nCurPos); 
      
      if (nPos < nFoundPos) 
         nFoundPos = nPos; 
   }
   
   std::string foundStr(m_str.substr(m_nCurPos, nFoundPos-m_nCurPos)); 
   m_nCurPos = nFoundPos;      
            
   return foundStr;    
}

CSerializer::Stream::XMLToken CSerializer::Stream::readXMLToken()
{
   assert(isClassValid()); 

   for(XMLToken nTok = XML_BEGIN_TOKENS; nTok < XML_END_TOKENS; nTok = XMLToken(nTok+1)) 
   {
      std::string token(ppszTokenStr[nTok]); 
      // if (m_str.compare(m_nCurPos, token.length(), token)==0)
      if (m_str.substr(m_nCurPos, token.length()) == token) 
      {
         m_nCurPos+= token.length(); 
         return nTok; 
      }
   }
   return XML_NO_TOKEN; 
}


bool CSerializer::Stream::isClassValid() const
{
   return true; 
}

bool CSerializer::readXMLTag(Stream &stream, XMLTag &token)
{
   stream.skipWhiteSpace(); 
   Stream::XMLToken nToken = stream.readXMLToken(); 
   if (nToken == Stream::XML_INVALID || nToken == Stream::XML_CLOSE) 
      return false;
       
   if (nToken == Stream::XML_NO_TOKEN) 
   {
      token.makeTextToken(stream.readUntilXMLToken());  
      return true; 
   }
   else 
   {
      bool bEnd = (nToken==Stream::XML_OPEN_END); 
      std::string tagName = stream.readUntilXMLToken(); 

      int nEndToken = stream.readXMLToken(); 
      if (nEndToken != Stream::XML_CLOSE) 
         return false; 
      token.makeTagToken(tagName, bEnd);
      return true; 
   }
}

bool CSerializer::readSubTree(Stream &stream, const XMLTag &beginToken, CTreeNode **ppNode)
{
   assert(*ppNode==NULL);
   if (!beginToken.isBeginTag()) 
      return false; 

   if (!CTreeNode::isValidTagName(beginToken.string()))
      return false; 

   XMLTag nextToken; 
   if (!readXMLTag(stream, nextToken))
      return false; 

   if (nextToken.isBeginTag() || nextToken.isEndTag()) 
   {
      std::auto_ptr<CTreeListNode> pNode(new CTreeListNode(beginToken.string())); 

      while (nextToken.isBeginTag())
      {
         CTreeNode *pSubTree = NULL; 
         if (!readSubTree(stream, nextToken, &pSubTree)) 
            return false; 
         pNode->addChild(pSubTree); 

         if (!readXMLTag(stream, nextToken))
            return false; 
      } 
       
      if (!nextToken.isEndTag() || nextToken.string() != beginToken.string()) 
         return false; 

      *ppNode = pNode.release(); 
      return true; 
   }  
   else
   {
      XMLTag endToken; 
      if (!readXMLTag(stream, endToken)) 
         return false; 
      if (!endToken.isEndTag() || endToken.string() != beginToken.string()) 
         return false; 

      if (!CText::isValidTextString(nextToken.string()))   
         return false;  

      std::auto_ptr<CTreeLeafNode> pNode(new CTreeLeafNode(beginToken.string())); 
      pNode->setText(nextToken.string()); 
      *ppNode = pNode.release(); 
      return true; 
   }
}

void CSerializer::writeSubTree(std::string &str, const CTreeNode *pNode, int nDepth) const
{
   if (pNode->isLeaf()) 
   {
      str.append(space(nDepth)); 
      str.append(pNode->beginTag()); 
      const CTreeLeafNode *pLeaf = static_cast<const CTreeLeafNode*>(pNode); 
      str.append(pLeaf->getText().getString()); 
      str.append(pNode->endTag()); 
      str.append("\n"); 
   }
   else 
   {
      str.append(space(nDepth)); 
      str.append(pNode->beginTag()); str.append("\n"); 
      const CTreeListNode *pList = static_cast<const CTreeListNode*>(pNode); 
      for(CTreeListNode::const_iterator iter = pList->beginChildren(); 
          iter != pList->endChildren(); 
          iter++)
      {
         writeSubTree(str, *iter, nDepth+1); 
      }
      str.append(space(nDepth)); 
      str.append(pNode->endTag()); str.append("\n");  
   }
}

std::string CSerializer::space(int nIndentDepth) {
   std::string str;
   int nChars(0); 
   if (nIndentDepth <= 10) 
      nChars = nIndentDepth*3; 
   else 
      nChars = 10*3 + (nIndentDepth-10); 
   str.insert((std::string::size_type)0, nChars, ' '); 
   return str; 
}
