// file      : MineSolver.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef MINESOLVER_H_INCLUDED
#define MINESOLVER_H_INCLUDED

#include <minebase/MineBase.h>
#include <cmath>
#include <string>
// XXX 
#include "CMineArray.h" 
#include "CInputField.h" 
#include "CResultField.h"


bool compGoodness(
   CMineArrayBase<CResultField> &resultArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount); 

bool compSolutionSets(
   CMineArrayBase<CResultField> &resultArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount); 

bool compPreSolvedMineArray(
   CMineArray &mineArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount); 


#endif 
