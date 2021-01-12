
#include "StdAfx.h" 
#include "CInputField.h"
#include "CMineArray.h" 


std::string CInputField::toString() const {
   if (m_nIsKnownBomb)
      return std::string("B"); 
   else if (m_bCovered) 
      return std::string("C"); 
   else 
   {
      char str[2]; 
      str[0] = '0' + m_nCount; 
      str[1] = 0; 
      return std::string(str); 
   }
}

bool CInputField::fromString(const std::string& str) {
   if (str.length() != 1) 
      return false; 

   if (str[0] == 'B') 
   {
      setKnownBomb(); 
      return true; 
   }
   if (str[0] == 'C') 
   {
      setCovered(); 
      return true; 
   }
   else if (str[0] >= '0' && str[0] <= '9') 
   {
      setUncovered(str[0]-'0'); 
      return true; 
   }
   else 
   {
      return false;
   }
}

/** 
 * Creates a CFieldValue (type used by the algos) from CInputField
 */ 
static CFieldValue inputFieldToSolve(CInputField src)
{
   CFieldValue dst; 
   if (src.isKnownBomb()) 
   {
      dst.makeSolveCovered(); 
      dst.setResolvedAs(true); 
   }
   else if (src.isCovered()) 
      dst.makeSolveCovered(); 
   else 
      dst.makeSolveCount(src.getCount()); 
   return dst; 
}

void inputArrayToSolveArray(CMineArray &dst, const CMineArrayBase<CInputField> &inputArray) 
{
   dst.resize(inputArray.range()); 
   CMethodOp0<CFieldValue> makeMarginOp(&CFieldValue::makeSolveMargin); 
   dst.doWithArrayAndMargin(makeMarginOp); 
   for(CRangeIterator iter(inputArray.range()); iter.isValid(); iter++) 
   {
      dst[iter.curPos()] = inputFieldToSolve(inputArray[iter.curPos()]); 
   }
}
