// file      : UIDrawContextWTL.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "UIDrawContextWTL.h" 

#include <memory>


CIconSetBase *CUISystemWTL::loadIconSet(int nIconsID, int nIconsX, int nIconsY)
{
   std::auto_ptr<CIconSetWTL> pIconSetWTL(new CIconSetWTL()); 
   if (pIconSetWTL.get() == NULL) return NULL; 
   if (!pIconSetWTL->load(nIconsID, nIconsX, nIconsY)) 
   {
      return NULL; 
   }
   return pIconSetWTL.release();  
}   

double CUISystemWTL::getTime() {
   return double(GetTickCount())/1000; 
}

bool CUISystemWTL::pushedEscape()
{
   return GetAsyncKeyState(VK_ESCAPE) != 0; 
}

CIconSetWTL::CIconSetWTL() : m_nInstX(0), m_nInstY(0) {}


CUISize CIconSetWTL::getSize() const {return m_nSize;}
   
bool CIconSetWTL::load(DWORD nBmpID, int nIconsX, int nIconsY)
{
   m_nInstX = nIconsX; 
   m_nInstY = nIconsY; 

   m_Bitmap.LoadBitmap(MAKEINTRESOURCE(nBmpID)); 
   CSize bmpSize; 
   m_Bitmap.GetSize(bmpSize); 
   ATLASSERT(bmpSize.cx % nIconsX == 0); 
   ATLASSERT(bmpSize.cy % nIconsY == 0); 
   if (bmpSize.cx % nIconsX != 0 || bmpSize.cy % nIconsY != 0) 
      return false;
   
   m_nSize = CUISize(bmpSize.cx / nIconsX, bmpSize.cy / nIconsY); 

   return true; 
}

void CIconSetWTL::drawIcon(HDC hdc, int nIdxX, int nIdxY, const CPoint &pos) const
{
   ATLASSERT(nIdxX < m_nInstX); 
   ATLASSERT(nIdxY < m_nInstY); 
   CDC hdcImage; 
   hdcImage.CreateCompatibleDC(hdc);
   ATLASSERT(hdcImage); 
   HBITMAP hOld = hdcImage.SelectBitmap(m_Bitmap);
   CDCHandle dstHDC(hdc); 
   dstHDC.BitBlt(
      pos.x, pos.y, 
      m_nSize.x(), m_nSize.y(), 
      hdcImage, 
      m_nSize.x()*nIdxX, m_nSize.y()*nIdxY, 
      SRCCOPY); 
   hdcImage.SelectBitmap(hOld); 
} 

const COLORREF CIUDrawContextWTL::m_colorTable[] = {
   RGB(0, 0, 0), 
   RGB(64, 64, 64),
   RGB(128, 128, 128),   
   RGB(192, 192, 192), 
   RGB(255, 255, 255),

   RGB(128, 0, 0), 
   RGB(255, 0, 0), 
   RGB(0, 128, 0), 
   RGB(0, 255, 0), 
   RGB(0, 0, 128), 
   RGB(0, 0, 255), 

   RGB(128, 128, 0),   
   RGB(255, 255, 0),

   RGB(128, 0, 128),   
   RGB(255, 0, 255),

   RGB(0, 128, 128),   
   RGB(0, 255, 255),
};    


CIUDrawContextWTL::CIUDrawContextWTL(HDC hdc) :  m_dc(hdc) {
   for(int i=0;i<END_COLOR;i++) 
   {
      m_vPen[i].CreatePen(PS_SOLID, 1, m_colorTable[i]); 
      m_vBrush[i].CreateSolidBrush(m_colorTable[i]);
   }
}

HPEN CIUDrawContextWTL::getPen(Color col) {
   ATLASSERT(col >= 0 && col < END_COLOR); 
   if (col >= END_COLOR) col = WHITE; 
   return m_vPen[col]; 
}

HBRUSH CIUDrawContextWTL::getBrush(Color col) {
   ATLASSERT(col >= 0 && col < END_COLOR); 
   if (col >= END_COLOR) col = WHITE; 
   return m_vBrush[col]; 
}


void CIUDrawContextWTL::drawOuterFrame(const CUIRect &r_arg, Color upperLeft, Color lowerRight, int nSize)
{
   HPEN hOldPen = m_dc.SelectPen(getPen(upperLeft)); 
   for(int i=0;i<nSize;i++) 
   {
      CUIRect r(r_arg.outerRect().inflate(i)); 
     
      m_dc.MoveTo(toWTL(r.vertex(3))); 
      m_dc.SelectPen(getPen(upperLeft)); m_dc.LineTo(toWTL(r.vertex(0))); m_dc.LineTo(toWTL(r.vertex(1))); 
      m_dc.SelectPen(getPen(lowerRight)); m_dc.LineTo(toWTL(r.vertex(2))); m_dc.LineTo(toWTL(r.vertex(3))); 
   }

   m_dc.SelectPen(hOldPen); 
}

void CIUDrawContextWTL::fillRect(const CUIRect &r, Color col)
{
   m_dc.FillRect(toWTL(r), getBrush(col)); 
}

void CIUDrawContextWTL::drawIcon(const CIconSetBase *pIcon, int nIdxX, int nIdxY, const CUIPoint &p, int nX, int nY)
{
   const CIconSetWTL *pIconWTL = static_cast<const CIconSetWTL*>(pIcon); 
   pIconWTL->drawIcon(m_dc, nIdxX, nIdxY, toWTL(p + pIcon->getSize().scaled(nX, nY))); 
}

void CIUDrawContextWTL::drawPixel(const CUIPoint &p, Color col)
{
   ATLASSERT(col >= 0 && col < END_COLOR); 
   if (col >= END_COLOR) col = WHITE; 
   m_dc.SetPixel(p.x(), p.y(), m_colorTable[col]); 
}

