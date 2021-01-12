// file      : CGameView.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CGAMEVIEW_H_INCLUDED
#define CGAMEVIEW_H_INCLUDED

#include <mineuibase/UIMisc.h>
#include "CUILayoutManager.h"
#include "FieldViews.h"
#include <string>
#include "CGameDocumentBase.h" 
#include "CDocChangeObserver.h" 

class CGameDocumentBase; 

/** 
 * Renders the whole client area of a minesweeper window. 
 * 
 * This class draws the whole client area, including 
 * the 'smilie'-button etc... 
 * 
 * The class delegates the drawing of the mine array to 
 * subclasses of @ref CFieldViewBase. 
 * 
 * The class takes some effort to redraw as little as 
 * possible at each update event to assure a good 
 * response time of the game. 
 */ 
class CGameView { 
public: 

   class CUpdateViewInfo {
   public: 
      CUpdateViewInfo() : m_bFullUpdate(false), m_updFieldsBegin(0,0), m_updFieldsEnd(0,0) {}
      void setFullUpdate() {m_bFullUpdate = true;}
   
      void setUpdateField(const CFieldPos &p) {
         m_updFieldsBegin = p; m_updFieldsEnd = CFieldPos(p.x()+1, p.y()+1);
      }
   
      void setUpdateFieldTriple(const CFieldPos &p) {
         m_updFieldsBegin = CFieldPos(p.x()-1, p.y()-1); 
         m_updFieldsEnd = CFieldPos(p.x()+2, p.y()+2);
      }

      bool doFullUpdate() const {return m_bFullUpdate;}
      bool doUpdateField(const CFieldPos &p) const {
         return p.inRange(m_updFieldsBegin, m_updFieldsEnd); 
      } 
      
   private: 
      bool m_bFullUpdate; 
      CFieldPos m_updFieldsBegin; 
      CFieldPos m_updFieldsEnd; 
   }; 

   class CDeviceStateInfo {
   public: 
      CDeviceStateInfo() : 
         m_bIsButtonPushed(false), 
         m_bIsSmiliePushed(false),
         m_bIsSolverProcessing(false) {} 
      bool m_bIsButtonPushed;    // true if a mouse button is pushed somewhere
      bool m_bIsSmiliePushed;    // true if mouse button is pushed on smilie
      bool m_bIsSolverProcessing; // true if solver is currently processing 
   }; 

   class CGameViewListener {
   public: 
      virtual void onPushSmilie()=0; 
   }; 

   enum MouseButton {
      BUTTON_NONE=-1,
      BUTTON_LEFT=0, 
      BUTTON_MIDDLE=1, 
      BUTTON_RIGHT=2
   }; 

   CGameView(CGameDocumentBase *pDoc);
   ~CGameView(); 
     
   void draw(CUIDrawContextBase *pCtx, 
             const CDeviceStateInfo&,
             const CUpdateViewInfo&);  

   void resetFieldView() {
      computeFieldViewFromDocState(); 
   }

   CUISize getClientSize() const {
      return m_LayoutMgr.getClientSize(); 
   }

   bool setFieldView(CFieldViewBase *pFieldView); 
  
   bool getToolTipMsg(const CFieldPos &, std::string& str) const; 
   bool isRedrawable(const CFieldPos &) const; 
   CUIRect getFieldRect(const CFieldPos &) const; 

   // controller 
   void onPushField(const CFieldPos &fieldPos, MouseButton nButton); 
   void onReleaseField(const CFieldPos &fieldPos, MouseButton nButton); 
   void pushSmilie(); 

   const CUILayoutManager &layout() const {return m_LayoutMgr;}

   void setListener(CGameViewListener *pListener) {
      m_pListener = pListener; 
   }

private: 
   /** 
    * The document this view displays 
    */ 
   CGameDocumentBase *m_pDoc;  
    
   CDocChangeObserver m_changeObserver;      
   /** 
    * A class that determines the position of the entities on the client area. 
    */ 
   CUILayoutManager m_LayoutMgr; 
    
   CFieldViewBase *m_pCurFieldView;
                                 
   CGameViewListener *m_pListener; 
   
   CGameView(const CGameView&); 
   CGameView& operator=(const CGameView&); 

   void recomputeLayout();
   void computeFieldViewFromDocState(); 
   void requestFullUpdate() {m_changeObserver.forceFullUpdate();}
}; 

#endif 
