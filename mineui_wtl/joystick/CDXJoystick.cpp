// file      : CDXJoystick.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "stdafx.h"
#include "CDXJoystick.h"
#include <cassert>
#include <cstdio>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDXJoystick::CDXJoystick() : 
   m_pDirectInput(0), 
   m_pDevice(0),
   m_pDevice2(0)
{
   memset(&m_joystickState, 0, sizeof(m_joystickState)); 
   memset(&m_deviceInstance, 0, sizeof(m_deviceInstance));
   m_nCounter = 0; 
   m_nEnumIdx = 0; 
   m_bFound = false; 
}

CDXJoystick::~CDXJoystick()
{
   if (m_pDirectInput) m_pDirectInput->Release(); 
   if (m_pDevice) m_pDevice->Release(); 
   if (m_pDevice2) m_pDevice2->Release(); 
}

/** 
 * Only to release the device before the destructor is called, 
 * usually not needed. 
 */ 
void CDXJoystick::releaseDevice()
{
   if (m_pDevice) m_pDevice->Release(); 
   m_pDevice = NULL; 
   if (m_pDevice2) m_pDevice2->Release(); 
   m_pDevice2 = NULL; 
}

/** 
 * Only to release the device before the destructor is called, 
 * usually not needed. 
 */ 
void CDXJoystick::releaseAll()
{
   if (m_pDirectInput) m_pDirectInput->Release(); 
   m_pDirectInput = NULL; 
   if (m_pDevice) m_pDevice->Release(); 
   m_pDevice = NULL; 
   if (m_pDevice2) m_pDevice2->Release(); 
   m_pDevice2 = NULL; 
}

/** 
 * Initialize direct input. 
 * First method to call after creating a instance of this class. 
 * 
 * Uses COM, so CoInitialize() must have been called before. 
 * Conceptually, this method should not be in the joystick class,
 * however, I'm only using the joystick support of direct X.
 * 
 * @param hInstance instance handle of the current exe 
 * 
 */ 
HRESULT CDXJoystick::createDirectInput(HINSTANCE hInstance)
{
   HRESULT res(S_OK); 
   // res = DirectInputCreate(hInstance, DIRECTINPUT_VERSION, &m_pDirectInput, NULL);
   res = CoCreateInstance(
            CLSID_DirectInput, NULL, CLSCTX_INPROC_SERVER, 
            IID_IDirectInput, (void**)(&m_pDirectInput));  
   if (!SUCCEEDED(res))
      return res; 
   res = m_pDirectInput->Initialize(hInstance, DIRECTINPUT_VERSION); 
   if (!SUCCEEDED(res))
      return res; 

   return S_OK; 
}

/** 
 * Returns a textual description of the joystick devices 
 * that are attached to this machine.
 * Call it only after CDXJoystick::createDirectInput. 
 * 
 * @param nDeviceIndex zero based index of a joystick. For machines
 *        with a single joystick always 0
 *        If theres no joystick for a index, the method simply fails.
 * @param pszStr string to copy the description to. strlen(pszStr)>1024
 *
 */ 
HRESULT CDXJoystick::getDeviceInfoString(int nDeviceIndex, char *pszStr)
{
   m_nCounter = 0; 
   m_nEnumIdx = nDeviceIndex; 
   m_bFound = false; 
   HRESULT res = m_pDirectInput->EnumDevices(
      DIDEVTYPE_JOYSTICK, 
      DIEnumDevicesProc, 
      (void*)(this), 
      DIEDFL_ATTACHEDONLY
      ); 
   if (!SUCCEEDED(res))
      return res; 
   if (!m_bFound) 
      return E_FAIL; 

   sprintf(pszStr, "Product: %s\nInstance: %s\n", 
      m_deviceInstance.tszProductName, m_deviceInstance.tszInstanceName); 

   return S_OK; 
}

/** 
 * Creates a direct input device for a joystick. 
 * Call only after CDXJoystick::createDirectInput.
 * Must be called before the joystick can be accessed. 
 * 
 * After calling this method, each axis returns values in
 * the range from -1 ... 1. (To choose other values : @see CDXJoystick::setAxisRange)
 * 
 * @param hWnd e.g. main window of the application 
 * @param nDeviceIndex choose 0 for machines with a single joystick, 
 *        @see CDXJoystick::getDeviceInfoString
 */ 
