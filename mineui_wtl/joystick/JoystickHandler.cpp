// file      : JoystickHandler.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
#include "stdafx.h" 
#include "JoystickHandler.h"

#include "CDXJoystick.h"

static CDXJoystick g_joystick; 
static CJoystickInputDevice *g_pDevice = NULL; 
static bool g_bFirePushed = false; 
static bool g_bLeft = false, g_bRight = false; 

bool joystickHandlerInit(HINSTANCE hModuleInstance, HWND hMainWnd)
{
   HRESULT res = g_joystick.createDirectInput(hModuleInstance); 
   ATLASSERT(SUCCEEDED(res)); 
   if (!SUCCEEDED(res)) 
       return false; 
   res = g_joystick.createDevice(hMainWnd, 0); 
   ATLASSERT(SUCCEEDED(res)); 
   if (!SUCCEEDED(res)) 
       return false; 
   return true; 
}

void joystickRelease()
{
   g_joystick.releaseAll(); 
}


void joystickSetTargetDevice(CJoystickInputDevice *pDevice)
{
   g_pDevice = pDevice; 
}

/** 
 * Reads the joystick and updates the minesweeper input device
 * appropriatly. 
 * Must be called in short intervals (e.g. every 50 ms). 
 * I'm currenly only polling the joystick, which was ok for 
 * this experiment. 
 */ 
void joystickTick()
{
   g_joystick.queryJoystickState(); 
   g_pDevice->onMoved(
      g_joystick.getAxisValue(CDXJoystick::AxisTransX),
      g_joystick.getAxisValue(CDXJoystick::AxisTransY)); 
   bool bFire = g_joystick.isButtonPressed(0); 
   bool bLeft = g_joystick.isButtonPressed(1); 
   bool bRight = g_joystick.isButtonPressed(2); 
   
   if (g_bFirePushed && !bFire) 
      g_pDevice->onFireReleased();
   g_bFirePushed = bFire; 

   bool bPushed = (bLeft && !g_bLeft) || (bRight && !g_bRight);       
   bool bReleased = (!bLeft && g_bLeft) || (!bRight && g_bRight);       
   if (bPushed) 
      g_pDevice->onButtonPressed(bLeft, bRight);
   if (bReleased) 
      g_pDevice->onButtonReleased();
      
   g_bLeft = bLeft; 
   g_bRight = bRight;
}


