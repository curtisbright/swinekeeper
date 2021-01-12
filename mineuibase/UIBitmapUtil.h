// file      : UIBitmapUtil.h
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#ifndef UIBITMAPUTIL_H_INCLUDED
#define UIBITMAPUTIL_H_INCLUDED

#include <stdio.h>
#include <vector>
#include "UIMisc.h" 

bool UILoadBitmap(FILE *fp, std::vector<unsigned char> &bitmap, CUISize &size); 

#endif 