HRESULT CDXJoystick::createDevice(HWND hWnd, int nDeviceIndex)
{
   m_nCounter = 0; 
   m_nEnumIdx = nDeviceIndex; 
   m_bFound = false; 
   HRESULT res = m_pDirectInput->EnumDevices(
      DIDEVTYPE_JOYSTICK, 
      DIEnumDevicesProc, 
      (void*)(this), 
      DIEDFL_ATTACHEDONLY
      ); 
   if (!SUCCEEDED(res))
      return res; 
   if (!m_bFound) 
      return E_FAIL; 
   
    res = m_pDirectInput->CreateDevice(m_deviceInstance.guidInstance, &m_pDevice, NULL); 
   if (!SUCCEEDED(res))
      return res; 

   res = m_pDevice->SetDataFormat(&c_dfDIJoystick); 
   if (!SUCCEEDED(res))
      return res; 

   res = m_pDevice->SetCooperativeLevel(hWnd, 
      DISCL_NONEXCLUSIVE | DISCL_FOREGROUND) ;
   if (!SUCCEEDED(res))
      return res; 

   res = m_pDevice->Acquire(); 
   if (!SUCCEEDED(res))
      return res; 

   res = m_pDevice->QueryInterface(IID_IDirectInputDevice2, (void**)(&m_pDevice2)); 
   if (!SUCCEEDED(res))
      return res; 

   res = queryJoystickState(); 
   if (!SUCCEEDED(res))
      return res; 

   int i; 
   for(i=0;i<AxisEnd;i++) setAxisRange(AxisId(i), -1, 1); 

   return S_OK; 
}

/** 
 * Reads the state of the joystick and saves it in a member variable. 
 * The methods @ref CDXJoystick::getAxisValue etc. will return 
 * the state the joystick had when this method was called. 
 */ 
HRESULT CDXJoystick::queryJoystickState()
{
   acquireJoystick(); 

   HRESULT res(S_OK); 
   if (m_pDevice2) 
   {
      res = m_pDevice2->Poll(); 
      if (!SUCCEEDED(res))
         return res; 
   }
   res = m_pDevice->GetDeviceState(sizeof(DIJOYSTATE), &m_joystickState); 
   if (!SUCCEEDED(res))
      return res; 
   return S_OK; 
}


BOOL CALLBACK CDXJoystick::DIEnumDevicesProc(const DIDEVICEINSTANCE* lpddi, LPVOID pvRef)
{
   CDXJoystick *pThis = reinterpret_cast<CDXJoystick*>(pvRef);
   char szStr[1000]; 
   sprintf(szStr, "\nIndex %d: %s, %s\n", pThis->m_nCounter, lpddi->tszProductName, lpddi->tszInstanceName); 
   OutputDebugString(szStr); 
   if (pThis->m_nEnumIdx == pThis->m_nCounter) 
   {
      pThis->m_deviceInstance = *lpddi;
      pThis->m_bFound = true; 
   }  
   pThis->m_nCounter++; 
   return DIENUM_CONTINUE ; 
}

DWORD CDXJoystick::offsetOfAxis(AxisId nAxisId)
{
   return FIELD_OFFSET(DIJOYSTATE, lX) + sizeof(LONG)*nAxisId; 
}

DWORD CDXJoystick::offsetOfButton(int nButtonIdx)
{
   assert(nButtonIdx >= 0 && nButtonIdx < 32); 
   return DIJOFS_BUTTON(nButtonIdx); 
}

DWORD CDXJoystick::offsetOfPov(int nPovIdx)
{
   assert(nPovIdx >= 0 && nPovIdx < 4); 
   return DIJOFS_POV(nPovIdx); 
}




HRESULT CDXJoystick::setDriverAxisRange(AxisId nAxisId, int nMin, int nMax)
{
   assert(int(nAxisId) >= 0 && nAxisId < AxisEnd); 
   DIPROPRANGE diprg;
   diprg.diph.dwSize       = sizeof(diprg);
   diprg.diph.dwHeaderSize = sizeof(diprg.diph);
   diprg.diph.dwObj        = offsetOfAxis(nAxisId); 
   diprg.diph.dwHow        = DIPH_BYOFFSET;
   diprg.lMin              = nMin;
   diprg.lMax              = nMax;

   HRESULT res = m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph) ; 
   if (!SUCCEEDED(res))
      return res; 

   return S_OK; 
}

