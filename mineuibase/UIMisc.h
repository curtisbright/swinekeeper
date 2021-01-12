// file      : UIMisc.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef UIMISC_H_INCLUDED
#define UIMISC_H_INCLUDED

#include <cassert>
#include <minebase/MineStd.h>
// #include <limits> does not work, not available in gcc 
#include <limits.h>

/** 
 * Represents the size of a rectangular area on the screen 
 */ 
class CUISize {
   friend class CUIPoint; 
public: 
   CUISize(int nX, int nY) : m_nX(nX), m_nY(nY) {}
   CUISize() : m_nX(0), m_nY(0) {}
   const CUISize& operator+=(const CUISize &p) {
      m_nX += p.m_nX; 
      m_nY += p.m_nY;
      return *this;
   } 
   const CUISize& operator-=(const CUISize &p) {
      m_nX -= p.m_nX; 
      m_nY -= p.m_nY;
      return *this;
   } 
   CUISize operator+(const CUISize &p) const {
      CUISize s(*this);
      s += p; 
      return s; 
   }   
   CUISize operator-(const CUISize &p) const {
      CUISize s(*this);
      s -= p; 
      return s; 
   }   
   CUISize scaled(int nXFac, int nYFac) const { 
      return CUISize(m_nX * nXFac, m_nY * nYFac);
   }

   int pixelCount() const {return m_nX*m_nY;}

   int x() const {return m_nX;}
   int y() const {return m_nY;}
  
private: 
   int m_nX, m_nY; 
}; 

/** 
 * Represents a pixel location on the screen 
 */ 
class CUIPoint {
public: 
   CUIPoint(int nX, int nY) : m_nX(nX), m_nY(nY) {}
   CUIPoint() : m_nX(0), m_nY(0) {}
   explicit CUIPoint(const CUISize& p) : m_nX(p.m_nX), m_nY(p.m_nY) {} 

   static CUIPoint trace(const CUIPoint &p1, const CUIPoint &p2) {
      return CUIPoint(p1.m_nX, p2.m_nY); 
   } 

   const CUIPoint& operator+=(const CUIPoint &p) {
      m_nX += p.m_nX; 
      m_nY += p.m_nY;
      return *this;
   } 
   const CUIPoint& operator-=(const CUIPoint &p) {
      m_nX -= p.m_nX; 
      m_nY -= p.m_nY;
      return *this;
   } 
   const CUIPoint& operator+=(const CUISize &p) {
      m_nX += p.m_nX; 
      m_nY += p.m_nY;
      return *this;
   } 
   const CUIPoint& operator-=(const CUISize &p) {
      m_nX -= p.m_nX; 
      m_nY -= p.m_nY;
      return *this;
   } 
   CUIPoint operator+(const CUIPoint &p) const {
      CUIPoint s(*this);
      s += p; 
      return s; 
   }   
   CUIPoint operator+(const CUISize &p) const {
      CUIPoint s(*this);
      s += p; 
      return s; 
   }   
   CUIPoint operator-(const CUISize &p) const {
      CUIPoint s(*this);
      s -= p; 
      return s; 
   }   

   int x() const {return m_nX;}
   int y() const {return m_nY;}
  
private: 
   int m_nX, m_nY; 
}; 

CUISize operator-(const CUIPoint &p1, const CUIPoint &p2); 

/** 
 * A rectangular area on the screen.
 * 
 * 'min' is always the upper left corner, 
 * 'max' is the lower right corner plus (1,1) 
 */ 
class CUIRect {
public: 

   #ifdef max 
      #undef max
   #endif 
   #ifdef min 
      #undef min
   #endif 

   /** 
    * use @ref CUIRect::emptyRect if you need a empty rectangle
    */ 
   CUIRect() : m_min(0, 0), m_max(0, 0) {} 
   CUIRect(const CUIPoint &min, const CUIPoint &max) : m_min(min), m_max(max) {}  
   CUIRect(const CUIPoint &min, const CUISize &size) : m_min(min), m_max(min + size) {}  
   CUIRect(int nMinX, int nMinY, int nMaxX, int nMaxY) : m_min(nMinX, nMinY), m_max(nMaxX, nMaxY) {}  

   /** 
    * returns a rectangle that is really empty 
    */ 
   static CUIRect emptyRect() {return CUIRect(
                                       INT_MAX, INT_MAX,
                                       INT_MIN, INT_MIN);}

