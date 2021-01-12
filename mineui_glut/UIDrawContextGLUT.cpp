// file      : UIDrawContextGLUT.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "UIDrawContextGLUT.h" 

#include <stdlib.h>
#include <cassert>
#include <time.h>
#include <mineuibase/UIBitmapUtil.h>

CIconSetBase *CUISystemGLUT::loadIconSet(char *pszFilename, int nIconsX, int nIconsY)
{
   CIconSetGLUT *pIconSet = new CIconSetGLUT; 
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

 
double CUISystemGLUT::getTime()
{
   time_t nTime; 
   time(&nTime); 
   return double(nTime); 
}


CIconSetGLUT::CIconSetGLUT() : m_nInstX(0), m_nInstY(0), m_nBitmapPixelCount(0) {}

CUISize CIconSetGLUT::getSize() const {return m_nSize;}


bool CIconSetGLUT::load(char *pszFilename, int nIconsX, int nIconsY)
{
   m_nInstX = nIconsX; 
   m_nInstY = nIconsY; 

   FILE *fp = fopen(pszFilename, "rb"); 
   if (!fp)
      return false; 

   std::vector<unsigned char> colIndexBitmap; 
   CUISize bmpSize; 
   if (!UILoadBitmap(fp, colIndexBitmap, bmpSize)) 
      return false; 

   assert(bmpSize.x()%nIconsX == 0); 
   assert(bmpSize.y()%nIconsY == 0); 
   m_nSize = CUISize(bmpSize.x()/nIconsX, bmpSize.y()/nIconsY); 
   int nBmpPitch = bmpSize.x(); 
   m_nBitmapPixelCount = m_nSize.x() * m_nSize.y(); 

   m_bitmap.resize(colIndexBitmap.size()); 
   int nX, nY, nU, nV; 
   int nDstPos=0; 
   for(nY=0;nY<nIconsY;nY++) 
      for(nX=0;nX<nIconsX;nX++) 
      {
      // int nBmpBase = nDstPos; 
         for(nV=0;nV<m_nSize.y();nV++)
            for(nU=0;nU<m_nSize.x();nU++) 
            {
               int nBmpPos = (nX*m_nSize.x()+nU) + (nY*m_nSize.y()+(m_nSize.y()-nV-1))*nBmpPitch; 
               CUIRGBColor col = CIUDrawContextGLUT::mStatic_RGBPalette[colIndexBitmap[nBmpPos]]; 
               unsigned int nCol = 
                    (col.blue() << 16) 
                  + (col.green() << 8) 
                  + (col.red() << 0);
               m_bitmap[nDstPos++] = nCol;  
            }  
      } 

   m_dispListNames.resize(nIconsY * nIconsX, 0); 

   return true; 
}

void CIconSetGLUT::drawIcon(int nIdxX, int nIdxY, const CUIPoint &pos) const
{
   int nBmpBase = (nIdxX + nIdxY*m_nInstX)*m_nBitmapPixelCount; 

   glRasterPos2i(pos.x(), pos.y()+m_nSize.y()); 

   if (m_dispListNames[nIdxX + nIdxY*m_nInstX] == 0) 
   {
      m_dispListNames[nIdxX + nIdxY*m_nInstX] = glGenLists(1); 
      glNewList(m_dispListNames[nIdxX + nIdxY*m_nInstX], GL_COMPILE); 
         glDrawPixels(m_nSize.x(), m_nSize.y(), GL_RGBA, GL_UNSIGNED_BYTE, &(m_bitmap[nBmpBase])); 
      glEndList();
   }
   
   // glDrawPixels(m_nSize.x(), m_nSize.y(), GL_RGBA, GL_UNSIGNED_BYTE, &(m_bitmap[nBmpBase])); 
   glCallList(m_dispListNames[nIdxX + nIdxY*m_nInstX]); 

}

CIUDrawContextGLUT::CIUDrawContextGLUT()
{
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
   glShadeModel(GL_FLAT); 
}

CIUDrawContextGLUT::~CIUDrawContextGLUT()
{
}

void CIUDrawContextGLUT::drawOuterFrame(const CUIRect &r_arg, Color upperLeft, Color lowerRight, int nSize)
{
   for(int i=0;i<nSize;i++) 
   {
      CUIRect r(r_arg.outerRect().inflate(i)); 
      glBegin(GL_LINE_STRIP); 
         glUIColor(upperLeft); 
         glUIVertex(r.vertex(3)); 
         glUIVertex(r.vertex(0)); 
         glUIVertex(r.vertex(1)); 
         glUIColor(lowerRight); 
         glUIVertex(r.vertex(2)); 
         glUIVertex(r.vertex(3)); 

         glUIVertex(r.vertex(2)); 
         glUIVertex(r.vertex(1)); 
         glUIColor(upperLeft); 
         glUIVertex(r.vertex(0)); 
         glUIVertex(r.vertex(3)); 
      glEnd(); 
   }
}

void CIUDrawContextGLUT::fillRect(const CUIRect &r, Color col)
{
   glBegin(GL_POLYGON); 
      glUIColor(col); 
      for(int i=0;i<4;i++) 
         glUIVertex(r.vertex(i)); 
   glEnd(); 
}

void CIUDrawContextGLUT::drawIcon(const CIconSetBase *pIcon, int nIdxX, int nIdxY, const CUIPoint &p, int nX, int nY)
{
   const CIconSetGLUT *pIconGLUT = static_cast<const CIconSetGLUT*>(pIcon); 
   pIconGLUT->drawIcon(nIdxX, nIdxY, p + pIcon->getSize().scaled(nX, nY)); 
}

void CIUDrawContextGLUT::drawPixel(const CUIPoint &p, Color col)
{
   glBegin(GL_POINTS); 
      glUIColor(col); 
      glUIVertex(p); 
   glEnd(); 
}

void CIUDrawContextGLUT::glUIColor(Color col)
{
   assert(col >= 0 && col < END_COLOR); 
   if (col >= END_COLOR) col = WHITE; 
   CUIRGBColor rgbCol = mStatic_RGBPalette[col]; 
   glColor3ub(rgbCol.red(), rgbCol.green(), rgbCol.blue()); 
}

void CIUDrawContextGLUT::glUIVertex(const CUIPoint &p)
{
   glVertex2i(p.x(), p.y());
}