HRESULT CDXJoystick::getDriverAxisRange(AxisId nAxisId, int &nMin, int &nMax)
{
   assert(int(nAxisId) >= 0 && nAxisId < AxisEnd); 
   DIPROPRANGE diprg;
   diprg.diph.dwSize       = sizeof(diprg);
   diprg.diph.dwHeaderSize = sizeof(diprg.diph);
   diprg.diph.dwObj        = offsetOfAxis(nAxisId); 
   diprg.diph.dwHow        = DIPH_BYOFFSET;
   diprg.lMin              = 0;
   diprg.lMax              = 0;

   HRESULT res = m_pDevice->GetProperty(DIPROP_RANGE, &diprg.diph) ; 
   if (!SUCCEEDED(res))
      return res; 

   nMin = diprg.lMin;
   nMax = diprg.lMax;

   return S_OK; 

}


HRESULT CDXJoystick::setDeadZone(AxisId nAxisId, double dDeadRatio)
{
   assert(int(nAxisId) >= 0 && nAxisId < AxisEnd); 
   assert(dDeadRatio >= 0 && dDeadRatio <= 1); 
   DIPROPDWORD dipdw;

   dipdw.diph.dwSize       = sizeof(dipdw);
   dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
   dipdw.diph.dwObj        = offsetOfAxis(nAxisId);
   dipdw.diph.dwHow        = DIPH_BYOFFSET;
   dipdw.dwData            = int(dDeadRatio*10000);
   HRESULT res = m_pDevice->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
   if (!SUCCEEDED(res))
      return res; 
   return S_OK; 
}

HRESULT CDXJoystick::acquireJoystick()
{
   HRESULT res = m_pDevice->Acquire(); 
   if (!SUCCEEDED(res))
      return res; 
   return S_OK; 
}

HRESULT CDXJoystick::unacquire()
{
   HRESULT res = m_pDevice->Unacquire(); 
   if (!SUCCEEDED(res))
      return res; 
   return S_OK; 
}


int CDXJoystick::getAxisValueInt(AxisId nAxisId)
{
   assert(int(nAxisId) >= 0 && nAxisId < AxisEnd); 
   long *pAxisPtr = (long*)((char*)(&m_joystickState) + offsetOfAxis(nAxisId)); 
   return (int)(*pAxisPtr); 
}

bool CDXJoystick::isButtonPressed(int nButtonIdx)
{
   char *pButtonPtr = ((char*)(&m_joystickState) + offsetOfButton(nButtonIdx));
   return ((*pButtonPtr) & 128) != 0; 
}

DWORD CDXJoystick::getPovInt(int nPovIdx)
{
   DWORD *pPovPtr = (DWORD*)((char*)(&m_joystickState) + offsetOfPov(nPovIdx));
   return (DWORD)(*pPovPtr); 
}

CDXJoystick::CRangeMap::CRangeMap() : 
   m_nJoyRangeMin(0), 
   m_nJoyRangeMax(0x10000), 
   m_dOut0(0), 
   m_dOut1(1)
{}

CDXJoystick::CRangeMap::CRangeMap(int nMin, int nMax, double dOut0, double dOut1) : 
   m_nJoyRangeMin(nMin), 
   m_nJoyRangeMax(nMax), 
   m_dOut0(dOut0), 
   m_dOut1(dOut1)
{}

double CDXJoystick::CRangeMap::eval(int nJoyVal)
{
   return (nJoyVal-m_nJoyRangeMin)*(m_dOut1-m_dOut0)
             /(m_nJoyRangeMax-m_nJoyRangeMin) 
          + m_dOut0; 
}

/** 
 * Sets the range of values that are returned by a given axis. 
 * Can be used to mirror a axis. 
 * 
 * @param nAxisId id of the axis to modify
 * @param dVal0 value the lower bound of the axis range is mapped to 
 * @param dVal1 value the upper bound of the axis range is mapped to
 */ 
