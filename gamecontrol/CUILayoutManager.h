// file      : CUILayoutManager.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CLAYOUTMANAGER_H_INCLUDED
#define CLAYOUTMANAGER_H_INCLUDED

#include <mineuibase/CUIMineFrame.h>
#include <mineuibase/UIDrawContext.h>
#include <minebase/MineBase.h>

/** 
 * Determines the positions of the various entities in the minesweeper window. 
 * Draws the frames in the minesweeper window. 
 */ 
class CUILayoutManager 
{
public: 

   CUILayoutManager();
   void init(const CUISize &smilieSize, const CUISize &digitSize, const CUISize &fieldSize); 
   void resize(int nX, int nY); 

   CUISize getClientSize() const {return m_clientFrame.getSize();}
   CUIRect getClientRect() const {return CUIRect(CUIPoint(0,0), getClientSize());}
   CUIRect getFieldRect(const CFieldPos &fieldPos) const {
      CUIPoint base = m_arrayFrameI.getInteriorBase(); 
      return CUIRect(
         CUIPoint(base.x() + fieldPos.x()*m_FieldSize.x(), base.y() + fieldPos.y()*m_FieldSize.y()),
         m_FieldSize);  
   }
   CUIRect getSmilieRect() const {return m_SmilieFrame.getInteriorRect();}
   CUIRect getLeftDigitsRect() const {return m_MineCounterFrame.getInteriorRect();}
   CUIRect getRightDigitsRect() const {return m_TimeFrame.getInteriorRect();}

   void draw(CUIDrawContextBase *pCtx); 

   bool isOverField(const CUIPoint &p, CFieldPos &fieldPos, double *pdRelX=0, double *pdRelY=0) const;
   bool isOverSmilie(const CUIPoint &p) const; 
   bool isOverClientArea(const CUIPoint &p) const; 
   
   int fieldsX() const {return m_nFieldCountX;}
   int fieldsY() const {return m_nFieldCountY;}

   CUIRect getFieldsRect(const CFieldPos &fieldBegin, const CFieldPos &fieldEnd) const; 

   bool doesTouchFrames(const CUIRect &) const; 

private: 

   CUISize m_DigitSize; 
   CUISize m_SmilieSize; 
   CUISize m_FieldSize; 

   CUIMineFrame m_clientFrame; 
   CUIMineFrame m_arrayFrameI;
   CUIMineFrame m_arrayFrameO;  
   CUIMineFrame m_ToolbarFrameI; 
   CUIMineFrame m_ToolbarFrameO; 
   CUIMineFrame m_ToolbarFrameO2;
   CUIMineFrame m_MineCounterFrame; 
   CUIMineFrame m_TimeFrame; 
   CUIMineFrame m_SmilieFrame; 

   int m_nFieldCountX, m_nFieldCountY; 

   void computeLayout(); 
}; 


#endif 
