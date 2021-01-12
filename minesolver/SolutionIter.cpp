// file      : SolutionIter.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "SolutionIter.h" 

CSolutionIter::CSolutionIter(const CMineArray &array) : m_array(array)
{
   m_array.computeGlobalActiveSubset(); 
   constructWithArray(); 
}

void CSolutionIter::constructWithArray()
{
   m_bValid = m_array.resolveActiveSubset(); 
   if (!m_bValid) 
      return; 
   m_array.clearFieldMarker(); 
   m_array.getResolvedFields(m_resolvedFields); 
}


bool CSolutionIter::getNextUnresolvedSubfield(CSolutionIterG &iterG)
{
   if (!m_bValid) 
      return false; 
   if (!m_array.getConnectedComponent(iterG.m_subArray)) 
      return false; 
   iterG.m_bValid = false; 
   return true; 
}

void CSolutionIter::insertSolution(CSolutionIterG &iterG)
{
   if (iterG.isValid()) 
   {
      m_array.insertSolution(iterG.m_subArray);   
   }
   else       
      m_bValid = false; 
}

void CSolutionIterG::getGuesses(CSolutionIter &g0, CSolutionIter &g1)
{
   m_subArray.splitField(g0.m_array, g1.m_array); 
   g0.constructWithArray(); 
   g1.constructWithArray(); 
}
 
void CSolutionIterG::applyGuesses(CSolutionIter &g0, CSolutionIter &g1)
{
   if (!g0.m_bValid && !g1.m_bValid) 
   {
      m_bValid = false; 
      return;   
   }
   m_subArray.mergeArray(g0.m_array, g0.m_bValid, g1.m_array, g1.m_bValid); 
   m_bValid = true; 
}

