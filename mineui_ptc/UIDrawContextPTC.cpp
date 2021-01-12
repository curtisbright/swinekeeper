// file      : UIDrawContextPTC.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "UIDrawContextPTC.h" 

#include <stdlib.h>
#include <cassert>
#include <time.h>
#include <mineuibase/UIBitmapUtil.h>

CIconSetBase *CUISystemPTC::loadIconSet(char *pszFilename, int nIconsX, int nIconsY)
{
   CIconSetPTC *pIconSet = new CIconSetPTC; 
   if (pIconSet->load(pszFilename, nIconsX, nIconsY)) 
   {
      return pIconSet; 
   }
   else 
   {
      delete pIconSet; 
      return NULL; 
   }
}  

 
double CUISystemPTC::getTime()
{
   time_t nTime; 
   time(&nTime); 
   return double(nTime); 
}


CIconSetPTC::CIconSetPTC() : m_nInstX(0), m_nInstY(0) {}

CUISize CIconSetPTC::getSize() const {return m_nSize;}


bool CIconSetPTC::load(char *pszFilename, int nIconsX, int nIconsY)
{
   FILE *fp = fopen(pszFilename, "rb"); 
   if (!fp)
      return false; 

   CUISize bmpSize; 
   if (!UILoadBitmap(fp, m_bitmap, bmpSize)) 
      return false; 

   m_nBitmapPitch = bmpSize.x(); 

   assert(bmpSize.x()%nIconsX == 0); 
   assert(bmpSize.y()%nIconsY == 0); 
   m_nSize = CUISize(bmpSize.x()/nIconsX, bmpSize.y()/nIconsY); 

   return true; 
}

void CIconSetPTC::drawIcon(unsigned char *pScreen, int nPitch, int nIdxX, int nIdxY, const CUIPoint &pos) const
{
   int nBmpBase = nIdxX*m_nSize.x() + (nIdxY*m_nSize.y())*m_nBitmapPitch; 
   int nScrBase = pos.x() + pos.y()*nPitch; 

   int nX, nY; 
   for(nY=0;nY<m_nSize.y();nY++)
   {
      for(nX=0;nX<m_nSize.x();nX++)
      {  
         pScreen[nX + nY*nPitch + nScrBase] = m_bitmap[nX + nY*m_nBitmapPitch + nBmpBase]; 
      }
   }
}

CIUDrawContextPTC::CIUDrawContextPTC(BaseSurface *pSurf)
{
   m_pSurf = pSurf; 
   m_pScreenPtr = reinterpret_cast<unsigned char*>(m_pSurf->lock()); 
   m_nScreenSize = CUISize(m_pSurf->width(), m_pSurf->height()); 
   m_nScreenRect = CUIRect(CUIPoint(0,0), m_nScreenSize); 
   m_nPitch = m_pSurf->pitch(); 
}

CIUDrawContextPTC::~CIUDrawContextPTC()
{
   m_pSurf->unlock(); 
}

void CIUDrawContextPTC::getPalette(Palette &pal)
{
   int32 intpal[256]; 
   int i; 
   for(i=0;i<256;i++) intpal[i] = 255; // blue; 
   for(i=0;i<END_COLOR;i++)
   {
      intpal[i] = (mStatic_RGBPalette[i].blue() << 0) 
                + (mStatic_RGBPalette[i].green() << 8)
                + (mStatic_RGBPalette[i].red() << 16); 
   }
   pal.load(intpal); 
}


void CIUDrawContextPTC::drawOuterFrame(const CUIRect &r_arg, Color upperLeft, Color lowerRight, int nSize)
{
   CUIRect outerrect = r_arg.inflated(nSize); 
   if (!m_nScreenRect.contains(outerrect)) 
   {
      // brute force clipping 
      assert(0); 
      return; 
   }

   for(int i=0;i<nSize;i++) 
   {
      CUIRect r(r_arg.outerRect().inflate(i)); 

      int j; 
      for(j = r.minV().x(); j<= r.maxV().x(); j++) 
      {
         m_pScreenPtr[j + r.minV().y() * m_nPitch] = static_cast<unsigned char>(upperLeft); 
         m_pScreenPtr[j + r.maxV().y() * m_nPitch] = static_cast<unsigned char>(lowerRight); 
      }

      for(j = r.minV().y(); j<= r.maxV().y(); j++) 
      {
         m_pScreenPtr[r.minV().x() + j * m_nPitch] = static_cast<unsigned char>(upperLeft); 
         m_pScreenPtr[r.maxV().x() + j * m_nPitch] = static_cast<unsigned char>(lowerRight); 
      }
   }
}

void CIUDrawContextPTC::fillRect(const CUIRect &r, Color col)
{
   if (!m_nScreenRect.contains(r)) 
   {
      // brute force clipping 
      assert(0); 
      return; 
   }

   int nX, nY; 
   for(nY = r.minV().y(); nY < r.maxV().y(); nY++) 
      for(nX = r.minV().x(); nX < r.maxV().x(); nX++)
          m_pScreenPtr[nX + nY * m_nPitch] = static_cast<unsigned char>(col);
}

void CIUDrawContextPTC::drawIcon(const CIconSetBase *pIcon, int nIdxX, int nIdxY, const CUIPoint &p, int nX, int nY)
{
   const CIconSetPTC *pIconPTC = static_cast<const CIconSetPTC*>(pIcon); 

   CUIPoint realPos = p + pIcon->getSize().scaled(nX, nY); 

   if (!m_nScreenRect.contains(CUIRect(realPos, pIcon->getSize()))) 
   {
      // brute force clipping 
      assert(0); 
      return; 
   }

   pIconPTC->drawIcon(m_pScreenPtr, m_nPitch, nIdxX, nIdxY, realPos); 
}

void CIUDrawContextPTC::drawPixel(const CUIPoint &p, Color col)
{
   if (!m_nScreenRect.isInside(p)) 
   {
      assert(0); 
      return; 
   }

   m_pScreenPtr[p.x() + p.y()*m_nPitch] = static_cast<unsigned char>(col); 
}


