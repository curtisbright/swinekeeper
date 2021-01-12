// file      : MineUI_GLUT.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

// MineUI_GLUT.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"
#include <GL/glut.h>
#include "UIDrawContextGLUT.h" 
#include <gamecontrol/CGameManager.h>
#include <gamecontrol/CGlobalResourceSet.h>
#include <gamecontrol/InputDevices.h>
#include <cstdio>

CGameManager g_gameMgr; 
CMouseInputDevice g_mouse;  
int g_nCurMouseButton=-1; 
bool g_vbMousePushed[3] = {false, false, false}; 

void display(void)
{
   // glClear(GL_COLOR_BUFFER_BIT);
   CIUDrawContextGLUT ctx; 
   g_gameMgr.draw(&ctx, true); 
   glutSwapBuffers();
}

void selectiveDisplay(void) 
{
   CIUDrawContextGLUT ctx; 
   g_gameMgr.draw(&ctx, false); 
   glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-.5, w-.5, h-.5, -.5);
  glMatrixMode(GL_MODELVIEW);
}

void timer(int val123) 
{
   if (val123 == 123) 
   {
      selectiveDisplay();
      glutTimerFunc(500, timer, 123); 
   }
}

void mouseCB(int button, int state, int x, int y)
{
   if (button >= 0 && button < 3) {
      g_vbMousePushed[button] = (state==GLUT_DOWN); 
   }

   if (state==GLUT_UP) 
   {  
      g_mouse.onReleaseButton(CUIPoint(x,y)); 
      g_nCurMouseButton = -1; 
   }
   else if (g_nCurMouseButton != button)  
   {
      CMouseInputDevice::MouseButton nButton; 
      switch(button) {
         case 0: nButton = CMouseInputDevice::BUTTON_LEFT; break; 
         case 1: nButton = CMouseInputDevice::BUTTON_MIDDLE; break; 
         case 2: nButton = CMouseInputDevice::BUTTON_RIGHT; break; 
         default: nButton = CMouseInputDevice::BUTTON_NONE; break;  
      }

      if (g_vbMousePushed[0] && g_vbMousePushed[2]) 
         nButton = CMouseInputDevice::BUTTON_MIDDLE;

      g_mouse.onPushButton(CUIPoint(x,y), nButton); 
      g_nCurMouseButton = button; 
   }
   else {
      g_mouse.onMoveMouse(CUIPoint(x,y)); 
   }
  selectiveDisplay();
}


int main(int argc, char* argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB); // GLUT_DOUBLE | 

   if (CUISystemGLUT::instance() == NULL) 
   {
      CUISystemGLUT *pSysGLUT = NULL;    
      pSysGLUT = new CUISystemGLUT; 
      CUISystemGLUT::setInstance(pSysGLUT); 
   }

   if (CGlobalResourceSet::instance() == NULL) 
   {
      CUISystemGLUT *pSysGLUT = static_cast<CUISystemGLUT*>(CUISystemGLUT::instance()); 
      CGlobalResourceSet *pRes = new CGlobalResourceSet; 
      std::auto_ptr<CIconSetBase> pSmilies(pSysGLUT->loadIconSet("Smilies.bmp", IconType::SMILIE_COUNT, 1)); 
      pRes->m_pSmilies = pSmilies; 
      std::auto_ptr<CIconSetBase> pDigits(pSysGLUT->loadIconSet("Digits.bmp", IconType::DIGIT_COUNT, 1)); 
      pRes->m_pDigits = pDigits; 
      std::auto_ptr<CIconSetBase> pFieldIcons(pSysGLUT->loadIconSet("FieldIcons.bmp", IconType::FIELD_COUNT, 1)); 
      pRes->m_pFieldIcons = pFieldIcons;
      std::auto_ptr<CIconSetBase> pFieldInfos(pSysGLUT->loadIconSet("FieldInfos.bmp", IconType::FIELDINFO_COUNT, 1)); 
      pRes->m_pFieldInfoIcons = pFieldInfos; 
      if (!pRes->isValid()) 
      {
         fprintf(stderr, "Unable to load bitmaps\n"); 
         return 2; 
      }

      CGlobalResourceSet::setInstance(pRes); 
   }

   g_gameMgr.init(&g_mouse); 
   g_gameMgr.resize(CGameDim(30, 16, 99)); 

   CUISize clientSize = g_gameMgr.getClientWindowSize(); 

   glutInitWindowSize(clientSize.x(), clientSize.y());
   glutCreateWindow("Truffle-Swine Keeper");

   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouseCB); 
   timer(123); 

   glutMainLoop();

    return 0;
}
