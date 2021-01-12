#ifndef CINPUTFIELD_H_INCLUDED
#define CINPUTFIELD_H_INCLUDED

#include <minebase/MineBase.h>
#include "CMineArray.h" 
#include <string>

/** 
 * This kind of field is used as input of the resolution algorithms. 
 */ 
class CInputField {
public: 
   CInputField() : m_bCovered(false), m_nCount(0), m_nIsKnownBomb(false) {}
   void setCovered() {m_bCovered = true; m_nCount = 0; m_nIsKnownBomb = false;}
   void setUncovered(int nCount) {m_bCovered = false; m_nCount = nCount; m_nIsKnownBomb = false;}
   void setKnownBomb() {m_bCovered = false; m_nCount = 0; m_nIsKnownBomb = true;}
   bool isCovered() const {return m_bCovered;}
   int getCount() const {return m_nCount;}
   bool isKnownBomb() const {return m_nIsKnownBomb;}
   // serialization 
   static int getToStringLength() {return 1;}
   std::string toString() const;
   bool fromString(const std::string& str);
private: 
   /** 
    * true, iff the field is covered 
    */ 
   bool m_bCovered; 
   /** 
    * Describes the number of bombs in the neighboring fields. 
    * Only valid if the field is not covered.
    */ 
   int m_nCount; 
   /** 
    * True, iff the field is known to be a bomb 
    */ 
   bool m_nIsKnownBomb; 
}; 

void inputArrayToSolveArray(
   CMineArray &dst, 
   const CMineArrayBase<CInputField> &inputArray); 


#endif 
