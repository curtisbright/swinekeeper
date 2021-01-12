// file      : Application.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
// if the preprocessor does not find the header below, you have to add the 
// path to the PTC library to the project settings / makefile 
// see doc/SourceDoc.txt 
#include <ptc.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "UIDrawContextPTC.h"
#include <gamecontrol/CGameManager.h>
#include <gamecontrol/CGlobalResourceSet.h>
#include <gamecontrol/CKeyboardInputDevice2.h>

// You need OpenPTC to compile this project
// look at http://www.gaffer.org/ptc

// int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
int main(int argc, char *argv[])
{

   if (CUISystemPTC::instance() == NULL) 
   {
      CUISystemPTC *pSysPTC = NULL;    
      pSysPTC = new CUISystemPTC; 
      CUISystemPTC::setInstance(pSysPTC); 
   }

   if (CGlobalResourceSet::instance() == NULL) 
   {
      CUISystemPTC *pSysPTC = static_cast<CUISystemPTC*>(CUISystemPTC::instance()); 
      CGlobalResourceSet *pRes = new CGlobalResourceSet; 
      std::auto_ptr<CIconSetBase> pSmilies(pSysPTC->loadIconSet("Smilies.bmp", IconType::SMILIE_COUNT, 1)); 
      pRes->m_pSmilies = pSmilies; 
      std::auto_ptr<CIconSetBase> pDigits(pSysPTC->loadIconSet("Digits.bmp", IconType::DIGIT_COUNT, 1)); 
      pRes->m_pDigits = pDigits; 
      std::auto_ptr<CIconSetBase> pFieldIcons(pSysPTC->loadIconSet("FieldIcons.bmp", IconType::FIELD_COUNT, 1)); 
      pRes->m_pFieldIcons = pFieldIcons;
      std::auto_ptr<CIconSetBase> pFieldInfos(pSysPTC->loadIconSet("FieldInfos.bmp", IconType::FIELDINFO_COUNT, 1)); 
      pRes->m_pFieldInfoIcons = pFieldInfos; 
      if (!pRes->isValid()) 
      {
         fprintf(stderr, "Unable to load bitmaps (Smilies.bmp etc. must be in the current directory)\n"); 
         return 1; 
      }

      CGlobalResourceSet::setInstance(pRes); 
   }

   CGameManager m_gameMgr; 
   CKeyboardInputDevice2 m_keyboard; 
   m_gameMgr.init(&m_keyboard); 
   m_gameMgr.resize(CGameDim(30, 16, 99)); 

   CUISize clientSize = m_gameMgr.getClientWindowSize(); 

   try
   {
      Console console;
      Format format(8);
      console.open("Truffle-Swine Keeper",clientSize.x(), clientSize.y(), format);
      Surface surface(console.width(),console.height(),format);

      Palette pal; 
      CIUDrawContextPTC::getPalette(pal); 
      surface.palette(pal);  

      bool bQuit = false; 
      bool bRequestRefresh = true; 
      int nLastTime = time(NULL); 
      while (!bQuit)
      {
         if (nLastTime != time(NULL)) {
            nLastTime = time(NULL); 
            bRequestRefresh = true; 
         }

         if (console.key()) 
         {
            Key key = console.read(); 
            
            int nPushedNumber(-1); 
            CGameView::MouseButton nPushedButton(CGameView::BUTTON_NONE); 

            if (key.code() >= Key::NUMPAD0 && key.code() <= Key::NUMPAD9)
               nPushedNumber = key.code() - Key::NUMPAD0;

            if (nPushedNumber == -1 && key.code() >= Key::ZERO && key.code() <= Key::NINE)
               nPushedNumber = key.code() - Key::ZERO;

            if (nPushedNumber == -1) 
            {
               // emulate numeric keypad with alpha keys 
               if (key.code() == Key::B) nPushedNumber = 1;  
               if (key.code() == Key::N) nPushedNumber = 2;  
               if (key.code() == Key::M) nPushedNumber = 3;  
               if (key.code() == Key::G) nPushedNumber = 4;  
               if (key.code() == Key::H) nPushedNumber = 5;  
               if (key.code() == Key::J) nPushedNumber = 6;  
               if (key.code() == Key::T) nPushedNumber = 7;  
               if (key.code() == Key::Z) nPushedNumber = 8;  
               if (key.code() == Key::Y) nPushedNumber = 8;  
               if (key.code() == Key::U) nPushedNumber = 9;   
            }

            if (key.code() == Key::X) 
               nPushedButton = CGameView::BUTTON_LEFT; 
            if (key.code() == Key::C) 
               nPushedButton = CGameView::BUTTON_MIDDLE; 
            if (key.code() == Key::V) 
               nPushedButton = CGameView::BUTTON_RIGHT;  

            if (nPushedNumber >= 1) 
            {
               int nKeyX = (nPushedNumber-1)%3-1; 
               int nKeyY = -(nPushedNumber-1)/3+1; 
               
               m_keyboard.onMoveKeyPressed(nKeyX, nKeyY); 
               bRequestRefresh = true; 
            }

            if (nPushedButton != CGameView::BUTTON_NONE) 
            {
               m_keyboard.onClickKeyPressed(nPushedButton); 
               m_keyboard.onClickKeyReleased(); 
               bRequestRefresh = true; 
            }

            if (key.code() == Key::ESCAPE) 
               bQuit = true; 
         
            if (key.code() == Key::SPACE)
            { 
               m_gameMgr.resetGame(); 
               bRequestRefresh = true; 
            }
         }

         if (bRequestRefresh) 
         {
            CIUDrawContextPTC ctx( &surface); 
            m_gameMgr.draw(&ctx, true); 
            surface.copy(console);
            bRequestRefresh = false; 
            console.update();
         }
      }
   }
   catch (Error &error)
   {
       error.report();
   }

   return 0;
}
