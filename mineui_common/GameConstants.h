// file      : GameConstants.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef GAMECONSTANTS_H_INCLUDED
#define GAMECONSTANTS_H_INCLUDED

#include <gamecontrol/GameMisc.h>

namespace GameConstant 
{

enum GameLevel {
   LEVEL_BEGINNER = 0, 
   LEVEL_INTERMEDIATE = 1, 
   LEVEL_EXPERT = 2, 
   LEVEL_USER_DEFINED = 3 
}; 

CGameDim getGameDimOfLevel(GameLevel nLevel); 

}

#endif 
