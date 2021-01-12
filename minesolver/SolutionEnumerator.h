// file      : SolutionEnumerator.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef SOLUTIONENUMERATOR_H_INCLUDED
#define SOLUTIONENUMERATOR_H_INCLUDED

#ifdef _MSC_VER
#pragma warning (disable:4786) // symbol truncated to length 256 
#endif 

#include <minebase/MineBase.h>
#include <vector>
#include <map>
#include <cassert>
#include <string>
#include "MineSolver.h" 

/** 
 * This vector only makes sense inside of @ref CSolutionEnum
 */ 
class CBoolVector {
public: 
   CBoolVector() {}
   void makeSingle(bool bBomb) {
      m_vector.resize(1); 
      m_vector[0] = bBomb; 
   }
   void makeScaledSingle(bool bBomb, int nFactor) {
      m_vector.resize(nFactor);
      for(int i=0;i<nFactor;i++) m_vector[i] = bBomb; 
   }
   void makeAdd(const CBoolVector &v1, const CBoolVector &v2); 
   void makeScaled(const CBoolVector &v1, int nFactor); 
   void makeRepeated(const CBoolVector &v1, int nFactor); 

   const std::vector<bool> solutions() const {return m_vector;}
   int size() const {return m_vector.size();}
   std::string toString(int nNum = 0) const; 
private: 
// each entry is a solution 
   std::vector<bool> m_vector; 
}; 


/** 
 * Stores a list of solutions for each connected component of 
 * the resolution graph. 
 * Used to enumerate all solutions of a problem instance. 
 */ 
class CSolutionEnum {
public: 
   CSolutionEnum(): m_nSize(1), m_nCurSolution(0) {}
   void makeAdd(const CSolutionEnum &e1,  const CSolutionEnum &e2); 
   void makeMerge(const CSolutionEnum &e1,  const CSolutionEnum &e2); 
   void addSolvedField(const CFieldPos &pos, bool bVal); 
   int solutionCount() const {return m_nSize;}
public: 
   typedef std::map<CFieldPos, CBoolVector> VMapType; 
   /** 
    * Each solution has an index.
    * This map holds a boolean vector for each field which has 
    * as many fields as there are solutions. The vector tells 
    * which fields have bombs in which solutions. 
    */ 
   std::map<CFieldPos, CBoolVector> m_vmap;    
   int m_nSize; 
   int m_nCurSolution; 
private: 
}; 

class CSolEnumArray; 

bool compSolutionEnum(
   CMineArrayBase<CResultField> &resultArray, 
   const CMineArrayBase<CInputField> &inputArray, 
   int nTotalBombCount,
   CSolEnumArray *pEnumArray=NULL); 

class CSolEnumField {
public: 
   CSolEnumField() : 
      m_bIsResolved(false), 
      m_nSolutionIdx(-1), 
      m_bIsBomb(false) 
   {}
   
   bool isResolved() const {return m_bIsResolved;}
   bool hasSolutionSet() const {return m_nSolutionIdx >= 0;}
   /** 
    * Return the index of the solution set that this field is part of 
    * @see CSolEnumArray::getSolutionCount ... 
    */ 
   int setIndex() const {return m_nSolutionIdx;}
   bool isBomb() const {return m_bIsBomb;}
   
   void setResolved(bool bIsBomb) {m_bIsResolved = true; m_bIsBomb = bIsBomb;}
   void setTmpSolution(bool bIsBomb) {m_bIsBomb = bIsBomb;}
   void setSolutionSet(int nSolIdx) {m_nSolutionIdx = nSolIdx;}

private: 
   bool m_bIsResolved; 
   int m_nSolutionIdx; 
   bool m_bIsBomb; 
}; 

/** 
 * A array that can be used to enumerate all solutions 
 * of a problem instance. 
 * Can be visualizes using @ref CSolutionEnumFieldView
 */ 
class CSolEnumArray : public CMineArrayBase<CSolEnumField> {
public: 
   int getSolutionCount(int nSet) const; 
   void applySolution(int nSet, int nSolIdx); 
   void nextSolution(int nSet); 

   void init(const CMineArrayBase<CResultField> &resField); 
   void addSolutionEnum(const CSolutionEnum &e); 

private: 
   std::vector<CSolutionEnum> m_solVector; 

}; 



#endif 
