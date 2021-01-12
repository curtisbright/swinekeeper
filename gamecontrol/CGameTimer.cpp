// file      : CGameTimer.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CGameTimer.h"

#include <mineuibase/UIDrawContext.h>

CGameTimer::CGameTimer() : 
   m_bIsRunning(false), 
   m_dStartTime(0), 
   m_dStopTime(0) 
   
{}
   
double CGameTimer::getSecs() const {
   return CUISystemBase::instance()->getTime(); 
}

void CGameTimer::startClock()
{
   m_dStartTime = getSecs(); 
   m_bIsRunning = true; 
}

void CGameTimer::stopClock()
{
   m_dStopTime = getSecs(); 
   m_bIsRunning = false; 
}

void CGameTimer::reset()
{
   m_dStartTime = 0; 
   m_dStopTime = 0; 
   m_bIsRunning = false; 
}

void CGameTimer::setStoppedTime(int nSecs)
{
   m_dStartTime = 0; 
   m_dStopTime = nSecs; 
   m_bIsRunning = false; 
}



int CGameTimer::getSecsValue() const
{
   if (m_bIsRunning) 
      return int(getSecs() - m_dStartTime);
   else 
      return int(m_dStopTime - m_dStartTime);  
}
