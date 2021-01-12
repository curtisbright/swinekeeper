// file      : MineBase.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef MINEBASE_H_INCLUDED
#define MINEBASE_H_INCLUDED

#include <cassert>
#include <vector>

/** 
 * Position of a field in a mine array. 
 */ 
class CFieldPos {
friend class CFieldRange; 
friend class CRangeIterator; 
public: 
   CFieldPos() : m_nX(-1), m_nY(-1) {} 
   CFieldPos(int nX, int nY) : m_nX(nX), m_nY(nY) {} 

   CFieldPos neighbor(int nIdx) const {
      assert(nIdx >= 0 && nIdx < 8); 
      return CFieldPos(m_nX+RELX[nIdx], m_nY+RELY[nIdx]); 
   }
   bool operator<(const CFieldPos &p) const{
      if (m_nX==p.m_nX) return m_nY<p.m_nY; 
      return m_nX<p.m_nX; 
   }
   bool operator==(const CFieldPos &p) const{
      return m_nX==p.m_nX && m_nY==p.m_nY; 
   }
   int distTo(const CFieldPos &p) const; 
   bool inRange(int nX, int nY) const {
      return m_nX >= 0 && m_nX < nX 
          && m_nY >= 0 && m_nY < nY;
   } 
   bool inRange(const CFieldPos &begin, const CFieldPos &end) const {
      return m_nX >= begin.m_nX && m_nX < end.m_nX 
          && m_nY >= begin.m_nY && m_nY < end.m_nY;
   }
   CFieldPos sum(int nX, int nY) const {return CFieldPos(m_nX + nX, m_nY + nY);}
   const CFieldPos& add(int nX, int nY) {
      m_nX += nX; 
      m_nY += nY; 
      return *this; 
   }
   void print();

   int x() const {return m_nX;}
   int y() const {return m_nY;}

private: 
   int m_nX; 
   int m_nY; 

private: 
   static const int RELX[8]; 
   static const int RELY[8];    
}; 


/** 
 * Rectangular sub area of a mine array
 */  
class CFieldRange {
friend class CRangeIterator; 
public: 
   CFieldRange(int beginX, int beginY, int endX, int endY) : 
       m_beginX(beginX), m_beginY(beginY), m_endX(endX), m_endY(endY)
   {}
   CFieldRange() : 
       m_beginX(0), m_beginY(0), m_endX(0), m_endY(0)
   {}      

   CFieldPos rand() const;

   int getFieldCount() const {
      return (m_endX-m_beginX)*(m_endY-m_beginY); 
   }

   CFieldRange enlarged(int nSize) const {
      return CFieldRange(m_beginX-nSize, m_beginY-nSize, m_endX+nSize, m_endY+nSize); 
   }

   bool inRange(const CFieldPos&p) const {
      return    p.m_nX >= m_beginX && p.m_nX < m_endX 
             && p.m_nY >= m_beginY && p.m_nY < m_endY; 
   }

   int sizeX() const {return m_endX-m_beginX;}
   int sizeY() const {return m_endY-m_beginY;}

   int beginX() const {return m_beginX;}
   int beginY() const {return m_beginY;}
   int endX() const {return m_endX;}
   int endY() const {return m_endY;}

   bool operator==(const CFieldRange &other) const {
      return m_beginX == other.m_beginX
          && m_beginY == other.m_beginY
          && m_endX == other.m_endX
          && m_endY == other.m_endY; 
   }

private: 
   int m_beginX, m_beginY; 
   // note that the lower right field of the area 
   // is at (m_endX-1, m_endY-1). 
   int m_endX, m_endY; 
}; 

/** 
 * Iterator that enumerates all fields in a field range
 */ 
class CRangeIterator {
public: 
   CRangeIterator(const CFieldRange &r) : 
       m_range(r), m_curPos(m_range.m_beginX, m_range.m_beginY) 
   {}

   const CFieldPos &operator++() {next(); return m_curPos;}
   CFieldPos operator++(int) {CFieldPos p(m_curPos); next(); return p;}
   const CFieldPos &curPos() {return m_curPos;}
   bool isValid() {return !atEnd();}

private: 
   void next() {
      m_curPos.m_nX++; 
      if (m_curPos.m_nX == m_range.m_endX) {
         m_curPos.m_nX = m_range.m_beginX; 
         m_curPos.m_nY++; 
      }
   }
   bool atEnd() {
      return m_curPos.m_nY >= m_range.m_endY; 
   }

   CFieldRange m_range; 
   CFieldPos m_curPos; 
}; 

/** 
 * Base class for all mine arrays in this project. 
 * 
 * It represents a rectangular array of fields. 
 * The type of the fields is a template parameter. 
 * The array always has a margin, i.e. it is bigger by one 
 * field than requested. This margin is only to simplify some operations. 
 * It should always be constant after resizing the array. 
 */ 
