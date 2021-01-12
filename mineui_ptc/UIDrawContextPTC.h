// file      : UIDrawContextPTC.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef UIDRAWCONTEXTPTC_H_INCLUDED
#define UIDRAWCONTEXTPTC_H_INCLUDED

#include <mineuibase/UIDrawContext.h>
#include <ptc.h>
#include <vector>

class CUISystemPTC : public CUISystemBase {
public: 
   CIconSetBase *loadIconSet(char *pszFilename, int nIconsX, int nIconsY);  
   virtual double getTime(); 
}; 

class CIconSetPTC : public CIconSetBase {
public: 
   CIconSetPTC(); 
   CUISize getSize() const;    
   bool load(char *pszFilename, int nIconsX, int nIconsY); 
   void drawIcon(unsigned char *pScreen, int nPitch, int nIdxX, int nIdxY, const CUIPoint &pos) const; 
private: 
   std::vector<unsigned char> m_bitmap; 
   CUISize m_nSize; 
   int m_nBitmapPitch; 
   int m_nInstX, m_nInstY;    
}; 

class CIUDrawContextPTC : public CUIDrawContextBase {
public: 
   CIUDrawContextPTC(BaseSurface *pSurf);
   ~CIUDrawContextPTC(); 
   static void getPalette(Palette &pal); 
   virtual void drawOuterFrame(const CUIRect &, Color upperLeft, Color lowerRight, int nSize); 
   virtual void fillRect(const CUIRect &, Color); 
   virtual void drawIcon(const CIconSetBase *, int nIdxX, int nIdxY, const CUIPoint &, int nX, int nY); 
   virtual void drawPixel(const CUIPoint&, Color); 
private: 
   BaseSurface *m_pSurf; 
   unsigned char *m_pScreenPtr; 
   CUISize m_nScreenSize; 
   CUIRect m_nScreenRect; 
   int m_nPitch; 
}; 

#endif 
