// file      : CDXJoystick.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#if !defined(AFX_DXJOYSTICK_H__8D5F8381_D19C_439B_8CAF_781E1C139EC7__INCLUDED_)
#define AFX_DXJOYSTICK_H__8D5F8381_D19C_439B_8CAF_781E1C139EC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ddraw.h>
#include <dinput.h>

/** 
 * A wrapper class for a DirectX joystick. 
 * 
 * Can be used to query the current state of the joystick. 
 * Does not support buffered input or events up to now. 
 * 
 * Usage: 
 * CoInitialize(NULL); 
 * createDirectInput(hInst); 
 * createDevice(hWnd, 0); 
 * while(game active) {
 *    queryJoystickState(); 
 *    double dAxis = getAxisValue(AxisTransX); 
 *    // ...
 * }
 */ 
class CDXJoystick {
public: 

   /** 
    * Ids that describe the axes of a joystick. 
    * AxisTransX and AxisTransY are usually the main axes every joystick has.
    */ 
   enum AxisId { 
         AxisTransX=0, AxisTransY, AxisTransZ, 
         AxisRotX, AxisRotY, AxisRotZ, 
         Slider0, Slider1, AxisEnd
   }; 
   
   CDXJoystick(); 
   ~CDXJoystick(); 
   void releaseDevice(); 
   void releaseAll(); 

   HRESULT createDirectInput(HINSTANCE hInstance); 
   HRESULT createDevice(HWND hWnd, int nDeviceIndex); 

   HRESULT queryJoystickState(); 
   bool isButtonPressed(int nButtonIdx); 
   double getAxisValue(AxisId nAxisId); 
   bool isPovCentered(); 
   int getPovDir(); 

   HRESULT setAxisRange(AxisId nAxisId, double dVal0, double dVal1); 

   void getStateInfoString(char *pszStr); 
private: 
   
   IDirectInput *m_pDirectInput; 
   IDirectInputDevice *m_pDevice; 
   IDirectInputDevice2 *m_pDevice2; 
   DIJOYSTATE m_joystickState; 

   class CRangeMap {
   public: 
      CRangeMap(); 
      CRangeMap(int nMin, int nMax, double dOut0, double dOut1); 
      double eval(int nJoyVal); 
   private: 
      int m_nJoyRangeMin; 
      int m_nJoyRangeMax; 
      double m_dOut0; 
      double m_dOut1; 
   }; 
   CRangeMap m_vRangeMap[AxisEnd]; 

   // private methods 
   DWORD offsetOfAxis(AxisId nAxisId); 
   DWORD offsetOfButton(int nButtonIdx);
   DWORD offsetOfPov(int nPovIdx); 
   HRESULT setDriverAxisRange(AxisId nAxisId, int nMin, int nMax); 
   HRESULT getDriverAxisRange(AxisId nAxisId, int &nMin, int &nMax); 
   HRESULT setDeadZone(AxisId nAxisId, double dDeadRatio); 
   HRESULT acquireJoystick(); 
   HRESULT unacquire(); 
   int getAxisValueInt(AxisId nAxisId); 
   DWORD getPovInt(int nPovIdx);
   HRESULT getObjectInfoString(DWORD nOffset, char *pszString); 
   HRESULT getDeviceInfoString(int nDeviceIdx, char *pszStr); 

   // temporary members for callback functions 
   static BOOL CALLBACK DIEnumDevicesProc(const DIDEVICEINSTANCE* lpddi, LPVOID pvRef); 
   int m_nCounter; 
   int m_nEnumIdx;   
   DIDEVICEINSTANCE m_deviceInstance;
   bool m_bFound; 
}; 

#endif // !defined(AFX_DXJOYSTICK_H__8D5F8381_D19C_439B_8CAF_781E1C139EC7__INCLUDED_)
