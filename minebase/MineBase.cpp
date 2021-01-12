// file      : MineBase.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "MineBase.h" 

#include <cstdlib>
#include <iostream>

using namespace std; 

void CFieldPos::print() {
   cout << "(" << m_nX << ", " << m_nY << ")"; 
}

int CFieldPos::distTo(const CFieldPos &p) const
{
   int nX = labs(m_nX - p.m_nX); 
   int nY = labs(m_nY - p.m_nY);
   if (nX > nY) 
      return nX; 
   else 
      return nY;  
}


const int CFieldPos::RELX[8] = {1,  1,  0, -1, -1, -1,  0,  1}; 
const int CFieldPos::RELY[8] = {0,  1,  1,  1,  0, -1, -1, -1}; 

CFieldPos CFieldRange::rand() const {
   return CFieldPos(
      ::rand()%(m_endX-m_beginX) + m_beginX, 
      ::rand()%(m_endY-m_beginY) + m_beginY); 
}