template <typename FIELDTYPE> 
class CMineArrayBase 
{
public: 
   
   CMineArrayBase() : m_nStride(0) {}

   /** 
    * Set set size of the array. Constructor. 
    * 
    * @param range: Size of the array without margin. 
    * @param fillValue : value to fill the array with 
    * @param fillMarginValue : value of the margin fields 
    */ 
   void resize(const CFieldRange &range, const FIELDTYPE& fillValue = FIELDTYPE(), const FIELDTYPE& fillMarginValue = FIELDTYPE());

   /** 
    * Return a reference to field at position p. 
    * @param p: position of a field, must be within 'range' (@see CMineArrayBase::resize), 
    *            or be on the margin of the array (i.e. one field beside the range) 
    */ 
   FIELDTYPE &fieldValue(const CFieldPos &p) {
      return m_MineArray[(p.x()-m_range.beginX()+1) + (p.y()-m_range.beginY()+1)*m_nStride];
   }
   const FIELDTYPE &fieldValue(const CFieldPos &p) const {
      return m_MineArray[(p.x()-m_range.beginX()+1) + (p.y()-m_range.beginY()+1)*m_nStride];
   }
   FIELDTYPE &operator[](const CFieldPos &p) {
      return fieldValue(p); 
   }
   const FIELDTYPE &operator[](const CFieldPos &p) const {
      return fieldValue(p); 
   }

   /** 
    * Apply the function object op to all fields of the array (without margin)
    */ 
   template <typename OP> void doWithArray(OP& op)
   {
      for(int i=m_range.beginX();i<m_range.endX();i++)
      { 
         for(int j=m_range.beginY();j<m_range.endY();j++) 
         {
            op(fieldValue(CFieldPos(i,j))); 
         }
      }  
   }
   template <typename OP> void doWithArrayConst(OP& op) const
   {
      for(int i=m_range.beginX();i<m_range.endX();i++)
      { 
         for(int j=m_range.beginY();j<m_range.endY();j++) 
         {
            op(fieldValue(CFieldPos(i,j))); 
         }
      }  
   }
   /** 
    * Apply the function object op to all fields of the array (with margin)
    */ 
   template <typename OP> void doWithArrayAndMargin(OP& op)
   {
      for(std::vector<FIELDTYPE>::iterator iter = m_MineArray.begin(); 
          iter != m_MineArray.end(); 
          iter++) 
      {
         op(*iter); 
      }
   }
   /** 
    * Apply the function object op to all immediate neighbors (8-way neighbors) of p. 
    */ 
   template <typename OP> void doWithNeighbors(const CFieldPos&p, OP& op) 
   {
      for(int i=0;i<8;i++) 
      {
         op(fieldValue(p.neighbor(i))); 
      }
   } 
   template <typename OP> void doWithNeighborsConst(const CFieldPos&p, OP& op) const
   {
      for(int i=0;i<8;i++) 
      {
         op(fieldValue(p.neighbor(i))); 
      }
   } 

   typedef bool (*IsEqualFieldFct)(const FIELDTYPE &f1, const FIELDTYPE& f2); 

   static bool isEqualFunc(
      const CMineArrayBase<FIELDTYPE> &a1, 
      const CMineArrayBase<FIELDTYPE> &a2,
      IsEqualFieldFct pfIsEqualField); 

   /** 
    * return the count of fields in the array 
    */ 
   int getArrayFieldsCount() {return m_range.getFieldCount();}
   const CFieldRange& range() const {return m_range;}

private: 
   CFieldRange m_range; 
   int m_nStride; 
   std::vector<FIELDTYPE> m_MineArray; 
}; 

/** 
 * Function object that calls a method of the field it is applied to. 
 * The method must have the signature 'void (FIELDTYPE::*)()' 
 */ 
template<typename FIELDTYPE> 
class CMethodOp0 {
public: 
   typedef void (FIELDTYPE::*MethodPtrV0)(); 
   CMethodOp0(MethodPtrV0 ptr) : m_fctPtr(ptr) {}
   void operator()(FIELDTYPE &value) {(value.*m_fctPtr)();}
private: 
   MethodPtrV0 m_fctPtr; 
}; 

/** 
 * Function object that calls a method of the field it is applied to. 
 * The method must have the signature 'void (FIELDTYPE::*)(ARG)' 
 */ 
template<typename FIELDTYPE, typename ARG> 
class CMethodOp1 {
public: 
   typedef void (FIELDTYPE::*MethodPtrV1)(ARG); 
   CMethodOp1(MethodPtrV1 ptr, ARG value) : m_fctPtr(ptr), m_value(value) {}
   void operator()(FIELDTYPE &value) {(value.*m_fctPtr)(m_value);}
private: 
   MethodPtrV1 m_fctPtr; 
   ARG m_value; 
}; 

