// file      : UIMisc.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "UIMisc.h" 

CUISize operator-(const CUIPoint &p1, const CUIPoint &p2) {
   return CUISize(p1.x() - p2.x(), p1.y() - p2.y());
}
