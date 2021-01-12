// file      : CGameManager.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CGAMEMANAGER_H_INCLUDED
#define CGAMEMANAGER_H_INCLUDED

#include <string>

class CGameManagerImpl; 
class CInputDeviceBase; 
class CGameDim; 
class CGameDocumentBase; 
class CUIDrawContextBase; 
class CUISize; 

/** 
 * This class serves as the interface (facade) to 
 * the actual UI implementation. You only need to access this interface, 
 * a subclass of CInputDeviceBase and some very basic classes to 
 * implement a UI. (That is, you don't need to access CGameView and 
 * CGameDocument directly.) 
 */ 
class CGameManager {
public: 

   /** 
    * Does only dummy initializations, @see CGameManager::init
    */ 
   CGameManager();
   ~CGameManager();

   /** 
    * Initializes the class. 
    * Must be called once and only once before using any other method 
    * of this class. 
    * Note that this method already expects the singletons CUISystemBase and 
    * CGlobalResourceSet to be initialized. (Therefore not part of the ctor)  
    * 
    * @param pInputDevice the input device (mouse, keyboard...), that is used 
    *           to operate the game. The client still has the ownership of this 
    *           class, but he must not delete it until this class is deleted. 
    */ 
   void init(CInputDeviceBase *pInputDevice);

   /** 
    * Returns the current dimensions of the game 
    */ 
   CGameDim getGameDim() const;

   /** 
    * Resizes the game (new width, height, bomb count) 
    */ 
   void resize(const CGameDim &newGameDim);

   bool userMayEnterHallOfFame() const; 

   /** 
    * Resets the game. 
    * Note that this function does not modify the current dimensions. 
    */ 
   void resetGame();

   /** 
    * Returns the size of the window the game manager needs to 
    * display all of the game. Usually you will call this 
    * after CGameManager::resize to resize the client window. 
    * The window must be able to display the pixels (0,0) 
    * and (getClientWindowSize().x()-1, getClientWindowSize().y()-1)). 
    * (0,0) is the upper left pixel.   
    */ 
   CUISize getClientWindowSize() const;

   /** 
    * Enables the use of question marks to tag fields, unimportant
    */ 
   void enableQMMarkers(bool bActive);
   bool areQMMarkersEnabled() const; 

   /**
    * Returns the time in seconds from the start of the game till the game was 
    * finished, either by loosing or winning. If the game is running, 
    * it returns simply the time till the start of the game. 
    * If the game has not jet started, it returns 0. 
    */  
   int getTime() const;

   /** 
    * Returns true iff the game is currently running 
    */ 
   bool isGameRunning() const;

   /** 
    * Returns true iff the game is lost 
    */ 
   bool isGameWon() const;

   bool isGameFinished() const;

   /** 
    * Shows a solution of the current game instance. 
    * Exact behaviour is undefined, may change in the future. 
    * There's currently no need for a function to hide the solution again, 
    * since the class CGameView does this automatically if 
    * the user clicks in a field. 
    */  
   void showSolution();
   void hideSolution(); 
   
   /** 
    * Draws the game window. 
    *  
    * @param pCtx the drawing context 
    * @param bFullUpdate if this parameter is false, only that parts 
    *           of the game window will be updated that changed since 
    *           the last call to CGameManager::draw. 
    *           Otherwise, the whole window is redrawn. 
    * 
    * @ref CGameManager::getClientWindowSize
    */ 
   void draw(CUIDrawContextBase *pCtx, bool bFullUpdate = false, bool isProcessing = false);

   /** 
    * Tries to get a tooltip message for the field under the current cursor position. 
    * 
    * This method takes the current cursor position from the input device, 
    * and 'asks' the field under it if it wants to display some 
    * textual information. If this is the case, it returns true, 
    * and the the parameter 'str' will contain the string to display. 
    * Usually only some fields in a solution view will actually return 
    * such a string (@see CGameManager::showSolution). The current 
    * standard solution view displays e.g. the probability that a the given 
    * field contains a bomb, but only if this probability is neither 0 nor 1. 
    */ 
   bool getToolTipMsg(std::string& str) const;

   
   void activateRewind();
   void historyPrev();
   void historyNext();

private: 
   CGameManagerImpl *m_pImpl; 

   void showDoc(CGameDocumentBase *pDoc);
   CGameManager(const CGameManager&); 
   CGameManager& operator=(const CGameManager&); 
}; 


#endif 