/** 
 * Function object that sets the value of all fields it is appied to. 
 */ 
template<typename FIELDTYPE> 
class CSetValueOp {
public: 
   CSetValueOp(const FIELDTYPE &value) : m_value(value) {}
   void operator()(FIELDTYPE &value) {value = m_value;}
private: 
   FIELDTYPE m_value; 
}; 

/** 
 * Function object that determines the number of fields for which a predicate evaluates to true. 
 * The predicate must have the signature 'bool (FIELDTYPE::*)() const' 
 */ 
template<typename FIELDTYPE>
class CCountTrueOp {
public: 
   typedef bool (FIELDTYPE::*MethodPtrB0)() const; 
   CCountTrueOp(MethodPtrB0 ptr) : m_predPtr(ptr), m_nCount(0) {}
   void operator()(const FIELDTYPE &value) {
      if ((value.*m_predPtr)()) m_nCount++;
   }
   int getCount() const {return m_nCount;}
private: 
   MethodPtrB0 m_predPtr; 
   int m_nCount; 
}; 

template<typename FIELDTYPE>
class CCountFalseOp {
public: 
   typedef bool (FIELDTYPE::*MethodPtrB0)() const; 
   CCountFalseOp(MethodPtrB0 ptr) : m_predPtr(ptr), m_nCount(0) {}
   void operator()(const FIELDTYPE &value) {
      if (!(value.*m_predPtr)()) m_nCount++;
   }
   int getCount() const {return m_nCount;}
private: 
   MethodPtrB0 m_predPtr; 
   int m_nCount; 
}; 


template <typename FIELDTYPE>
void CMineArrayBase<FIELDTYPE>::resize(
      const CFieldRange &range,
      const FIELDTYPE& fillValue,
      const FIELDTYPE& fillMarginValue)
{
   m_MineArray.resize(0); 
   m_range = range; 
   m_nStride = (m_range.endX()-m_range.beginX())+2;  
   m_MineArray.resize(m_nStride * ((m_range.endY()-m_range.beginY())+2), fillMarginValue);
   CSetValueOp<FIELDTYPE> setFillValueOp(fillValue);
   doWithArray(setFillValueOp); 
}

template <typename FIELDTYPE>
bool operator==(const CMineArrayBase<FIELDTYPE> &a1, const CMineArrayBase<FIELDTYPE> &a2) 
{
   if (!(a1.range() == a2.range())) 
      return false; 

   CFieldRange range = a1.range().enlarged(1); 

   for(CRangeIterator iter(range); iter.isValid(); iter++) 
   {
      if (!(a1[iter.curPos()] == a2[iter.curPos()])) 
         return false; 
   }

   return true; 
}

/** 
 * Function that applies the predicate pfIsEqualField(a1[p], a2[p]) to 
 * all fieldpositions of the arrays a1 and a2, and returns true iff the 
 * predicate always returns true. 
 * If the arrays have different size, the function always returns false. 
 * Used to determine if two arrays are equal. 
 */ 
template <typename FIELDTYPE>
bool CMineArrayBase<FIELDTYPE>::isEqualFunc(
   const CMineArrayBase<FIELDTYPE> &a1, 
   const CMineArrayBase<FIELDTYPE> &a2,
   IsEqualFieldFct pfIsEqualField)
{
   if (!(a1.range() == a2.range())) 
      return false; 

   CFieldRange range = a1.range().enlarged(1); 

   for(CRangeIterator iter(range); iter.isValid(); iter++) 
   {
      if (!pfIsEqualField(a1[iter.curPos()], a2[iter.curPos()])) 
         return false; 
   }

   return true; 
}

/** 
 * Convert CMineArrayBase<SRCFIELD> to CMineArrayBase<DSTFIELD>. 
 * 
 * @param fnOp: Pointer to function that converts a single field from SRCFIELD to DSTFIELD. 
 */ 
template <typename DSTFIELD, typename SRCFIELD>
void convertArray(
   CMineArrayBase<DSTFIELD> &dstArray, 
   const CMineArrayBase<SRCFIELD> &srcArray, 
   const DSTFIELD &initval, 
   DSTFIELD (*fnOp)(SRCFIELD))
{
   dstArray.resize(srcArray.range()); 
   CSetValueOp<DSTFIELD> setInitValOp(initval); 
   dstArray.doWithArrayAndMargin(setInitValOp); 
   for(CRangeIterator iter(srcArray.range()); iter.isValid(); iter++) 
   {
      dstArray[iter.curPos()] = fnOp(srcArray[iter.curPos()]); 
   }
}



#endif 
