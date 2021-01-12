// file      : UIAux.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef UIAUX_H_INCLUDED
#define UIAUX_H_INCLUDED

#include "UIDrawContext.h" 
#include "UIMisc.h" 


namespace UIAux {

void drawNumber(
   CUIDrawContextBase *pCtx, 
   CIconSetBase *pDigits, int nDigits, 
   const CUIPoint &p, 
   int nNumber); 

void drawRatioIcon( 
   CUIDrawContextBase *pCtx, 
   const CUIRect &r,
   CUIDrawContextBase::Color nFrameColor, 
   CUIDrawContextBase::Color nColor, 
   double dRatio); 

}; 



#endif 
