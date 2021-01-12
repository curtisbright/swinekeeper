// file      : GameMisc.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef GAMEMISC_H_INCLUDED
#define GAMEMISC_H_INCLUDED

/** 
 * Dimensions of a minesweeper game. 
 */ 
class CGameDim {
public: 
   CGameDim();
   CGameDim(int nX, int nY, int nM) : 
      m_nSizeX(nX), m_nSizeY(nY), m_nMines(nM) {}
   bool operator==(const CGameDim &d) const {
      return m_nSizeX == d.m_nSizeX
          && m_nSizeY == d.m_nSizeY
          && m_nMines == d.m_nMines; 
   }
   bool hasReasonableValues() const; 
   int sizeX() const {return m_nSizeX;}
   int sizeY() const {return m_nSizeY;}
   int bombCount() const {return m_nMines;}

public: 
   int m_nSizeX; 
   int m_nSizeY; 
   int m_nMines; 
}; 


#endif 
