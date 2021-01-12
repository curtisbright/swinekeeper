// file      : UIDrawContext.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef UIDRAWCONTEXT_H_INCLUDED
#define UIDRAWCONTEXT_H_INCLUDED

#include "UIMisc.h"
#include <cassert>
#include <cmath>
#include <cstdlib>

class CIconSetBase; 

class CUIRGBColor {
public: 
   CUIRGBColor() {m_nRGB[0]=0; m_nRGB[1]=0; m_nRGB[2]=0;} 
   CUIRGBColor(int r, int g, int b) {m_nRGB[0]=r; m_nRGB[1]=g; m_nRGB[2]=b;} 
   int &red() {return m_nRGB[0];}
   int red() const {return m_nRGB[0];}
   int &green() {return m_nRGB[1];}
   int green() const {return m_nRGB[1];}
   int &blue() {return m_nRGB[2];}
   int blue() const {return m_nRGB[2];}
   int &operator[](int i) {assert(i>=0&&i<3); return m_nRGB[i];}
   int operator[](int i) const {assert(i>=0&&i<3); return m_nRGB[i];}
   int dist(const CUIRGBColor &c) {
      int nSum = 0; 
      for(int i=0;i<3;i++) nSum += labs(m_nRGB[i]-c.m_nRGB[i]); 
      return nSum; 
   }

private: 
   int m_nRGB[3]; 
}; 

/** 
 * A singleton that contains some system-dependant functions.
 * Must be subclasses for each supported OS. 
 */ 
class CUISystemBase {
   public: 
   virtual ~CUISystemBase() {} 

   /** 
    * Returns the current time in seconds. 
    * It undefined to which base. 
    */ 
   virtual double getTime() = 0; 
   virtual bool pushedEscape() {return false;}

   static CUISystemBase *instance() {return m_pInstance;}
   static void setInstance(CUISystemBase *p); 
private: 
   static CUISystemBase *m_pInstance; 
}; 

/** 
 * A icon set is a rectangular array of icons of the same size.
 * @see CUIDrawContextBase::drawIcon
 */ 
class CIconSetBase {
public: 
   /** 
    * Returns the size of a single icon. 
    */ 
   virtual CUISize getSize() const =0; 
   virtual ~CIconSetBase() {} 
}; 

/** 
 * The drawing code uses the the methods of this class 
 * to draw the client area of minesweeper. 
 * 
 * The drawing code does not issue any drawing commands that draw outside
 * the client area. 
 */ 
class CUIDrawContextBase {
public: 
   /** 
    * I don't need more than 16 colors.  
    */ 
   enum Color {
      BLACK, 
      DARK_GRAY, 
      GRAY, 
      LIGHT_GRAY, 
      WHITE, 
   
      DARK_RED, 
      RED, 
      DARK_GREEN, 
      GREEN, 
      DARK_BLUE, 
      BLUE, 

      DARK_CYAN, 
      CYAN, 
      DARK_MAGENTA, 
      MAGENTA, 
      DARK_YELLOW,
      YELLOW,

      END_COLOR, 
                  
      // the colors used to draw the frames 
      DARK = GRAY, 
      LIGHT = WHITE, 
      MEDIUM = LIGHT_GRAY  
   }; 

   /** 
    * Draws a frame 
    * 
    * @param r : A rectangle that describes the area INSIDE the frame.  
    *            I.e. the method will draw a frame around this rectangle. 
    * @param upperLeft : Color of the upper and the left side of the frame 
    * @param lowerRight : Color of the lower and the right side of the frame 
    * @param nSize : width of the frame, >= 1
    */ 
   virtual void drawOuterFrame(const CUIRect &r, Color upperLeft, Color lowerRight, int nSize)=0; 
   /** 
    * Fills a rectangle with a constant color 
    */ 
   virtual void fillRect(const CUIRect &, Color)=0; 
   /** 
    * Draws a icon of a icon set. 
    * The icon is drawn at the location p + (nX*IconWidth, nY*IconHeight). 
    * 
    * @param pIconSet a 2-dim array of icons of the same size 
    * @param nIdxX first index of the icon that should be drawn 
    * @param nIdxY second index of the icon that should be drawn
    */ 
   virtual void drawIcon(const CIconSetBase *pIconSet, int nIdxX, int nIdxY, const CUIPoint &p, int nX=0, int nY=0)=0; 
   /** 
    * Draws a single pixel. 
    */ 
   virtual void drawPixel(const CUIPoint&, Color)=0; 

   virtual ~CUIDrawContextBase() {} 

   /** 
    * The RGB values of the colors in CUIDrawContextBase::Color. 
    * To simplify the implementation of the subclasses of this class.
    */ 
   static const CUIRGBColor mStatic_RGBPalette[END_COLOR]; 
}; 

#endif 
