// file      : Tree.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#include "StdAfx.h"
#include "Tree.h"
#include <ctype.h>
#include <cassert>

using namespace Storage; 

CTreeNode::CTreeNode(const std::string &tag) : 
   m_tagname(tag) {assert(isClassValid());}

bool CTreeNode::isClassValid()
{
   if (!isValidTagName(m_tagname)) 
      return false; 
   return true;    
}

bool CTreeNode::isValidTagChar(char c) {
   return (isalpha(c) && islower(c)) || isdigit(c) || c == '-'; 
}


bool CTreeNode::isValidTagName(const std::string &str)
{
   for(int i=0;i<int(str.length());i++) {
      if (!isValidTagChar(str[i])) 
         return false; 
   }

   if (str.length() == 0) 
      return false; 

   return true; 
}

CTreeNode* CTreeLeafNode::clone() const
{
   return new CTreeLeafNode(tagName(), getText()); 
}

CTreeNode* CTreeListNode::clone() const
{
   CTreeListNode *pListNode = new CTreeListNode(tagName()); 
   for(const_iterator iter = beginChildren(); iter != endChildren(); iter++) 
   {
      pListNode->addChild((*iter)->clone()); 
   }
   return pListNode; 
}


void CTreeListNode::addChild(CTreeNode *pNode) {
   m_children.push_back(pNode); 
}

CTreeListNode::~CTreeListNode()
{
   for(iterator iter = beginChildren(); iter != endChildren(); iter++) 
      delete (*iter); 
}

CTreeNode *CTreeListNode::findFirstChild(const std::string &tagName) 
{
   // inefficient 
   for(iterator iter = beginChildren(); iter != endChildren(); iter++) 
   {
      if ((*iter)->tagName() == tagName) 
         return (*iter); 
   }
   return NULL; 
}

void CTreeListNode::findChildren(const std::string &tagName, std::list<CTreeNode*> &children) 
{
   for(iterator iter = beginChildren(); iter != endChildren(); iter++) 
   {
      if ((*iter)->tagName() == tagName) 
         children.push_back(*iter); 
   }
}

