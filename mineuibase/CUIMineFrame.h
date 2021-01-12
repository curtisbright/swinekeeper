// file      : CUIMineFrame.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CUIMINEFRAME_H_INCLUDED
#define CUIMINEFRAME_H_INCLUDED

#include "UIMisc.h" 

class CUIDrawContextBase; 

/** 
 * Draws the raised frames in the minesweeper area. 
 * Has auxillary methods to compute the layout of the minesweeper area. 
 */ 
class CUIMineFrame
{
public:
   enum FrameType {
      RAISED, SUNKEN, PLANAR
   }; 
   CUIMineFrame() {}
   CUIMineFrame(const CUIRect &r, FrameType nF, int nD) : m_rect(r), m_nDepth(nD), m_nFrameType(nF) {}
   CUIMineFrame(FrameType nF, int nD) : m_rect(0,0,0,0), m_nDepth(nD), m_nFrameType(nF) {}

   void setRect(const CUIRect &r) {m_rect = r;}
   CUIRect getRect() const {return m_rect;}
   CUISize getSize() const {return m_rect.size();}
   CUISize getInteriorSize() const {return getInteriorRect().size();}
   void setInteriorRect(const CUIRect &r) {m_rect = r;m_rect.inflate(m_nDepth);}
   CUIRect getInteriorRect() const {CUIRect r(m_rect); r.deflate(m_nDepth); return r;}

   bool isInInterior(const CUIPoint &p) const {
      return getInteriorRect().isInside(p); 
   }

   void setSize(const CUISize &s) {m_rect.setRect(getBase(), getBase()+s);}
   void setInteriorSize(const CUISize &s) {
      m_rect.setRect(getInteriorBase(), getInteriorBase()+s);
      m_rect.inflate(m_nDepth);
   }
   int getDepth() const {return m_nDepth;}

   void moveTo(const CUIPoint &p) {CUISize s(getSize()); m_rect = CUIRect(p, s);}
   void moveBottomRightTo(const CUIPoint &p) {
      CUIPoint p2 = p - getSize(); 
      moveTo(p2); 
   }
   void moveMiddleTo(const CUIPoint &p) {
      CUIPoint p2 = p - CUISize(getSize().x()/2, getSize().y()/2); 
      moveTo(p2); 
   }
   CUIPoint getMiddle() const {
      return m_rect.minV() + CUISize(getSize().x()/2, getSize().y()/2); 
   }
   void moveTopRightTo(const CUIPoint &p) {
      CUIPoint p2(p.x() - getSize().x(), p.y()); 
      moveTo(p2); 
   }

   void moveRel(const CUISize &p) { m_rect.move(p);}
   CUIPoint getBase() const {return m_rect.minV();}
   CUIPoint getTopLeft() const {return m_rect.minV();}
   CUIPoint getBottomRight() const {return m_rect.maxV();}
   CUIPoint getInteriorBase() const {return getInteriorRect().minV();}
   CUIPoint getInteriorTopLeft() const {return getInteriorRect().minV();}
   CUIPoint getInteriorTopRight() const {CUIRect r = getInteriorRect(); return CUIPoint(r.maxV().x(), r.minV().y());}
   CUIPoint getInteriorBottomRight() const {return getInteriorRect().maxV();}

   void attachBelow(const CUIMineFrame &f); 
   CUISize getAttachDiffBelow(const CUIMineFrame &f) const; 

   bool drawFrame(CUIDrawContextBase *pCtx) const; 
   bool drawInterior(CUIDrawContextBase *pCtx) const; 
   
private: 
   CUIRect m_rect; 
   int m_nDepth; 
   FrameType m_nFrameType; 

}; 


#endif 
