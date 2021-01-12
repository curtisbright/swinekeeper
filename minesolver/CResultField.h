#ifndef CRESULTFIELD_H_INCLUDED
#define CRESULTFIELD_H_INCLUDED

#include <minebase/MineBase.h>
#include "CMineArray.h" 
#include <cmath>
#include <string>

namespace Storage {
   class CSection; 
}


/** 
 * A field that is used as output of several resolution algos. 
 * Basically, each result field holds
 * - the propability that this field is a bomb 
 * - a descriptive string 
 * - a arbitrary number
 * The values of the last two properties depends on the resolution algo used. 
 * Each of these properties are optional, i.e. a algorithm does not 
 * need to provide a value for it. 
 * 
 * You can use the class @ref CSolutionFieldView to visualize arrays of 
 * CResultField's. 
 */ 
class CResultField {
public: 
   CResultField() : m_bHasProp(false), m_dProp(-1), m_bHasVal(false), m_dVal(0) {}
   bool hasProp() const {return m_bHasProp;}
   double getProp() const {return m_dProp;}
   void setProp(double dProp) {m_bHasProp = true; m_dProp = dProp;}
   void setKnownBomb() {setProp(1);}
   void setKnownNoBomb() {setProp(0);}
   bool isKnownBomb() const {return fabs(m_dProp-1) < 1e-6;}
   bool isKnownNoBomb() const {return fabs(m_dProp) < 1e-6;}
   bool isUndecideable() const {return m_dProp > 1e-6 && m_dProp < 1 - 1e-6;}
   void setDesc(const std::string& desc) {m_desc = desc;}
   const std::string desc() {return m_desc;}

   void setVal(double dVal) {m_bHasVal = true; m_dVal = dVal;}
   bool hasVal() const {return m_bHasVal;}
   double getVal() const {return m_dVal;}

   std::string toString() const;

   void transferData(Storage::CSection section); 

   static bool isProbabilityEqual(const CResultField &r1, const CResultField &r2);  

private: 
   /** 
    * True, iff the field has a probability assigned 
    */ 
   bool m_bHasProp;
   /** 
    * Propability that the field holds a bomb. 
    * (of course 1.0 is a sure bomb, 0.0 is a sure no-bomb 
    */  
   double m_dProp;    
   /** 
    * Descriptive string, empty if no string is available
    */ 
   std::string m_desc; 
   /** 
    * True if the field has a descriptive value.
    */ 
   bool m_bHasVal; 
   /** 
    * Descriptive value, 
    * Should be between 0.0 and 1.0 if visualized with @ref CSolutionFieldView
    */ 
   double m_dVal; 
}; 

/* 
*/ 

#endif 
