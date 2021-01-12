// file      : UIAux.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "UIAux.h" 

/** 
 * Draws a multi-digit number. 
 * 
 * @param pCtx The drawing context to draw into.
 * @param pDigits A icon set that contains of 10 icons, each representing a digit. 
 * @param nDigitCount The number of digits to draw
 * @param p Upper left position of the rectangle into which the icons should be 
 *        drawn. (The size of the rectangle depends on the size of the icons 
 *        in the icon set.) 
 * @param nNumber The number to draw. If the number is too big or negative, 
 *        it is truncated. 
 */ 
void UIAux::drawNumber(
   CUIDrawContextBase *pCtx, 
   CIconSetBase *pDigits, int nDigitCount, 
   const CUIPoint &p, 
   int nNumber)
{
   int nV = 1; 
   int i; 
   for(i=0;i<nDigitCount;i++) nV *= 10;
   if (nNumber >= nV) nNumber = nV-1; 
   if (nNumber < 0) nNumber = 0;  
       
   nV = 1; 
   for(i=0;i<nDigitCount;i++) 
   {
      int nDigit = (nNumber/nV)%10; 
      pCtx->drawIcon(pDigits, nDigit, 0, p, nDigitCount-i-1, 0); 
      nV*=10; 
   }
}

/** 
 * Draws an icon that visualizes a real number between 0 and 1
 * Read implementation for exact behaviour. 
 * 
 * @param pCtx Drawing Context 
 * @param r Rectangle of the icon (i.e. size and position on the screen) 
 * @param nFrameColor  
 * @param nColor 
 * @param dRatio The number to visualize 0 <= dRatio <= 1
 */ 
void UIAux::drawRatioIcon( 
   CUIDrawContextBase *pCtx, 
   const CUIRect &r,
   CUIDrawContextBase::Color nFrameColor, 
   CUIDrawContextBase::Color nColor, 
   double dRatio) 
{
   if (dRatio >= 1) dRatio = 1; 

   CUIRect rFrame = r.deflated(4); 
   pCtx->fillRect(rFrame, CUIDrawContextBase::LIGHT_GRAY); 
   pCtx->drawOuterFrame(rFrame, nFrameColor, nFrameColor, 1); 
   CUIRect rInfoFrame = rFrame.deflated(1); 

   int nSizeX = rInfoFrame.size().x();
   int nSizeY = rInfoFrame.size().y();

   int nYVal = int(dRatio*nSizeY); 
   int nXVal = int((dRatio*nSizeY - nYVal)*nSizeX + .5); 

   CUIRect rI1(rInfoFrame.minV() + CUISize(0, nSizeY-nYVal), rInfoFrame.maxV()); 
   CUIRect rI2(rInfoFrame.minV() + CUISize(0, nSizeY-nYVal-1), rInfoFrame.maxV() - CUISize(nSizeX-nXVal,0)); 

   pCtx->fillRect(rI1, nColor); 
   pCtx->fillRect(rI2, nColor); 
} 
