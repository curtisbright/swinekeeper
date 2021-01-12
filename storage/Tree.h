// file      : Tree.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#if !defined(AFX_TREE_H__C0F01233_931F_11D4_BF0C_000000000000__INCLUDED_)
#define AFX_TREE_H__C0F01233_931F_11D4_BF0C_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <list>
#include "CText.h" 

namespace Storage {

class CTreeNode {
   CTreeNode(const CTreeNode&); 
   const CTreeNode& operator=(const CTreeNode&); 
public: 
   CTreeNode(const std::string &tag);
   virtual ~CTreeNode() {} 
   void setTagName(const std::string& str) {m_tagname = str;}

   virtual bool isLeaf() const=0; 
   virtual CTreeNode* clone() const=0; 

   std::string tagName() const {return m_tagname;}
   std::string beginTag() const {return std::string("<") + m_tagname + std::string(">");}
   std::string endTag() const {return std::string("</") + m_tagname + std::string(">");}

   static bool isValidTagName(const std::string &str); 
   
private: 
   
   std::string m_tagname; 

   static bool isValidTagChar(char c);
   bool isClassValid(); 

}; 

class CTreeLeafNode : public CTreeNode 
{
public: 
   CTreeLeafNode(const std::string &tag) : CTreeNode(tag) {}
   CTreeLeafNode(const std::string &tag, const CText &text) : CTreeNode(tag), m_text(text) {}
   virtual CTreeNode* clone() const; 
   void setText(const CText &text) {m_text = text;}
   const CText& getText() const {return m_text;}
   bool isLeaf() const {return true;}
private: 
   CText m_text; 
}; 

class CTreeListNode : public CTreeNode 
{
   CTreeListNode(const CTreeListNode&); 
   const CTreeListNode& operator=(const CTreeListNode&); 
public: 
   CTreeListNode(const std::string &tag) : CTreeNode(tag) {}
   ~CTreeListNode(); 
   virtual CTreeNode* clone() const; 
   void addChild(CTreeNode *pNode);

   typedef std::list<CTreeNode*> ChildListType; 
   typedef ChildListType::iterator iterator; 
   typedef ChildListType::const_iterator const_iterator; 
   
   iterator beginChildren() {return m_children.begin();}
   iterator endChildren() {return m_children.end();}
   const_iterator beginChildren() const {return m_children.begin();}
   const_iterator endChildren() const {return m_children.end();}
   bool isLeaf() const {return false;}

   CTreeNode *findFirstChild(const std::string &tagName) ; 

   void findChildren(const std::string &tagName, std::list<CTreeNode*> &children) ; 

private: 
   ChildListType m_children; 
}; 


}

#endif // !defined(AFX_TREE_H__C0F01233_931F_11D4_BF0C_000000000000__INCLUDED_)
