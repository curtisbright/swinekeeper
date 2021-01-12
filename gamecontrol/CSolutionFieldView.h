// file      : CSolutionFieldView.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef CSOLUTIONFIELDVIEW_H_INCLUDED
#define CSOLUTIONFIELDVIEW_H_INCLUDED

#include <minesolver/CompProbabilities.h>
#include "FieldViews.h" 
// XXX 
#include <minesolver/SolutionEnumerator.h>

/** 
 * FieldView to display the contents of a CMineArrayBase<CResultField>
 * @see CResultField
 * @see CGameView::setExternalFieldView
 */ 
class CSolutionFieldView : public CFieldViewBase {
public: 
   CSolutionFieldView() : 
      m_pDoc(NULL), 
      m_bHasValidSolution(false) {}
   virtual bool initDoc(CGameDocumentBase *pDoc) {
      m_pDoc = pDoc;
      m_runningFieldView.initDoc(pDoc); 
      return computeSolution(); 
   }
   virtual void drawField( 
      CUIDrawContextBase *pCtx, 
      const CUIRect &scrRect, 
      const CFieldPos &fieldPos
   );
   bool getFieldMessage(const CFieldPos &scrPos, std::string &) const; 

   void invalidateSolution() {m_bHasValidSolution = false;}
private:
   CGameDocumentBase *m_pDoc; 
   bool m_bHasValidSolution; 
   CRunningFieldView m_runningFieldView; 
   CMineArrayBase<CResultField> m_propArray; 

   bool computeSolution(); 
}; 

/** 
 * FieldView to display the contents of a @ref CSolEnumArray
 */ 
class CSolutionEnumFieldView : public CFieldViewBase {
public: 
   CSolutionEnumFieldView() : 
      m_pDoc(NULL), 
      m_bHasValidSolution(false) 
   {}
   virtual bool initDoc(CGameDocumentBase *pDoc) {
      m_pDoc = pDoc;
      m_runningFieldView.initDoc(pDoc); 
      computeSolution(); 
      return true;
   }
   virtual void drawField( 
      CUIDrawContextBase *pCtx, 
      const CUIRect &scrRect, 
      const CFieldPos &fieldPos
   );
   bool getFieldMessage(const CFieldPos &scrPos, std::string &) const; 
   bool onPushField(const CFieldPos &, int nMouseButton);

   void invalidateSolution() {m_bHasValidSolution = false;}
private:
   CGameDocumentBase *m_pDoc; 
   bool m_bHasValidSolution; 
   CRunningFieldView m_runningFieldView; 
   CSolEnumArray m_enumArray; 
   CMineArrayBase<CResultField> m_propArray; 

   void computeSolution(); 
}; 


#endif 
