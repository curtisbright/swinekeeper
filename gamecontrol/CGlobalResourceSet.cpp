// file      : CGlobalResourceSet.cpp
// begin     : Jul 30 2000
// copyright : (C) 2000 by Hans Kopp
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "StdAfx.h" 
#include "CGlobalResourceSet.h" 

#include <cassert>

CGlobalResourceSet *CGlobalResourceSet::m_pInstance=0; 

void CGlobalResourceSet::setInstance(CGlobalResourceSet *p) {
   assert(m_pInstance == 0); 
   m_pInstance = p; 
}
