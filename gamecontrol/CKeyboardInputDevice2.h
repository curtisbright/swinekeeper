// file      : CKeyboardInputDevice2.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CKEYBOARDINPUTDEVICE2_H_INCLUDED
#define CKEYBOARDINPUTDEVICE2_H_INCLUDED

#include "InputDevices.h" 
#include "CGameView.h"

/** 
 * Input device for keyboards. 
 * 
 * Simpler version than CKeyboardInputDevice, easier portable
 * since it doesn't need the modified keys (shift, ctrl, alt)  
 * 
 * I created this class only to be able to port 
 * minesweeper to OpenPTC. Playing minesweeper with 
 * a keyboard is not such a good idea. 
 */ 
class CKeyboardInputDevice2 : public CInputDeviceBase {
public: 

   CKeyboardInputDevice2(); 
   virtual void setView(CGameView *pView); 
   virtual bool getCurFieldPos(CFieldPos &p) const; 
   virtual CGameView::MouseButton getCurMouseButton() const; 
   virtual void draw(CUIDrawContextBase *pCtx, bool bForceUpdate); 

   virtual void getUpdateViewInfo(CGameView::CUpdateViewInfo &viewInfo) const; 
   virtual void getViewDeviceStateInfo(CGameView::CDeviceStateInfo &state) const; 

   // input events from the keyboard
   void onMoveKeyPressed(int nKeyX, int nKeyY); 
   void onClickKeyPressed(CGameView::MouseButton nButtonIndex); 
   void onClickKeyReleased(); 

private: 
   
   CFieldPos restrictedToArray(const CFieldPos &fp) const; 

   CGameView *m_pView;

   struct CDeviceState {
      CDeviceState() : m_nButton(CGameView::BUTTON_NONE), m_fieldPos(1,1) {}
      CGameView::MouseButton m_nButton; 
      CFieldPos m_fieldPos;  
   }; 

   CDeviceState m_curState; 
}; 



#endif 
