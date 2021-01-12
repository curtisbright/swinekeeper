// file      : CGlobalResourceSet.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CGLOBALRESOURCESET_H_INCLUDED
#define CGLOBALRESOURCESET_H_INCLUDED

#include <mineuibase/UIDrawContext.h> 

#include <memory>


/** 
 * 'Namespace' containing identifiers for the icon types used by minesweeper. 
 * The numbers that are assigned to the identifiers have to match 
 * with the positions of the icons in the bitmap files. 
 */ 
class IconType {
public: 

   enum Smilie {
      SMILIE_STANDARD,
      SMILIE_LOST, 
      SMILIE_WON, 
      SMILIE_ONCLICK, 
      SMILIE_PUSHED, 
      SMILIE_SOLVING, 
      SMILIE_COUNT
   }; 

   /** 
    * standard icons used during game play 
    */ 
   enum Field {
      FIELD_COUNT_BEGIN=0, 
      FIELD_COUNT_END=10, 
      FIELD_COVERED=10, 
      FIELD_COVERED_BOMBFLAG=11, 
      FIELD_UNCOVERED_BOMB=12, 
      FIELD_UNCOVERED_CLICKED_BOMB=13, 
      FIELD_UNCOVERED_MARKED_NOBOMB=14, 
      FIELD_ON_CLICK=15,
      FIELD_COVERED_QUESTIONMARK=16, 
      FIELD_COUNT
   }; 

   /** 
    * icons used to visualize results of a algorithm 
    */ 
   enum FieldInfo {
      FIELDINFO_KNOWN_NOBOMB, 
      FIELDINFO_KNOWN_BOMB, 
      FIELDINFO_KNOWN_FLAGBOMB, 
      FIELDINFO_KNOWN_FLAGNOBOMB, 
      FIELDINFO_UNDECIDEABLE,
      FIELDINFO_COUNT
   }; 

   enum Digit {
      DIGIT_COUNT = 10
   }; 

}; 

/** 
 * Singleton, that contains all icon sets of the program as members. 
 * Must be initialized by the client before e.g. @ref CGameView is used. 
 */ 
class CGlobalResourceSet {
public: 
   std::auto_ptr<CIconSetBase> m_pSmilies; 
   std::auto_ptr<CIconSetBase> m_pDigits; 
   std::auto_ptr<CIconSetBase> m_pFieldIcons; 
   std::auto_ptr<CIconSetBase> m_pFieldInfoIcons; 

   static CGlobalResourceSet *instance() {return m_pInstance;}
   static void setInstance(CGlobalResourceSet *p); 

   bool isValid() {
      return m_pSmilies.get() && 
             m_pDigits.get() && 
             m_pFieldIcons.get() && 
             m_pFieldInfoIcons.get(); 
   }

private: 
   static CGlobalResourceSet *m_pInstance; 
}; 

#endif 
