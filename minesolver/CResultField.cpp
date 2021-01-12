#include "StdAfx.h" 
#include "CResultField.h" 

#include <cstdio>
#include <storage/Document.h>

std::string CResultField::toString() const {
   int nProp = int(m_dProp*1000); 
   if (nProp >= 1000) nProp = 999; 
   if (nProp < 0) nProp = 0; 
   char str[10]; 
   sprintf(str, "%03d:", nProp); 
   return std::string(str); 
}

void CResultField::transferData(Storage::CSection section)
{
   section.transferOptionalItem("prop", m_bHasProp).transferFloat(m_dProp); 
   section.transferOptionalItem("val", m_bHasVal).transferFloat(m_dVal); 
   // section.transferItem("has-prob").transferBool(m_bHasProp); 
   // section.transferItem("prob").transferFloat(m_dProp); 
   // section.transferItem("has-val").transferBool(m_bHasVal); 
   // section.transferItem("val").transferFloat(m_dVal); 
}

bool CResultField::isProbabilityEqual(const CResultField &r1, const CResultField &r2) 
{
   return fabs(r1.getProp() - r2.getProp()) < 1e-3; 
}
