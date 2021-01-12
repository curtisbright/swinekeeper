// file      : GameMisc.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "GameMisc.h" 

CGameDim::CGameDim() : 
   m_nSizeX(0), m_nSizeY(0), m_nMines(0)
{
}


/** 
 * Just verifies if the values are not completely bogus.
 * The size of the array might stil be too large for the screen etc...
 */ 
bool CGameDim::hasReasonableValues() const
{
   return   
         m_nSizeX >= 3 && m_nSizeX < 1024 
      && m_nSizeY >= 3 && m_nSizeY < 1024
      && m_nMines >= 1 && m_nMines < 1024*1024;  
}  