   CUISize size() const {return m_max-m_min;}

   const CUIPoint &minV() const {return m_min;}
   const CUIPoint &maxV() const {return m_max;}

   /** 
    * Returns the vertices in counter-clockwise order
    * 
    * @param i index of the vertex, 0 <= i < 4
    */ 
   CUIPoint vertex(int i) const {
      assert(i>=0 && i<4); 
      switch(i) {
         case 0: return m_min;
         case 1: return CUIPoint::trace(m_min, m_max); 
         case 2: return m_max; 
         case 3: return CUIPoint::trace(m_max, m_min);
         default: return m_min; 
      }
   }

   bool isInside(const CUIPoint &p) const {
      return p.x() >= m_min.x() && p.x() < m_max.x()
          && p.y() >= m_min.y() && p.y() < m_max.y(); 
   }

   bool isEmpty() const {
      return m_min.x() >= m_max.x() || m_min.y() >= m_max.y(); 
   }

   static bool doIntervalsOverlap(int a1, int b1, int a2, int b2) {
      assert(a1 <= b1 && a2 <= b2); 
      return a2 < b1 && a1 < b2;
   }

   /** 
    * True, if *this and r have a nonempty intersection
    */ 
   bool touches(const CUIRect &r) const {
      return doIntervalsOverlap(m_min.x(), m_max.x(), r.m_min.x(), r.m_max.x()) 
          && doIntervalsOverlap(m_min.y(), m_max.y(), r.m_min.y(), r.m_max.y());  
   }

   /** 
    * True, if r is a subset of *this
    */ 
   bool contains(const CUIRect &r) const {
      // XXX not sure if ok 
      return isInside(r.m_min) && isInside(r.m_max - CUISize(1,1)); 
   }

   /** 
    * Return the smallest rectangle that contains both *this and r 
    */ 
   CUIRect getUnionBBox(const CUIRect &r) const {
      return CUIRect(
         MineStd::auxMin(m_min.x(), r.m_min.x()), 
         MineStd::auxMin(m_min.y(), r.m_min.y()), 
         MineStd::auxMax(m_max.x(), r.m_max.x()), 
         MineStd::auxMax(m_max.y(), r.m_max.y())); 
   }

   CUIRect getIntersection(const CUIRect &r) const {
      return CUIRect(
         MineStd::auxMax(m_min.x(), r.m_min.x()), 
         MineStd::auxMax(m_min.y(), r.m_min.y()), 
         MineStd::auxMin(m_max.x(), r.m_max.x()), 
         MineStd::auxMin(m_max.y(), r.m_max.y())); 
   }


   CUIRect innerRect() const {return CUIRect(m_min, m_max - CUISize(1,1));}
   CUIRect outerRect() const {return CUIRect(m_min-CUISize(1,1), m_max);}
   CUIPoint innerVertex(int i) const {return innerRect().vertex(i);}
   CUIPoint outerVertex(int i) const {return outerRect().vertex(i);}
   const CUIRect &inflate(int s) {m_min -= CUISize(s,s); m_max += CUISize(s,s); return (*this);}
   const CUIRect &deflate(int s) {return inflate(-s);}
   CUIRect inflated(int s) const {CUIRect r(*this); return r.inflate(s);}
   CUIRect deflated(int s) const {CUIRect r(*this); return r.deflate(s);}

   const CUIRect &move(const CUISize &p) {m_min += p; m_max += p; return *this;}
   CUIRect moved(const CUISize &p) const {CUIRect r(*this); return r.move(p);}

   const CUIRect &moveTo(const CUIPoint &p) {
      CUISize s(size()); 
      m_min = p; m_max = m_min + s; 
      return *this;
   }
   CUIRect movedTo(const CUIPoint &p) const {CUIRect r(*this); return r.moveTo(p);}

   /** 
    * Resize the array while leaving the upper left corner at its current place
    */  
   const CUIRect &setSize(const CUISize &s) {
      m_max = m_min + s; 
      return *this;
   }
   const CUIRect &setRect(const CUIPoint &amin, const CUIPoint &amax) {
      m_min = amin; 
      m_max = amax;
      return *this; 
   }
   const CUIRect &setRect(const CUIPoint &amin, const CUISize &s) {
      m_min = amin; 
      m_max = amin + s;
      return *this; 
   }
    
         
private: 
   CUIPoint m_min; 
   CUIPoint m_max; 
}; 


#endif 
