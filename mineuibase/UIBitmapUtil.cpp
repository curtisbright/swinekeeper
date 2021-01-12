// file      : UIBitmapUtil.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "UIBitmapUtil.h" 

#include "UIDrawContext.h" 
#include <stdlib.h>
#include <stdio.h>
#include <cassert>

typedef unsigned char BMP_UINT8; 
typedef unsigned short BMP_UINT16; 
typedef unsigned long BMP_UINT32; 
typedef long BMP_INT32; 

// structures for reading the bitmaps 
// all little endian
// the compiler must not insert bytes for padding 
// (I modified the structures so that he usually won't do this) 
struct CBmpBitmapFileHeader  { 
    BMP_UINT16    nType;       // must be "BM" 
    BMP_UINT16    nSizeLow;       // size of bitmap file in bytes 
    BMP_UINT16    nSizeHigh;
    BMP_UINT16    nReserved1; 
    BMP_UINT16    nReserved2; 
    BMP_UINT16    nOffBitsLow;    // offset from beginning to bitmap bits 
    BMP_UINT16    nOffBitsHigh; 
}; 
const int CBMPBITMAPFILEHEADER_SIZE = 7*2; 

struct CBmpBitmapInfoHeader { 
    BMP_UINT32  nSize;         // size of this structure in bytes 
    BMP_INT32   nWidth;        // width of picture in pixels 
    BMP_INT32   nHeight;       // height in pixels (might be negative ???) 
    BMP_UINT16  nPlanes;       // always 1 
    BMP_UINT16  nBitCount;     // 8 means 256 colors 
    BMP_UINT32  nCompression;  // must be 0, in our case (== no compression) 
    BMP_UINT32  nSizeImage;    // don't use 
    BMP_INT32   nXPixelsPerMeter; 
    BMP_INT32   nYPixelsPerMeter; 
    BMP_UINT32  nUsedColorIndices; 
    BMP_UINT32  nRequiredColorCount; 
}; 

struct CBmpRGBColor { 
    BMP_UINT8    nBlue; 
    BMP_UINT8    nGreen; 
    BMP_UINT8    nRed; 
    BMP_UINT8    nReserved; 
}; 

/** 
 * Loads a Bitmap into memory. 
 * 
 * The function reads a BMP-file into memory and returns the stored image 
 * as a rectangular array of unsigned chars. 
 * The values of this array are according to the enum CUIDrawContextBase::Color. 
 *
 * @return Success 
 * @param fp A opened BMP file. Must be a uncompressed 256 color Bitmap. 
 * @param bitmap On return this array contains the image row by row, upper row first. 
 * @param size The width and height of the image (i.e. bitmap.size() == size.x()*size.y())
 */  
bool UILoadBitmap(FILE *fp, std::vector<unsigned char> &bitmap, CUISize &size)
{
   const CUIRGBColor *pPalArray = CUIDrawContextBase::mStatic_RGBPalette; 
   int nPalSize = CUIDrawContextBase::END_COLOR; 

   CBmpBitmapFileHeader header; 

   // code works only for 32 bit integers, 
   // little endian byte order 
   int nTestVal = 1; 
   assert(sizeof(nTestVal)==4); 
   assert(*((char*)(&nTestVal)) == 1); 
   
   // no padding allowed  
   assert((char*)(&(header.nOffBitsHigh)) - (char*)(&header) == 6*2); 

   int nRet = 0; 
   nRet = fread(&header, CBMPBITMAPFILEHEADER_SIZE, 1, fp); 
   if (nRet != 1) 
      return false; 

   CBmpBitmapInfoHeader infoheader; 
   
   // no padding allowed 
   assert((char*)(&(infoheader.nRequiredColorCount)) - (char*)(&infoheader) == 36); 
   
   nRet = fread(&infoheader, sizeof(CBmpBitmapInfoHeader), 1, fp); 
   if (nRet != 1) 
      return false; 

   int nDiff = infoheader.nSize - sizeof(CBmpBitmapInfoHeader); 
   if (nDiff > 0) {
      fseek(fp, nDiff, SEEK_CUR); 
   }
   
   if (infoheader.nBitCount != 8) 
      return false; 

   CBmpRGBColor pnIntBMPPalette[256]; 
   assert(sizeof(CBmpRGBColor) == 4); 
   nRet = fread(pnIntBMPPalette, sizeof(int), 256, fp);  
   if (nRet != 256) 
      return false; 

   int i; 

   int map[256]; 
   for(i=0;i<256;i++) 
   {
      CBmpRGBColor col = pnIntBMPPalette[i]; 
      CUIRGBColor palCol(col.nRed, col.nGreen, col.nBlue); 
      int nOptIdx=0; 
      int nMinDist=100000; 
      for(int j=0;j<nPalSize;j++) 
      {
         int nDist = palCol.dist(pPalArray[j]);
         if (nDist < nMinDist) {
            nMinDist = nDist; 
            nOptIdx = j; 
         }
      }
      map[i] = nOptIdx; 
   }

   int nSizeX = infoheader.nWidth; 
   int nSizeY = labs(infoheader.nHeight); 
   
   bitmap.resize(nSizeX*nSizeY); 

   int nX, nY; 
   for(nY=0;nY<nSizeY;nY++)
   {
      for(nX=0;nX<nSizeX;nX++)
      {  
         unsigned char nVal; 
         nRet = fread(&nVal, sizeof(char), 1, fp); 
         if (nRet != 1) 
            return false; 
         bitmap[nX + (nSizeY-nY-1)*nSizeX] = map[nVal]; 
      }
      int nPadding = nSizeX%4; 
      fseek(fp, nPadding, SEEK_CUR); 

   }
   
   size = CUISize(nSizeX, nSizeY); 
   return true; 
}