HRESULT CDXJoystick::setAxisRange(AxisId nAxisId, double dVal0, double dVal1)
{
   assert(int(nAxisId) >= 0 && nAxisId < AxisEnd); 
   int nMin(0), nMax(0x10000); 
   HRESULT res = getDriverAxisRange(nAxisId, nMin, nMax); 
   if (!SUCCEEDED(res)) 
      return res; 
   m_vRangeMap[int(nAxisId)] = CRangeMap(nMin, nMax, dVal0, dVal1); 
   return S_OK; 
}

/** 
 * Returns the value of a given axis. 
 * 
 * @see CDXJoystick::queryJoystickState
 * @see CDXJoystick::setAxisRange
 */ 
double CDXJoystick::getAxisValue(AxisId nAxisId)
{
   assert(int(nAxisId) >= 0 && nAxisId < AxisEnd); 
   int nAxisValue = getAxisValueInt(nAxisId); 
   return m_vRangeMap[int(nAxisId)].eval(nAxisValue); 
}

/** 
 * Returns true iff the view direction selector is centered. 
 */ 
bool CDXJoystick::isPovCentered()
{
   DWORD nPovVal = getPovInt(0); 
   BOOL POVCentered = (LOWORD(nPovVal) == 0xFFFF);
   return POVCentered != 0; 
}

/** 
 * Returns the current direction of the view direction selector. 
 * @return : a value from 0 to 7, right = 0, up = 2, left = 4 ... 
 */ 
int CDXJoystick::getPovDir()
{
   if (isPovCentered()) 
      return 0; 

   int nPovVal = int(getPovInt(0)); 
   int nMathVal = 9000 - nPovVal; 
   if (nMathVal < 0) nMathVal += 36000; 

   return int((nMathVal+4500/2)/4500); 
}

/** 
 * Returns a multi line string describing the state of the joystick. 
 * @see CDXJoystick::queryJoystickState
 * 
 * @param pszStr : strlen(pszStr) > 2024
 */ 
void CDXJoystick::getStateInfoString(char *pszStr)
{
   sprintf(pszStr, "lx %d (%f)\nly %d (%f)\nlz %d (%f)\nlRx %d (%f)\nlRy %d (%f)\nlRz %d (%f)\n"
                  "rglSlider[0] %d (%f)\nrglSlider[1] %d (%f)\n"
                  "rgdwPOV[0] %d, %s\n"
                  "rgbButtons[0] %d\nrgbButtons[1] %d\n"
                  "rgbButtons[2] %d\nrgbButtons[3] %d\n"
                  "rgbButtons[4] %d\nrgbButtons[5] %d\n"
                  "rgbButtons[6] %d\nrgbButtons[7] %d\n",
                  getAxisValueInt((AxisId)0), getAxisValue((AxisId)0),
                  getAxisValueInt((AxisId)1), getAxisValue((AxisId)1),
                  getAxisValueInt((AxisId)2), getAxisValue((AxisId)2),
                  getAxisValueInt((AxisId)3), getAxisValue((AxisId)3),
                  getAxisValueInt((AxisId)4), getAxisValue((AxisId)4),
                  getAxisValueInt((AxisId)5), getAxisValue((AxisId)5),
                  getAxisValueInt((AxisId)6), getAxisValue((AxisId)6),
                  getAxisValueInt((AxisId)7), getAxisValue((AxisId)7),
                  getPovDir(), isPovCentered() ? "centered" : "", 
                  int(isButtonPressed(0)), 
                  int(isButtonPressed(1)), 
                  int(isButtonPressed(2)), 
                  int(isButtonPressed(3)), 
                  int(isButtonPressed(4)), 
                  int(isButtonPressed(5)), 
                  int(isButtonPressed(6)), 
                  int(isButtonPressed(7))); 
}  

HRESULT CDXJoystick::getObjectInfoString(DWORD nOffset, char *pszString)
{
   DIDEVICEOBJECTINSTANCE objInstance; 
   memset(&objInstance, 0, sizeof(objInstance)); 
   objInstance.dwSize = sizeof(DIDEVICEOBJECTINSTANCE); 
   
   HRESULT res = m_pDevice->GetObjectInfo(&objInstance, nOffset, DIPH_BYOFFSET); 
   if (!SUCCEEDED(res))
      return res; 
   
   sprintf(pszString, "Name : %s\n", objInstance.tszName); 
   return S_OK; 
}

