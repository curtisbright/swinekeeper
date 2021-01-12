#ifndef COMPWINPROP_H_INCLUDED
#define COMPWINPROP_H_INCLUDED

#include <minebase/MineBase.h>
#include "CResultField.h" 
#include "CInputField.h" 


bool compWinProp(
   CMineArrayBase<CResultField> &resultArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount);


#endif 
