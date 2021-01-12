// file      : CKeyboardInputDevice.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CKEYBOARDINPUTDEVICE_H_INCLUDED
#define CKEYBOARDINPUTDEVICE_H_INCLUDED

#include "InputDevices.h" 
#include "CGameView.h"

/** 
 * Input device for keyboards. 
 * 
 * With it, it is possible to play minesweeper with the 
 * numeric keypad and e.g. the shift- and the control-key. 
 * 
 * I created this class only to be able to port 
 * minesweeper to OpenPTC. Playing minesweeper with 
 * a keyboard is not such a good idea. 
 */ 
class CKeyboardInputDevice : public CInputDeviceBase {
public: 

   CKeyboardInputDevice(); 
   virtual void setView(CGameView *pView); 
   virtual bool getCurFieldPos(CFieldPos &p) const; 
   virtual CGameView::MouseButton getCurMouseButton() const; 
   virtual void draw(CUIDrawContextBase *pCtx, bool bForceUpdate); 

   virtual void getUpdateViewInfo(CGameView::CUpdateViewInfo &viewInfo) const; 
   virtual void getViewDeviceStateInfo(CGameView::CDeviceStateInfo &state) const; 

   void onKeyPressed(int nKeyX, int nKeyY, bool bLeftButton, bool bRightButton); 
   void onKeyReleased(); 

private: 
   
   CFieldPos restrictedToArray(const CFieldPos &fp) const; 

   CGameView *m_pView;

   struct CDeviceState {
      CDeviceState() : m_bRightButton(false), m_bLeftButton(false), m_fieldPos(1,1) {}
      bool m_bRightButton; 
      bool m_bLeftButton; 
      CFieldPos m_fieldPos;  
      CFieldPos m_pushedField;  
   }; 

   CDeviceState m_curState; 
}; 



#endif 
