// file      : GameConstants.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "GameConstants.h" 
#include <cassert>

using namespace GameConstant; 

CGameDim GameConstant::getGameDimOfLevel(GameLevel nLevel)
{
   switch(nLevel) 
   {
      case LEVEL_BEGINNER:    
         return CGameDim(8,8,10); 
      case LEVEL_INTERMEDIATE: 
         return CGameDim(16,16,40); 
      case LEVEL_EXPERT: 
         return CGameDim(30,16,99); 
      default: 
         assert(0); 
         return CGameDim(30,16,99); 
   }
}

