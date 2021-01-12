// file      : MineBaseSerialize.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.


#if !defined(AFX_MINEBASESERIALIZE_H__38BF67A1_94BE_11D4_BF0E_000000000000__INCLUDED_)
#define AFX_MINEBASESERIALIZE_H__38BF67A1_94BE_11D4_BF0E_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MineBase.h" 
#include <storage/Document.h>
#include <cassert>

template <typename FIELDTYPE>
void transferDataFromObject(Storage::CSection section, CMineArrayBase<FIELDTYPE> &array)
{
   assert(!section.isTransferDocToObject()); 
   CFieldRange range = array.range(); 
   for(int y=range.beginY(); y<range.endY(); y++) 
   {
      Storage::CSection rowSection = section.addSection("row"); 
      for(int x=range.beginX(); x<range.endX(); x++) 
      {
         Storage::CSection fieldSection = rowSection.addSection("field"); 
         array.fieldValue(CFieldPos(x,y)).transferData(fieldSection); 
      }
   }
}

template <typename FIELDTYPE>
void transferDataFromObjectCompact(Storage::CSection section, CMineArrayBase<FIELDTYPE> &array)
{
   assert(!section.isTransferDocToObject()); 
   CFieldRange range = array.range(); 
   for(int y=range.beginY(); y<range.endY(); y++) 
   {
      std::string rowStr; 
      for(int x=range.beginX(); x<range.endX(); x++) 
      {
         rowStr += array.fieldValue(CFieldPos(x,y)).toString(); 
      }
      section.addItem("row").setString(rowStr); 
   }
}

template <typename FIELDTYPE>
bool transferDataToObject(Storage::CSection section, CMineArrayBase<FIELDTYPE> &array)
{  
   assert(section.isTransferDocToObject()); 
   std::list<Storage::CSection> rows; 
   section.findSections("row", rows); 
   int nSizeY = rows.size(); 
   if (nSizeY < 2) 
      return false; 

   std::list<Storage::CSection> firstRowFields; 
   rows.front().findSections("field", firstRowFields); 

   int nSizeX = firstRowFields.size(); 
   if (nSizeX < 2) 
      return false; 

   array.resize(CFieldRange(0,0, nSizeX, nSizeY));  

   std::list<Storage::CSection>::iterator curRowIter = rows.begin(); 
   for(int y=0;y<nSizeY;y++) 
   {
      std::list<Storage::CSection> fields; 
      (*curRowIter).findSections("field", fields); 
      
      if (int(fields.size()) != nSizeX) 
         return false; 

      std::list<Storage::CSection>::iterator curFieldIter = fields.begin(); 
      for(int x=0;x<nSizeX;x++) 
      {
         array.fieldValue(CFieldPos(x,y)).transferData(*curFieldIter); 
         curFieldIter++; 
      }

      curRowIter++;    
   }
   return true; 
}

template <typename FIELDTYPE>
bool transferDataToObjectCompact(Storage::CSection section, CMineArrayBase<FIELDTYPE> &array)
{  
   assert(section.isTransferDocToObject()); 
   std::list<Storage::CItem> rows; 
   section.findItems("row", rows); 
   const int nSizeY = rows.size(); 
   if (nSizeY < 2) 
      return false; 

   std::string firstRowString; 
   rows.front().getString(firstRowString); 

   const int nChars = firstRowString.length(); 
   const int nCharsPerField = FIELDTYPE::getToStringLength(); 

   if (nChars % nCharsPerField != 0) 
      return false; 

   const int nSizeX = nChars/nCharsPerField; 

   if (nSizeX < 2) 
      return false; 

   array.resize(CFieldRange(0,0, nSizeX, nSizeY));  

   std::list<Storage::CItem>::iterator curRowIter = rows.begin(); 
   for(int y=0;y<nSizeY;y++) 
   {
      std::string rowStr;
      (*curRowIter).getString(rowStr); 
      if (int(rowStr.length()) != nChars) 
         return false; 
            
      for(int x=0;x<nSizeX;x++) 
      {
         std::string fieldStr = rowStr.substr(x*nCharsPerField, nCharsPerField); 
         if (!array.fieldValue(CFieldPos(x,y)).fromString(fieldStr)) 
            return false; 
      }

      curRowIter++;    
   }
   return true; 
}

template <typename FIELDTYPE>
void transferDataCompact(Storage::CSection section, CMineArrayBase<FIELDTYPE> &array)
{
   if (section.isTransferDocToObject()) 
      transferDataToObjectCompact(section, array); 
   else 
      transferDataFromObjectCompact(section, array); 
}

template <typename FIELDTYPE>
void transferData(Storage::CSection section, CMineArrayBase<FIELDTYPE> &array)
{
   if (section.isTransferDocToObject()) 
      transferDataToObject(section, array); 
   else 
      transferDataFromObject(section, array); 
}


#endif // !defined(AFX_MINEBASESERIALIZE_H__38BF67A1_94BE_11D4_BF0E_000000000000__INCLUDED_)
