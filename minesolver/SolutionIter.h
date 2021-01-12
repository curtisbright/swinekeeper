// file      : SolutionIter.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef SOLUTIONITER_H_INCLUDED
#define SOLUTIONITER_H_INCLUDED

#include "CMineArray.h"

class CSolutionIterG; 

/** 
 * This class, together with CSolutionIterG, is the interface 
 * of a algorithm that computes all valid solutions of a given 
 * minesweeper instance. 
 * @see markKnownFields for a example how it its used. 
 * 
 * CSolutionIter is a iterator that enumerates independent areas
 * of the minesweeper array. (If you take the graph described at @ref CMineArray, 
 * it enumerates connected components of the resoltution graph.) 
 */ 
class CSolutionIter {
   friend CSolutionIterG; 
public: 
   /** 
    * @param array Must be a 'SolveField' 
    */ 
   CSolutionIter(const CMineArray &array); 
   CSolutionIter() {}
   
   /** 
    * Returns true iff the array represents a valid solution
    */ 
   bool isValid() {return m_bValid;}
   
   /** 
    * Return the next connected component. 
    * @return true, iff the function was able to find another connected component 
    * 
    * The union of the active subsets returned by this method together with 
    * the fields set returned by CSolutionIter::resolvedFields
    * is equal to the active subset of this class. The subsets described 
    * above are disjunct. 
    */ 
   bool getNextUnresolvedSubfield(CSolutionIterG &); 
   /** 
    * After computing the solution for a connected component, use this 
    * function to insert the solution into the 'source array' 
    */ 
   void insertSolution(CSolutionIterG &); 

   /** 
    * List of fields the value of which was already determined in the ctor. 
    */ 
   const std::deque<CFieldPos>& resolvedFields() const {return m_resolvedFields;}
   const CMineArray& mineArray() const {return m_array;}

   /**
    * List of fields (vertices) the connected component consists of
    */ 
   const std::deque<CFieldPos> &activeSubSet() const {return m_array.activeSubSet();}

private: 
   CMineArray m_array; 
   bool m_bValid; 
   std::deque<CFieldPos> m_resolvedFields; 

   void constructWithArray(); 
}; 

/** 
 * Creates two mine array by setting a single field to be a bomb/noBomb 
 */ 
class CSolutionIterG {
   friend CSolutionIter; 
public: 
   bool isValid() {return m_bValid;}
   /** 
    * Return the two guesses. 
    * The active subset of the two guesses is equal to 
    * the active subset of this class. 
    */ 
   void getGuesses(CSolutionIter &g1, CSolutionIter &g2); 
   /** 
    * After solving the guesses, use this function to insert the 
    * solution into the source array again.
    */ 
   void applyGuesses(CSolutionIter &g1, CSolutionIter &g2); 
   const std::deque<CFieldPos> &activeSubSet() const {return m_subArray.activeSubSet();}
private: 
   CMineArray m_subArray; 
   bool m_bValid; 
}; 


#endif 
