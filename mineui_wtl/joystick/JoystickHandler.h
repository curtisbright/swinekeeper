// file      : JoystickHandler.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef JOYSTICKHANDLER_H_INCLUDED
#define JOYSTICKHANDLER_H_INCLUDED

#include <gamecontrol/CJoystickInputDevice.h>

// a list of functions that connect 
// minesweeper with the joystick
// only for experimental purposes, not clean 

bool joystickHandlerInit(HINSTANCE hModuleInstance, HWND hMainWnd); 
void joystickSetTargetDevice(CJoystickInputDevice *pDevice); 
void joystickTick(); 
void joystickRelease(); 

#endif 
