// file      : MineMath.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef MINEMATH_H_INCLUDED
#define MINEMATH_H_INCLUDED


#include <vector>

double bOutOfC(int nB, int nC, int nBBaseMax); 
double bOutOfC(int nB, int nC); 

/** 
 * A function that maps integers to doubles. 
 * 
 * It is used to store the count of solutions (arrays) in dependency of 
 * the number of bombs used in these solutions. (see @compProbabilities_Aux 
 * for details)
 */ 
class CIntDoubleFct {
public: 
   CIntDoubleFct(int nPos, int nValue);
   CIntDoubleFct() {}
   void makeUnit(); 
   void setInstPerBC(int nBC, double nInst); 
   const CIntDoubleFct& makeAdd(const CIntDoubleFct &c1, const CIntDoubleFct &c2); 
   const CIntDoubleFct& add(const CIntDoubleFct &c1); 
   const CIntDoubleFct& makeMult(const CIntDoubleFct &c1, const CIntDoubleFct &c2); 
   const CIntDoubleFct& mult(const CIntDoubleFct &c1); 
   const CIntDoubleFct& makeShift(const CIntDoubleFct &c, int nBombs); 
   const CIntDoubleFct& shift(int nBombs); 
   int size() const {return m_Fct.size();}
   double operator[](int i) {return m_Fct[i];}
   void print(); 
   int minNotZeroIdx(); 
   int maxNotZeroIdx(); 
   double getProp(std::vector<double> &PropOfBombC, CIntDoubleFct &TotalInst); 

private: 
   std::vector<double> m_Fct; 
}; 

#endif 
