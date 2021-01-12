// file      : CPersistentState.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CPERSISTENTSTATE_H_INCLUDED
#define CPERSISTENTSTATE_H_INCLUDED

#include <mineui_common/GameOptions.h> 
#include "CPersistentDictionary.h"

/** 
 * The properties of this class are persistent. 
 */ 
class CPersistentState {
public:  
   CPersistentState(); 
   ~CPersistentState(); 
   // static CPersistentState* instance() {return &m_instance;}
   
   void init(CPersistentDictionary *pDictionary); 

   void getScoreTable(CScoreTable &table) const; 
   void setScoreTable(const CScoreTable &table); 

   void getGameOptions(CGameOptions &options) const; 
   void setGameOptions(const CGameOptions &options); 

private:    
   // static CPersistentState m_instance; 

   CPersistentDictionary *m_pDictionary; 

   const char *getScoreTimeKey(GameConstant::GameLevel level) const; 
   const char *getScoreNameKey(GameConstant::GameLevel level) const; 
}; 

#endif 
