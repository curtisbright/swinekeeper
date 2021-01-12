// file      : CJoystickInputDevice.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CJOYSTICKINPUTDEVICE_H_INCLUDED
#define CJOYSTICKINPUTDEVICE_H_INCLUDED

#include "InputDevices.h" 
#include "CGameView.h"

/** 
 * Input device for joysticks 
 * 
 * This was a experiment if playing minesweeper with 
 * a joystick is possible. Result: not a good idea.
 *
 */ 
class CJoystickInputDevice : public CInputDeviceBase {
public: 

   CJoystickInputDevice(); 
   virtual void setView(CGameView *pView); 
   virtual bool getCurFieldPos(CFieldPos &p) const; 
   virtual CGameView::MouseButton getCurMouseButton() const; 
   virtual void draw(CUIDrawContextBase *pCtx, bool bForceUpdate); 

   virtual void getUpdateViewInfo(CGameView::CUpdateViewInfo &viewInfo) const; 
   virtual void getViewDeviceStateInfo(CGameView::CDeviceStateInfo &state) const; 

   void onButtonPressed(bool bLeft, bool bRight); 
   void onFireReleased(); 
   void onMoved(double dX, double dY); 
   void onButtonReleased(); 

   enum {AreaRadius = 3}; 

private: 
   

   CFieldPos restrictedToArray(const CFieldPos &fp) const; 

   CGameView *m_pView;

   struct CDeviceState {
      CDeviceState() : 
         m_bRightButton(false), 
         m_bLeftButton(false), 
         m_centerField(AreaRadius, AreaRadius),
         m_selectedField(AreaRadius, AreaRadius)
      {}
      bool m_bRightButton; 
      bool m_bLeftButton; 
      CFieldPos m_centerField;   
      CFieldPos m_selectedField;  
   }; 

   CDeviceState m_curState; 
}; 



#endif 
