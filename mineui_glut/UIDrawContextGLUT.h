// file      : UIDrawContextGLUT.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef UIDRAWCONTEXTGLUT_H_INCLUDED
#define UIDRAWCONTEXTGLUT_H_INCLUDED

#include <mineuibase/UIDrawContext.h>
#include <GL/glut.h>
#include <vector>

class CUISystemGLUT : public CUISystemBase {
public: 
   CIconSetBase *loadIconSet(char *pszFilename, int nIconsX, int nIconsY);  
   virtual double getTime(); 
}; 

class CIconSetGLUT : public CIconSetBase {
public: 
   CIconSetGLUT(); 
   CUISize getSize() const;    
   bool load(char *pszFilename, int nIconsX, int nIconsY); 
   void drawIcon(int nIdxX, int nIdxY, const CUIPoint &pos) const; 
private: 
   std::vector<unsigned int> m_bitmap; 
   mutable std::vector<GLuint> m_dispListNames; 
   CUISize m_nSize; 
   int m_nInstX, m_nInstY;    
   int m_nBitmapPixelCount; 
}; 

class CIUDrawContextGLUT : public CUIDrawContextBase {
public: 
   CIUDrawContextGLUT();
   ~CIUDrawContextGLUT(); 
   virtual void drawOuterFrame(const CUIRect &, Color upperLeft, Color lowerRight, int nSize); 
   virtual void fillRect(const CUIRect &, Color); 
   virtual void drawIcon(const CIconSetBase *, int nIdxX, int nIdxY, const CUIPoint &, int nX, int nY); 
   virtual void drawPixel(const CUIPoint&, Color); 
private: 
   unsigned char *m_pScreenPtr; 
   CUISize m_nScreenSize; 
   CUIRect m_nScreenRect; 
   int m_nPitch; 
   void glUIColor(Color col); 
   void glUIVertex(const CUIPoint &p); 
}; 

#endif 
