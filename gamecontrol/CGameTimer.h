// file      : CGameTimer.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CGAMETIMER_H_INCLUDED
#define CGAMETIMER_H_INCLUDED

/** 
 * Start/Stop-Timer. 
 * Used to implement the display of the time that elapsed
 * since the beginning of a game. 
 */ 
class CGameTimer {
public: 
   CGameTimer(); 
   void startClock(); 
   void stopClock(); 
   void reset(); 
   int getSecsValue() const; 
   void setStoppedTime(int nSecs); 
private: 
   bool m_bIsRunning; 
   double m_dStartTime; 
   double m_dStopTime; 
   double getSecs() const; 
}; 

#endif 
