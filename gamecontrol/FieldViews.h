// file      : FieldViews.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef FIELDVIEWS_H_INCLUDED
#define FIELDVIEWS_H_INCLUDED

#include <mineuibase/UIDrawContext.h>
#include <minebase/MineBase.h>
#include <string>

class CGameDocumentBase; 

/** 
 * Base class of all 'field views'. 
 * Field views determine what to display in the game array. 
 */ 
class CFieldViewBase {
public: 

   /** 
    * Associate a document with the view 
    */ 
   virtual bool initDoc(CGameDocumentBase *pDoc) = 0; 

   /** 
    * Draws the field at position 'fieldPos' inside of the rectangle 'scrRect'
    */ 
   virtual void drawField( 
      CUIDrawContextBase *pCtx, 
      const CUIRect &scrRect, 
      const CFieldPos &fieldPos
   )=0; 

   /** 
    * Returns a description of the field. 
    * @return iff true, the method has returned a descriptive string 
    */ 
   virtual bool getFieldMessage(const CFieldPos &, std::string &) const {return false;}

   /** 
    * Returns true if the field does not show any important information, 
    * and may be redrawn by the client 
    */ 
   virtual bool isRedrawable(const CFieldPos &) const {return false;}

   /** 
    * Called by the client if the user pushes on the field. 
    * @return true, if the method handled the event.
    *         If the method returns false, the client is expected to handle the event.  
    */ 
   virtual bool onPushField(const CFieldPos &, int /*nMouseButton*/) {return false;}

   /** 
    * Only the field view class that displays the array during 
    * playing returns true in this method 
    */ 
   virtual bool isRunningGameView() const {return false;}

   virtual ~CFieldViewBase() {}
}; 

/** 
 * View to display the mine array during normal game play 
 */ 
class CRunningFieldView : public CFieldViewBase {
public: 
   CRunningFieldView() : m_pDoc(NULL) {}

   virtual bool initDoc(CGameDocumentBase *pDoc) {m_pDoc = pDoc; return true;}

   virtual void drawField( 
      CUIDrawContextBase *pCtx, 
      const CUIRect &scrRect, 
      const CFieldPos &fieldPos
   ); 
   virtual bool isRedrawable(const CFieldPos &scrPos) const;
   virtual bool isRunningGameView() const {return true;}

private: 
   CGameDocumentBase *m_pDoc;
}; 

/** 
 * View to display the mine array when the game is lost. It shows the locations of the bombs. 
 */ 
class CLostFieldView : public CFieldViewBase {
public: 
   CLostFieldView() : m_pDoc(NULL) {}
   virtual bool initDoc(CGameDocumentBase *pDoc) {m_pDoc = pDoc; return true;}
   virtual void drawField( 
      CUIDrawContextBase *pCtx, 
      const CUIRect &scrRect, 
      const CFieldPos &fieldPos
   ); 
private: 
   CGameDocumentBase *m_pDoc;
}; 



#endif 
