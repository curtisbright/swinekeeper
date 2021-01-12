// file      : MineMath.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 

#include "MineMath.h"
#include <cassert>
#include <iostream>
#include <float.h>


using namespace std; 

/** 
 * Compute the following formula: 
 * 
 * ( nC ) 
 * ( nB )
 * -----------
 * ( nC       ) 
 * ( nBBaseMax) 
 * 
 * The nominator is only there to avoid computing large 
 * numbers and thus large errors in the algorithms below. 
 */ 
double bOutOfC(int nB, int nC, int nBBaseMax)
{
   assert(nB >= 0); 
   assert(nB <= nBBaseMax);
   assert(nC >= nB);  
   double nX = 1; 
   int i; 

   for(i=nB+1;i<=nBBaseMax;i++) {
      assert(nC-i+1 > 0); 
      nX *= double(i)/double(nC-i+1); 
   }
   return nX; 
}

double bOutOfC(int nB, int nC) 
{
   double nX = 1; 
   int i; 
   for(i=0;i<nB;i++) {
      nX *= double(nC-i)/double(i+1); 
   }
   return nX; 
}

void CIntDoubleFct::print()
{
   for(int i=0;i<int(m_Fct.size());i++) 
   {
      if (m_Fct[i] != 0) {
         cout << "B[" << i << "]=" << m_Fct[i] << ", "; 
      }
   }
}

CIntDoubleFct::CIntDoubleFct(int nPos, int nValue) : m_Fct(nPos+1,0) {m_Fct[nPos] = nValue;}

void CIntDoubleFct::makeUnit()
{
   m_Fct.resize(1); 
   m_Fct[0] = 1; 
}


void CIntDoubleFct::setInstPerBC(int nBC, double nInst) {
   assert(nBC >= 0 && nBC < int(m_Fct.size())); 
   m_Fct[nBC] = nInst; 
}

/** 
 * add two functions element wise 
 */ 
const CIntDoubleFct& CIntDoubleFct::add(const CIntDoubleFct &c1)
{
   bool bIsThisSmaller = (size() < c1.size()); 
   const CIntDoubleFct &cmin = bIsThisSmaller ? *this : c1; 
   const CIntDoubleFct &cmax = bIsThisSmaller ? c1 : *this; 
   m_Fct.resize(cmax.size(), 0.0); 
   int i; 
   for(i=0;i<cmin.size();i++) m_Fct[i] += c1.m_Fct[i]; 
   if (bIsThisSmaller) {
      for(;i<cmax.size();i++) m_Fct[i] = c1.m_Fct[i]; 
   }
   return *this;    
}

const CIntDoubleFct& CIntDoubleFct::makeAdd(const CIntDoubleFct &c1, const CIntDoubleFct &c2)
{
   *this = c1; 
   add(c2);     
   return *this;   
}


/** 
 * Compute the convolution of two functions. 
 */ 
const CIntDoubleFct& CIntDoubleFct::makeMult(const CIntDoubleFct &c1, const CIntDoubleFct &c2)
{
   int nSumSize = c1.size() + c2.size(); 
   m_Fct.resize(0); 
   m_Fct.resize(nSumSize, 0.0); 

   for(int i1=0;i1<c1.size();i1++) 
      for(int i2=0;i2<c2.size();i2++) 
         m_Fct[i1+i2] += c1.m_Fct[i1]*c2.m_Fct[i2];  

   int nMaxIdxNotZero=0; 
   for(int i=0;i<nSumSize;i++) 
      if (m_Fct[i] != 0) nMaxIdxNotZero=i;
   m_Fct.resize(nMaxIdxNotZero+1); 

   return *this;   
}

const CIntDoubleFct& CIntDoubleFct::mult(const CIntDoubleFct &c1)
{
   CIntDoubleFct f; 
   f.makeMult(*this, c1); 
   *this = f; 
   return *this; 
}

/** 
 * Shift a function (i.e. OutFct(i) = InFct(i-nBombs)) 
 */ 
const CIntDoubleFct& CIntDoubleFct::makeShift(const CIntDoubleFct &c, int nBombs)
{
   *this = c; 
   shift(nBombs); 
   return *this;   
}

const CIntDoubleFct& CIntDoubleFct::shift(int nBombs)
{
   assert(nBombs >= 0); 
   int nOldSize = m_Fct.size();
   m_Fct.resize(m_Fct.size() + nBombs); 
   int i; 
   for(i=nOldSize-1;i>=0;i--) m_Fct[i+nBombs] = m_Fct[i]; 
   for(i=0;i<nBombs;i++) m_Fct[i] = 0; 
   return *this; 
}

int CIntDoubleFct::minNotZeroIdx() {
   int nIdx = m_Fct.size(); 
   for(int i=m_Fct.size()-1;i>=0;i--) 
      if (m_Fct[i]!=0.0) nIdx = i; 
   return nIdx; 
}
int CIntDoubleFct::maxNotZeroIdx() {
   int nIdx = 0; 
   for(int i=0;i<int(m_Fct.size());i++) 
      if (m_Fct[i]!=0.0) nIdx = i; 
   return nIdx; 
}


double CIntDoubleFct::getProp(vector<double> &PropOfBombC, CIntDoubleFct &TotalInst) {
   int maxNotZeroIdx = size(); 
   assert(maxNotZeroIdx <= int(PropOfBombC.size())); 
   assert(maxNotZeroIdx <= TotalInst.size()); 
   double dD = 0; 
   for(int i=0;i<maxNotZeroIdx;i++) 
   {
      if (TotalInst[i] != 0) 
         dD += PropOfBombC[i]*m_Fct[i]/TotalInst[i]; 
      // assert(!_isnan(dD)); 
   }
   return dD;   
}

