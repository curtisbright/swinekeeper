// file      : UIDrawContextWTL.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef UIDRAWCONTEXTWTL_H_INCLUDED
#define UIDRAWCONTEXTWTL_H_INCLUDED

#include <mineuibase/UIDrawContext.h>

inline CUIPoint toUI(const CPoint &p) {return CUIPoint(p.x, p.y);}
inline CUISize toUI(const CSize &p) {return CUISize(p.cx, p.cy);}
inline CUIRect toUI(const CRect &r) {return CUIRect(toUI(r.TopLeft()), toUI(r.BottomRight()));}

inline CPoint toWTL(const CUIPoint &p) {return CPoint(p.x(), p.y());}
inline CSize toWTL(const CUISize &p) {return CSize(p.x(), p.y());}
inline CRect toWTL(const CUIRect &r) {return CRect(toWTL(r.minV()), toWTL(r.maxV()));}

class CUISystemWTL : public CUISystemBase {
public: 
   static CUISystemWTL *instanceWTL() {return static_cast<CUISystemWTL *>(instance());}

   virtual CIconSetBase *loadIconSet(int nIconsID, int nIconsX, int nIconsY);   
   virtual double getTime(); 
   virtual bool pushedEscape(); 
}; 

class CIconSetWTL : public CIconSetBase {
public: 
   CIconSetWTL(); 
   CUISize getSize() const;    
   bool load(DWORD nBmpID, int nIconsX, int nIconsY); 
   void drawIcon(HDC hdc, int nIdxX, int nIdxY, const CPoint &pos) const; 
private: 
   CBitmap m_Bitmap; 
   CUISize m_nSize; 
   int m_nInstX, m_nInstY;    
}; 

class CIUDrawContextWTL : public CUIDrawContextBase {
public: 
   CIUDrawContextWTL(HDC hdc); 
   virtual void drawOuterFrame(const CUIRect &, Color upperLeft, Color lowerRight, int nSize); 
   virtual void fillRect(const CUIRect &, Color); 
   virtual void drawIcon(const CIconSetBase *, int nIdxX, int nIdxY, const CUIPoint &, int nX, int nY); 
   virtual void drawPixel(const CUIPoint&, Color); 
private: 
   CDCHandle m_dc; 
   CPen m_vPen[END_COLOR]; 
   CBrush m_vBrush[END_COLOR]; 
   HPEN getPen(Color col); 
   HBRUSH getBrush(Color col); 

   static const COLORREF m_colorTable[END_COLOR]; 
}; 

#endif 
