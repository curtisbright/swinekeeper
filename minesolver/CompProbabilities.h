#ifndef COMPPROBABILITIES_H_INCLUDED
#define COMPPROBABILITIES_H_INCLUDED

#include <minebase/MineBase.h>
#include "CResultField.h" 
#include "CInputField.h" 
#include "CTerminator.h"

class CMineArray; 

namespace Storage {
   class CSection; 
}


/** 
 * Field that holds only the propability that there's a bomb under the field
 */ 
class CPropField {
public: 
   CPropField() : m_bHasProp(false), m_dProp(-1) {
   }
   bool hasProp() const {return m_bHasProp;}
   double getProp() const {return m_dProp;}
   void setProp(double dProp) {m_bHasProp = true; m_dProp = dProp;}
   void setKnownBomb() {setProp(1);}
   void setKnownNoBomb() {setProp(0);}
   bool isKnownBomb() const {return fabs(m_dProp-1) < 1e-6;}
   bool isKnownNoBomb() const {return fabs(m_dProp) < 1e-6;}
   bool isUndecideable() const {return m_dProp > 1e-6 && m_dProp < 1 - 1e-6;}
   void transferData(Storage::CSection section); 

private: 
   bool m_bHasProp; 
   double m_dProp;    
}; 

CResultField propFieldToResult(CPropField src); 

bool compProbabilities(
   CMineArrayBase<CResultField> &resultArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount, 
   CTerminator *pTerminator = NULL); 

bool compProbabilities_Aux(
   CMineArrayBase<CPropField> &resultArray, 
   CMineArray &inputResArray, 
   int nTotalBombCount, 
   double *pdWaysToCoverFieldsWithBombs = NULL, 
   CTerminator *pTerminator = NULL); 

double compTotalProp( 
   CMineArray &inputArray, 
   int nTotalBombCount); 

bool validateProbabilities( 
   CMineArrayBase<CPropField> &resultArray, 
   CMineArray &inputResArray, 
   int nTotalBombCount); 
   

#endif 
