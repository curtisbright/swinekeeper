// file      : UIDrawContext.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "UIDrawContext.h" 

#include <cassert>

void CUISystemBase::setInstance(CUISystemBase *p) {
   // set only once 
   assert(m_pInstance == 0); 
   m_pInstance = p; 
}



CUISystemBase *CUISystemBase::m_pInstance = 0; 

const CUIRGBColor CUIDrawContextBase::mStatic_RGBPalette[END_COLOR] = {
   CUIRGBColor(0, 0, 0), 
   CUIRGBColor(64, 64, 64),
   CUIRGBColor(128, 128, 128),   
   CUIRGBColor(192, 192, 192), 
   CUIRGBColor(255, 255, 255),

   CUIRGBColor(128, 0, 0), 
   CUIRGBColor(255, 0, 0), 
   CUIRGBColor(0, 128, 0), 
   CUIRGBColor(0, 255, 0), 
   CUIRGBColor(0, 0, 128), 
   CUIRGBColor(0, 0, 255), 

   CUIRGBColor(128, 128, 0),   
   CUIRGBColor(255, 255, 0),

   CUIRGBColor(128, 0, 128),   
   CUIRGBColor(255, 0, 255),

   CUIRGBColor(0, 128, 128),   
   CUIRGBColor(0, 255, 255),
}; 
